/*
==============================================================================================================================
Name: 4.c
Author: Suchir Okram
Description: Write a program to measure how much time is taken to execute 100 getppid ( )
                system call. Use time stamp counter.
Date: 1st Oct, 2025
==============================================================================================================================
*/
#include<unistd.h>
#include<stdio.h>
#include<time.h>
int main() {
    clock_t start, end;
    start = clock();

    for(int i = 0; i < 100; i++) {
        getppid();
    }
    end = clock();
    double duration = ((double)(end-start))/CLOCKS_PER_SEC;

    printf("Time taken for 100 getppid system calls: %lf seconds\n", duration);
    return 0;
}

/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q4$ gcc 4.c -o 4
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q4$ ./4
    Time taken for 100 getppid system calls: 0.000063 seconds
==============================================================================================================================
*/