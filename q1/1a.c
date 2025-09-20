/*
==============================================================================================================================
Name: 1a.c
Author: Suchir Okram
Description: Write a separate program (for each time domain) to set a interval timer in 10sec and
                10micro second
                a. ITIMER_REAL
Date: 9th Sep, 2025
==============================================================================================================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/time.h>
#include<unistd.h>
void timer_handler(int sig) {
    static int count=0;
    printf("ITIMER_REAL: Timer expired %d times\n", ++count);

}
int main() {
    struct itimerval timer;
    signal(SIGALRM, timer_handler);
    timer.it_value.tv_sec=10;
    timer.it_value.tv_usec=0;
    timer.it_interval.tv_sec=0;
    timer.it_interval.tv_usec=10;
    if(setitimer(ITIMER_REAL, &timer, NULL)==-1) {
        perror("setitimer");
        exit(EXIT_FAILURE);
    }
    while(1) pause();
    return 0;
}
/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q1$ gcc 1a.c -o 1a
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q1$ ./1a
    ITIMER_REAL: Timer expired 911865 times
    ITIMER_REAL: Timer expired 911866 times
    ITIMER_REAL: Timer expired 911867 times
    ITIMER_REAL: Timer expired 911868 times
    ITIMER_REAL: Timer expired 911869 times
==============================================================================================================================
*/