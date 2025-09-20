/*
==============================================================================================================================
Name: 17c.c
Author: Suchir Okram
Description: Write a program to execute ls -l | wc.
                c. use fcntl
Date: 11th Sep, 2025
==============================================================================================================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
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
        close(STDOUT_FILENO);
        if(fcntl(fd[1], F_DUPFD, STDOUT_FILENO)==-1) {
            perror("fcntl");
            exit(EXIT_FAILURE);
        }
        close(fd[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }
    else {
        close(fd[1]);
        close(STDIN_FILENO);
        if(fcntl(fd[0], F_DUPFD, STDIN_FILENO)==-1) {
            perror("fcntl");
            exit(EXIT_FAILURE);
        }
        close(fd[0]);
        execlp("wc", "wc", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }
}
/*
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q17$ gcc 17c.c -o 17c
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q17$ ./17c
        7      56     387
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q17$ ls -l | wc
        7      56     387
*/