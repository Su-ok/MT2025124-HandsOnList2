/*
==============================================================================================================================
Name: 23.c
Author: Suchir Okram
Description: Write a program to print the maximum number of files can be opened within a process and
                size of a pipe (circular buffer).
Date: 21st Sep, 2025
==============================================================================================================================
*/
#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
int main() {
    long maxopen;
    int fd[2];
    int pipesize;
    maxopen=sysconf(_SC_OPEN_MAX);
    if(maxopen==-1) {
        perror("sysconf");
        exit(EXIT_FAILURE);
    }
    printf("Maximum number of open files per process: %ld\n", maxopen);

    if(pipe(fd)==-1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pipesize=fcntl(fd[0], F_GETPIPE_SZ);
    if(pipesize==-1) {
        perror("fcntl(F_GETPIPE_SZ)");
        exit(EXIT_FAILURE);
    }

    printf("Default pipe (circular buffer) size: %d bytes\n", pipesize);
    close(fd[0]);
    close(fd[1]);
    return 0;
}
/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q23$ gcc 23.c -o 23
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q23$ ./23
    Maximum number of open files per process: 1024
    Default pipe (circular buffer) size: 65536 bytes
==============================================================================================================================
*/