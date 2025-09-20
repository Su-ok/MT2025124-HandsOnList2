/*
==============================================================================================================================
Name: 17a.c
Author: Suchir Okram
Description: Write a program to execute ls -l | wc.
                a. use dup
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
        close(STDOUT_FILENO);
        dup(fd[1]);
        close(fd[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }
    else {
        close(fd[1]);
        close(STDIN_FILENO);
        dup(fd[0]);
        close(fd[0]);
        execlp("wc", "wc", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }
}

/* 
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q17$ gcc 17a.c -o 17a
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q17$ ./17a
        3      20     135
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q17$ ls
    17a  17a.c
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q17$ ls -l
    total 20
    -rwxrwxr-x 1 suchir-okram suchir-okram 16208 Sep 11 18:17 17a
    -rw-rw-r-- 1 suchir-okram suchir-okram  1374 Sep 11 18:17 17a.c
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q17$ ls -l | wc
        3      20     135
==============================================================================================================================
*/
