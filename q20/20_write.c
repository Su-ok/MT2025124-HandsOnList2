/*
==============================================================================================================================
Name: 20_write.c
Author: Suchir Okram
Description: Write two programs so that both can communicate by FIFO -Use one way communication
Date: 13th Sep, 2025
==============================================================================================================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<string.h>
#define FIFO_NAME "myfifo"
int main() {
    int fd;
    const char *msg="FIFO writer is greeting.";
    if(mkfifo(FIFO_NAME, 0666)==-1) {
        perror("mkfifo(ignored if already exists)");
    }

    fd=open(FIFO_NAME, O_WRONLY);
    if(fd<0) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    write(fd, msg, strlen(msg)+1);
    printf("Writer has sent message: %s\n", msg);
    close(fd);
    return 0;
}
/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q20$ gcc 20_write.c -o 20_write
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q20$ gcc 20_read.c -o 20_read
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q20$ ls
    20_read  20_read.c  20_write  20_write.c
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q20$ ./20_write
    Writer has sent message: FIFO writer is greeting.
==============================================================================================================================
*/