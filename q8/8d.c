/*
==============================================================================================================================
Name: 8d.c
Author: Suchir Okram
Description: Write a separate program using signal system call to catch the following signals.
            d. SIGALRM (use alarm system call)
Date: 1st Oct, 2025
==============================================================================================================================
*/
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
void sigAlrm(int sig) {
    printf("Caught SIGALRM %d\n", sig);
    exit(1);
}
int main() {
    signal(SIGALRM, sigAlrm);
    alarm(3);
    printf("Waiting for the alarm...\n");
    pause();

    return 0;
}

/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q8$ gcc 8d.c -o 8d
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q8$ ./8d
    Waiting for the alarm...
    Caught SIGALRM 14

==============================================================================================================================
*/