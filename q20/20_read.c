/*
==============================================================================================================================
Name: 20_read.c
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
    char buffer[100];
    fd=open(FIFO_NAME, O_RDONLY);
    if(fd<0) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    read(fd, buffer, sizeof(buffer));
    printf("Reader has received message: %s\n", buffer);

    close(fd);
    return 0;
}

/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q20$ ./20_read
    Reader has received message: FIFO writer is greeting.
==============================================================================================================================
*/
