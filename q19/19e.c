/*
==============================================================================================================================
Name: 19e.c
Author: Suchir Okram
Description: Create a FIFO file by
                e. mkfifo library function
Date: 11th Sep, 2025
==============================================================================================================================
*/
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int main() {
    if(mkfifo("myfifo_libfunc", 0666)==-1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }
    printf("FIFO created using mififo library function\n");
    return 0;
}
/*
==============================================================================================================================
SAMPLE OUTPUT: 
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q19$ gcc 19e.c -o 19e
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q19$ ./19e
    FIFO created using mififo library function
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q19$ ls -l
    total 48
    -rw-rw-r-- 1 suchir-okram suchir-okram  5620 Sep 12 10:39 19abc.c
    -rwxrwxr-x 1 suchir-okram suchir-okram 16080 Sep 12 10:37 19d
    -rw-rw-r-- 1 suchir-okram suchir-okram  1815 Sep 12 10:38 19d.c
    -rwxrwxr-x 1 suchir-okram suchir-okram 16088 Sep 12 10:41 19e
    -rw-rw-r-- 1 suchir-okram suchir-okram   965 Sep 12 10:41 19e.c
    prw-rw-r-- 1 suchir-okram suchir-okram     0 Sep 12 10:12 Fifotest
    prw-rw-r-- 1 suchir-okram suchir-okram     0 Sep 12 10:14 Fifotest2
    prw-rw-r-- 1 suchir-okram suchir-okram     0 Sep 12 10:02 Myfifo1
    prw-rw-r-- 1 suchir-okram suchir-okram     0 Sep 12 10:03 Myfifo2
    prw-rw-r-- 1 suchir-okram suchir-okram     0 Sep 12 10:41 myfifo_libfunc
    prw-rw-r-- 1 suchir-okram suchir-okram     0 Sep 12 10:37 myfifo_syscall
==============================================================================================================================
*/