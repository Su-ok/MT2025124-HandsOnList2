/*
==============================================================================================================================
Name: 10c.c
Author: Suchir Okram
Description: Write a separate program using sigaction system call to catch the following signals.
            c. SIGFPE
Date: 1st Oct, 2025
==============================================================================================================================
*/
#define _GNU_SOURCE
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
void handling_sigfpe(int sig) {
    printf("\nFloating-Point Exception caught! Signal number: %d. Exiting cleanly.\n", sig);
    exit(EXIT_FAILURE);
}

int main() {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler=handling_sigfpe;

    if(sigaction(SIGFPE, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    printf("Handler installed. Program will now cause a floating-point exception...\n");
    int a = 1, b = 0;
    a = a / b;
    printf("This message will not be printed.\n");

    return 0;
}

/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q10$ gcc 10c.c -o 10c
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q10$ ./10c
    Handler installed. Program will now cause a floating-point exception...

    Floating-Point Exception caught! Signal number: 8. Exiting cleanly.
==============================================================================================================================
*/