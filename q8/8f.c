/*
==============================================================================================================================
Name: 8f.c
Author: Suchir Okram
Description: Write a separate program using signal system call to catch the following signals.
            f. SIGVTALRM (use setitimer system call)
Date: 1st Oct, 2025
==============================================================================================================================
*/
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/time.h>
void handling_sigVTAlrm(int sig) {
    printf("Caught SIVTGALRM %d\n", sig);
    exit(0);
}
int main() {
    struct itimerval timer;
    signal(SIGVTALRM, handling_sigVTAlrm);

    timer.it_value.tv_sec = 2;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    if(setitimer(ITIMER_VIRTUAL, &timer, NULL)==-1) {
        perror("setitimer");
        exit(1);
    }

    printf("Timer set for 2 seconds of CPU time...\n");

    while(1) {}
    return 0;
}
/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q8$ gcc 8f.c -o 8f
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q8$ ./8f
    Timer set for 2 seconds of CPU time...
    Caught SIVTGALRM 26

==============================================================================================================================
*/