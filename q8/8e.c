/*
==============================================================================================================================
Name: 8e.c
Author: Suchir Okram
Description: Write a separate program using signal system call to catch the following signals.
            e. SIGALRM (use setitimer system call)
Date: 1st Oct, 2025
==============================================================================================================================
*/
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/time.h>
void sigAlrm(int sig) {
    printf("Caught SIGALRM %d\n", sig);
    exit(1);
}
int main() {
    struct itimerval timer;
    signal(SIGALRM, sigAlrm);

    timer.it_value.tv_sec = 3;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_REAL, &timer, NULL);

    printf("Waiting for the alarm...\n");
    pause();

    return 0;
}
/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q8$ gcc 8e.c -o 8e
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q8$ ./8e
    Waiting for the alarm...
    Caught SIGALRM 14

==============================================================================================================================
*/