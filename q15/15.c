/*
==============================================================================================================================
Name: 15.c
Author: Suchir Okram
Description: Write a simple program to send some data from parent to the child process.
Date: 11th Sep, 2025
==============================================================================================================================
*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
int main() {
    int fd[2];
    char buffer[]="Hello my child.";
    if(pipe(fd)==-1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    if(fork()) { 
        close(fd[0]);
        write(fd[1], buffer, strlen(buffer)+1);
        close(fd[1]);
    }
    else {
        char buf[20];
        close(fd[1]);
        ssize_t n=read(fd[0], buf, sizeof(buf));
        if(n>0)
            printf("Child got: %s\n",buf);
        close(fd[0]);
    }
    return 0;
}

/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q15$ gcc 15.c -o 15
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q15$ ./15
    Child got: Hello my child.
==============================================================================================================================
*/