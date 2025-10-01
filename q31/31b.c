/*
==============================================================================================================================
Name: 31b.c
Author: Suchir Okram
Description: Write a program to create a semaphore and initialize value to the semaphore.
            a. create a counting semaphore
Date: 1st Oct, 2025
==============================================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main() {
    key_t k;
    int semid;
    union semun arg;

    k=ftok(".", 85);
    if (k==-1) {
        perror("ftok failed");
        exit(EXIT_FAILURE);
    }

    semid=semget(k, 1, IPC_CREAT | 0666);
    if (semid==-1) {
        perror("semget failed");
        exit(EXIT_FAILURE);
    }
    printf("Semaphore created with semid: %d\n", semid);

    arg.val = 10;
    if (semctl(semid, 0, SETVAL, arg) == -1) {
        perror("semctl SETVAL failed");
        exit(EXIT_FAILURE);
    }
    printf("Semaphore initialized to 10\n");

    return 0;
}
/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q31$ gcc 31b.c -o 31b
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q31$ ./31b
    Semaphore created with semid: 1
    Semaphore initialized to 10
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q31$ ipcs -s

    ------ Semaphore Arrays --------
    key        semid      owner      perms      nsems     
    0x4b0715e0 0          suchir-okr 666        1         
    0x550715e0 1          suchir-okr 666        1         

    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q31$ ipcs -si 1

    Semaphore Array semid=1
    uid=1000	 gid=1000	 cuid=1000	 cgid=1000
    mode=0666, access_perms=0666
    nsems = 1
    otime = Not set                   
    ctime = Wed Oct  1 19:10:11 2025  
    semnum     value      ncount     zcount     pid       
    0          10         0          0          12226
==============================================================================================================================
*/