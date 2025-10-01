/*
==============================================================================================================================
Name: 8b.c
Author: Suchir Okram
Description: Write a separate program using signal system call to catch the following signals.
            b. SIGINT
Date: 1st Oct, 2025
==============================================================================================================================
*/
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>
void sigInt(int sig) {
    printf("Caught SIGINT\n");
    exit(0);
}
int main() {
    signal(SIGINT, sigInt);
    while(1) {
        printf("Process is running... \n");
        sleep(1);
    }
    return 0;
}

/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q8$ gcc 8b.c -o 8b
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q8$ ./8b
    Process is running... 
    Process is running... 
    Process is running... 
    Process is running... 
    ^CCaught SIGINT

==============================================================================================================================
*/