/*
==============================================================================================================================
Name: 5.c
Author: Suchir Okram
Description: Write a program to print the system limitation of
            a. maximum length of the arguments to the exec family of functions.
            b. maximum number of simultaneous process per user id.
            c. number of clock ticks (jiffy) per second.
            d. maximum number of open files
            e. size of a page
            f. total number of pages in the physical memory
            g. number of currently available pages in the physical memory.
Date: 1st Oct, 2025
==============================================================================================================================
*/
#include<stdio.h>
#include<unistd.h>
int main() {
    printf("---------------------System Limitations---------------------\n");
    printf("maximum length of the arguments to the exec family of functions: %ld\n", sysconf(_SC_ARG_MAX));
    printf("maximum number of simultaneous process per user id: %ld\n", sysconf(_SC_CHILD_MAX));
    printf("maximum number of clock ticks (jiffy) per second: %ld\n", sysconf(_SC_CLK_TCK));
    printf("number of open files : %ld\n", sysconf(_SC_OPEN_MAX));
    printf("size of a page in bytes: %ld\n", sysconf(_SC_PAGE_SIZE));
    printf("total number of pages in the physical memory: %ld\n", sysconf(_SC_PHYS_PAGES));
    printf("number of currently available pages in the physical memory: %ld\n", sysconf(_SC_AVPHYS_PAGES));
    return 0;
}

/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q5$ gcc 5.c -o 5
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q5$ ./5
    ---------------------System Limitations---------------------
    maximum length of the arguments to the exec family of functions: 2097152
    maximum number of simultaneous process per user id: 30087
    maximum number of clock ticks (jiffy) per second: 100
    number of open files : 1024
    size of a page in bytes: 4096
    total number of pages in the physical memory: 1973874
    number of currently available pages in the physical memory: 332748

==============================================================================================================================
*/