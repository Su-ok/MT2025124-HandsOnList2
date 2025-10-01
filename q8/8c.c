/*
==============================================================================================================================
Name: 8c.c
Author: Suchir Okram
Description: Write a separate program using signal system call to catch the following signals.
            c. SIGFPE
Date: 1st Oct, 2025
==============================================================================================================================
*/
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
void handling_sigfpe(int sig) {
    printf("Caught SIGPFE %d\n", sig);
    exit(1);
}
int main() {
    int a=1, b=0, x;
    signal(SIGFPE, handling_sigfpe);
    x=a/b;
    printf("x: %d\n", x);
    return 0;
}

/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q8$ gcc 8c.c -o 8c
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q8$ ./8c
    Caught SIGPFE 8

==============================================================================================================================
*/