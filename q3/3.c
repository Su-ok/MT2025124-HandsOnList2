/*
==============================================================================================================================
Name: 3.c
Author: Suchir Okram
Description: Write a program to set (any one) system resource limit. Use setrlimit system call.
Date: 1st Oct, 2025
==============================================================================================================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<sys/resource.h>
int main() {
    struct rlimit rl;
    rl.rlim_cur = 1;
    rl.rlim_max = 2;

    setrlimit(RLIMIT_CPU, &rl);

    printf("CPU time limit set to 1 second.\n");
    while(1);
    return EXIT_SUCCESS;
}

/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q3$ gcc 3.c -o 3
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q3$ ./3
    CPU time limit set to 1 second.
    CPU time limit exceeded (core dumped)
==============================================================================================================================
*/