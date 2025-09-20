/*
==============================================================================================================================
Name: 17b.c
Author: Suchir Okram
Description: Write a program to execute ls -l | wc.
                b. use dup2
Date: 11th Sep, 2025
==============================================================================================================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
int main() {
    int fd[2];
    pid_t pid;
    if(pipe(fd)==-1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid=fork();
    if(pid<0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if(pid==0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }
    else {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        execlp("wc", "wc", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }
}

/* 
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q17$ gcc 17b.c -o 17b
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q17$ ./17b
        5      38     261
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q17$ ls -l | wc
        5      38     261
==============================================================================================================================
*/