/*
==============================================================================================================================
Name: 21_program1.c
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
    const char *msg1="Hello from 21_program1.c!";
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);
    fd1=open(FIFO1, O_WRONLY);
    if(fd1<0) {
        perror("open fifo1");
        exit(EXIT_FAILURE);
    }

    fd2=open(FIFO2, O_RDONLY);
    if(fd2<0) {
        perror("open fifo2");
        exit(EXIT_FAILURE);
    }

    write(fd1, msg1, strlen(msg1)+1);
    printf("21_program1.c sent message: %s\n", msg1);

    read(fd2, buffer, sizeof(buffer));
    printf("21_program1.c received response: %s\n", buffer);

    close(fd1);
    close(fd2);
    return 0;
}
/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q21$ gcc 21_program1.c -o 21p1
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q21$ gcc 21_program2.c -o 21p2
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q21$ ls
    21p1  21p2  21_program1.c  21_program2.c  fifo1  fifo2
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q21$ ./21p1
    21_program1.c sent message: Hello from 21_program1.c!
    21_program1.c received response: Hello from 21_program2.c!
==============================================================================================================================
*/