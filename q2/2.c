/*
==============================================================================================================================
Name: 2.c
Author: Suchir Okram
Description: Write a program to print the system resource limits. Use getrlimit system call.
Date: 1st Oct, 2025
==============================================================================================================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/resource.h>
void rsrc_lmt(int resrc, const char *resrc_name) {
    struct rlimit limit;

    if (getrlimit(resrc, &limit) == 0) {
        printf("%s:\n", resrc_name);
        printf("Soft limit: %ld\n", limit.rlim_cur);
        printf("Hard limit: %ld\n\n", limit.rlim_max);
    } 
    else {
        perror("getrlimit failed");
        exit(EXIT_FAILURE);
    }
}
int main() {
    rsrc_lmt(RLIMIT_CPU, "CPU time limit");
    rsrc_lmt(RLIMIT_FSIZE, "File size limit");
    rsrc_lmt(RLIMIT_STACK, "Stack size limit");
    rsrc_lmt(RLIMIT_NOFILE, "Number of open files limit");
    rsrc_lmt(RLIMIT_NPROC, "Number of processes limit");

    return 0;
}

/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q2$ gcc 2.c -o 2
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q2$ ./2
    CPU time limit:
    Soft limit: -1
    Hard limit: -1

    File size limit:
    Soft limit: -1
    Hard limit: -1

    Stack size limit:
    Soft limit: 8388608
    Hard limit: -1

    Number of open files limit:
    Soft limit: 1024
    Hard limit: 1048576

    Number of processes limit:
    Soft limit: 30087
    Hard limit: 30087

==============================================================================================================================
*/