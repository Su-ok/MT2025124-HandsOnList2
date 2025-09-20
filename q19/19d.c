/*
==============================================================================================================================
Name: 19d.c
Author: Suchir Okram
Description: Create a FIFO file by
                d. mknod system call
Date: 11th Sep, 2025
==============================================================================================================================
*/
#define _XOPEN_SOURCE 500
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int main() {
    if(mknod("myfifo_syscall", S_IFIFO | 0666, 0)==-1) {
        perror("mknod");
        exit(EXIT_FAILURE);
    }
    printf("FIFO created using mknod system call\n");
    return 0;
}
/*
==============================================================================================================================
SAMPLE OUTPUT: 
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q19$ gcc 19d.c -o 19d
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q19$ ./19d
    FIFO created using mknod system call
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q19$ ls -l
    total 28
    -rw-rw-r-- 1 suchir-okram suchir-okram  5620 Sep 12 10:31 19abc.c
    -rwxrwxr-x 1 suchir-okram suchir-okram 16080 Sep 12 10:37 19d
    -rw-rw-r-- 1 suchir-okram suchir-okram   985 Sep 12 10:37 19d.c
    prw-rw-r-- 1 suchir-okram suchir-okram     0 Sep 12 10:12 Fifotest
    prw-rw-r-- 1 suchir-okram suchir-okram     0 Sep 12 10:14 Fifotest2
    prw-rw-r-- 1 suchir-okram suchir-okram     0 Sep 12 10:02 Myfifo1
    prw-rw-r-- 1 suchir-okram suchir-okram     0 Sep 12 10:03 Myfifo2
    prw-rw-r-- 1 suchir-okram suchir-okram     0 Sep 12 10:37 myfifo_syscall
==============================================================================================================================
*/