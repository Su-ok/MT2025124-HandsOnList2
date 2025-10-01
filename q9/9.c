/*
==============================================================================================================================
Name: 9.c
Author: Suchir Okram
Description: Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal - Use signal system call.
Date: 1st Oct, 2025
==============================================================================================================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
int main() {
    printf("Ignoring SIGINT signal\n");
    signal(SIGINT, SIG_IGN);
    sleep(7);
    printf("\nDefault action of SIGINT signal\n");
    signal(SIGINT, SIG_DFL);
    sleep(7);
    return(0);
}
/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q9$ gcc 9.c -o 9
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q9$ ./9
    Ignoring SIGINT signal
    ^C^C^C^C^C^C^C
    Default action of SIGINT signal
    ^C
==============================================================================================================================
*/