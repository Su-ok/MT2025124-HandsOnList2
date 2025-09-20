/*
==============================================================================================================================
Name: 14.c
Author: Suchir Okram
Description: Write a simple program to create a pipe, write to the pipe, read from pipe and display on
                the monitor.
Date: 11th Sep, 2025
==============================================================================================================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
int main() {
    int fd[2];
    char write_msg[]="Hello from Question No. 14.";
    char read_buffer[100];
    ssize_t bytes_read;
    if(pipe(fd)==-1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    write(fd[1], write_msg, strlen(write_msg)+1);
    close(fd[1]);
    bytes_read=read(fd[0], read_buffer, sizeof(read_buffer));
    if(bytes_read==-1) {
        perror("read");
        exit(EXIT_FAILURE);
    }
    close(fd[0]);

    printf("Message read from pipe: %s\n", read_buffer);
    return 0;
}

/* 
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q14$ gcc 14.c -o 14
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q14$ ./14
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q14$ ./14
    Message read from pipe: Hello from Question No. 14.
==============================================================================================================================
*/