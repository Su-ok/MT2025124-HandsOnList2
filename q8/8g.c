/*
==============================================================================================================================
Name: 8g.c
Author: Suchir Okram
Description: Write a separate program using signal system call to catch the following signals.
            g. SIGPROF (use setitimer system call)
Date: 1st Oct, 2025
==============================================================================================================================
*/
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/time.h>
void handling_sigProf(int sig) {
    printf("Caught SIGPROF %d\n", sig);
    exit(0);
}
int main() {
    struct itimerval timer;
    signal(SIGPROF, handling_sigProf);

    timer.it_value.tv_sec = 3;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_PROF, &timer, NULL);

    printf("Waiting for profiling timer alarm...\n");
    for(long long i=0; i<1e10; ++i);
    pause();
    return 0;
}
/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q8$ gcc 8g.c -o 8g
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q8$ ./8g
    Waiting for profiling timer alarm...
    Caught SIGPROF 27

==============================================================================================================================
*/