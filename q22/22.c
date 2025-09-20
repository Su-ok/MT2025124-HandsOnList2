/*
==============================================================================================================================
Name: 22.c
Author: Suchir Okram
Description: Write a program to wait for data to be written into FIFO within 10 seconds, use select system call with FIFO.
Date: 20th Sep, 2025
==============================================================================================================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/select.h>
#include<string.h>
#include<errno.h>
#define fifo_name "fifo_select"
int main() {
    int fd;
    char buf[100];
    fd_set readfds;
    struct timeval timeout;
    int ret;

    if(mkfifo(fifo_name, 0666)==-1) {
        if(errno!=EEXIST) {
            perror("mkfifo");
            exit(EXIT_FAILURE);
        }
    }

    fd=open(fifo_name, O_RDONLY | O_NONBLOCK);
    if(fd<0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);
    timeout.tv_sec=10;
    timeout.tv_usec=0;
    printf("Waiting for data for 10 seconds...\n");
    ret=select(fd+1, &readfds, NULL, NULL, &timeout);
    if(ret==-1) {
        perror("select");
        close(fd);
        exit(EXIT_FAILURE);
    }
    else if(ret==0) {
        printf("Timeout: NO data written to FIFO within 10 seconds.\n");
    }
    else {
        if(FD_ISSET(fd, &readfds)) {
            ssize_t n=read(fd, buf, sizeof(buf));
            if(n>0) {
                printf("Received data: %s\n", buf);
            }
            else {
                printf("No data received (EOF or error).\n");
            }
        }
    }
    close(fd);
    return 0;
}
/*
==============================================================================================================================
SAMPLE OUTPUT:
    Terminal 1:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q22$ gcc 22.c -o 22
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q22$ ./22
    Waiting for data for 10 seconds...
    Timeout: NO data written to FIFO within 10 seconds.
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q22$ ./22
    Waiting for data for 10 seconds...

    Terminal 2 (within 10 seconds):
        suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q22$ ls
        22  22.c  fifo_select
        suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q22$ echo "Hello Question 22 via FIFO!" > fifo_select

    Terminal 1 (after writing to fifo_select within 10 seconds):
        suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q22$ ./22
        Waiting for data for 10 seconds...
        Received data: Hello Question 22 via FIFO!
==============================================================================================================================
*/