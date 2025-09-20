/*
==============================================================================================================================
Name: 1b.c
Author: Suchir Okram
Description: Write a separate program (for each time domain) to set a interval timer in 10sec and
                10micro second
                b. ITIMER_VIRTUAL
Date: 9th Sep, 2025
==============================================================================================================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/time.h>
#include<unistd.h>
void timer_handler(int signum) {
    static int count=0;
    printf("ITIMER_VIRTUAL: Timer expired %d times\n", ++count);
}
int main() {
    struct itimerval timer;
    signal(SIGVTALRM, timer_handler);
    timer.it_value.tv_sec=10;
    timer.it_value.tv_usec=0;
    timer.it_interval.tv_sec=0;
    timer.it_interval.tv_usec=10;
    
    if(setitimer(ITIMER_VIRTUAL, &timer, NULL)==-1) {
        perror("setitimer");
        exit(EXIT_FAILURE);
    }
    while(1);
    return 0;
}
/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q1$ gcc 1b.c -o 1b
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q1$ ./1b
    ITIMER_VIRTUAL: Timer expired 7982 times
    ITIMER_VIRTUAL: Timer expired 7983 times
    ITIMER_VIRTUAL: Timer expired 7984 times
    ITIMER_VIRTUAL: Timer expired 7985 times
    ITIMER_VIRTUAL: Timer expired 7986 times
    ITIMER_VIRTUAL: Timer expired 7987 times
    ITIMER_VIRTUAL: Timer expired 7988 times
    ITIMER_VIRTUAL: Timer expired 7989 times
==============================================================================================================================
*/