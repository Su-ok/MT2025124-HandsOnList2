/*
==============================================================================================================================
Name: 16.c
Author: Suchir Okram
Description: Write a program to send and receive data from parent to child vice versa. Use two way
                communication.
Date: 9th Sep, 2025
==============================================================================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
int main() {
    int pipe1[2], pipe2[2];
    pid_t pid;
    char parent_msg[]="Hello my child.";
    char child_msg[]="Hello dear parent.";
    char buffer[100];

    if(pipe(pipe1)==-1 || pipe(pipe2)==-1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid=fork();
    if(pid<0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if(pid>0) {
        close(pipe1[0]);
        close(pipe2[1]);
        write(pipe1[1], parent_msg, strlen(parent_msg)+1);
        close(pipe1[1]);

        read(pipe2[0], buffer, sizeof(buffer));
        printf("Parent received: %s\n", buffer);
        close(pipe2[0]);
    }
    else {
        close(pipe1[1]);
        close(pipe2[0]);
        read(pipe1[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        close(pipe1[0]);

        write(pipe2[1], child_msg, strlen(child_msg)+1);
        close(pipe2[1]);
    }
    return 0;
}
/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q16$ gcc 16.c -o 16
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q16$ ./16
    Child received: Hello my child.
    Parent received: Hello dear parent.
==============================================================================================================================
*/