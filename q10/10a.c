/*
==============================================================================================================================
Name: 10a.c
Author: Suchir Okram
Description: Write a separate program using sigaction system call to catch the following signals.
            a. SIGSEGV
Date: 1st Oct, 2025
==============================================================================================================================
*/
#define _GNU_SOURCE
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
void handling_sigsegv(int sig) {
    printf("\nSegmentation Fault caught! Signal number: %d. Exiting cleanly.\n", sig);
    exit(EXIT_FAILURE);
}

int main() {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler=handling_sigsegv;

    if(sigaction(SIGSEGV, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    printf("Handler installed. Program will now cause a segmentation fault...\n");

    int *ptr = NULL;
    *ptr = 42;

    printf("This message will not be printed.\n");

    return 0;
}

/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q10$ gcc 10a.c -o 10a
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q10$ ./10a
    Handler installed. Program will now cause a segmentation fault...

    Segmentation Fault caught! Signal number: 11. Exiting cleanly.

==============================================================================================================================
*/