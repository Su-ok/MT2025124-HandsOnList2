/*
==============================================================================================================================
Name: 21_program2.c
Author: Suchir Okram
Description: Write two programs so that both can communicate by FIFO -Use two way communication
Date: 16th Sep, 2025
==============================================================================================================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<string.h>
#define FIFO1 "fifo1"
#define FIFO2 "fifo2"
int main() {
    int fd1, fd2;
    char buffer[100];
    const char *msg2="Hello from 21_program2.c!";
    fd1=open(FIFO1, O_RDONLY);
    if(fd1<0) {
        perror("open fifo1");
        exit(EXIT_FAILURE);
    }

    fd2=open(FIFO2, O_WRONLY);
    if(fd2<0) {
        perror("open fifo2");
        exit(EXIT_FAILURE);
    }

    read(fd1, buffer, sizeof(buffer));
    printf("21_program2.c sent message: %s\n", msg2);

    write(fd2, msg2, strlen(msg2)+1);
    printf("21_program2.c received response: %s\n", buffer);

    close(fd1);
    close(fd2);
    return 0;
}
/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q21$ ./21p2
    21_program2.c sent message: Hello from 21_program2.c!
    21_program2.c received response: Hello from 21_program1.c!
==============================================================================================================================
*/