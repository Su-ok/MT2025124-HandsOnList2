/*
==============================================================================================================================
Name: 8a.c
Author: Suchir Okram
Description: Write a separate program using signal system call to catch the following signals.
            a. SIGSEGV
Date: 1st Oct, 2025
==============================================================================================================================
*/
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
void seg_fault(int sig) {
    printf("Segmentation Fault\n");
    exit(1);
}
int main() {
    signal(SIGSEGV, seg_fault);
    int *p = NULL;
    *p = 10;
    return 0;
}

/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q8$ gcc 8a.c -o 8a
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q8$ ./8a
    Segmentation Fault
==============================================================================================================================
*/