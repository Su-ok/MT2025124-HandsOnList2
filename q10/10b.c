/*
==============================================================================================================================
Name: 10b.c
Author: Suchir Okram
Description: Write a separate program using sigaction system call to catch the following signals.
            b. SIGINT
Date: 1st Oct, 2025
==============================================================================================================================
*/
#define _GNU_SOURCE
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
void handling_sigint(int sig) {
    printf("\nSIGINT signal (%d) caught! Ignoring. Press Ctrl+\\ to quit.\n", sig);
    exit(EXIT_FAILURE);
}

int main() {
    struct sigaction sa;
    sa.sa_handler=handling_sigint;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if(sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    printf("PID: %d. Waiting for SIGINT (Ctrl+C)...\n", getpid());

    while (1) {
        pause();
    }

    return 0;
}

/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q10$ gcc 10b.c -o 10b
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q10$ ./10b
    PID: 18301. Waiting for SIGINT (Ctrl+C)...
    ^C
    SIGINT signal (2) caught! Ignoring. Press Ctrl+\ to quit.
==============================================================================================================================
*/