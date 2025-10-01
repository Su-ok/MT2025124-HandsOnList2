/*
==============================================================================================================================
Name: 32d.c
Author: Suchir Okram
Description: Write a program to implement semaphore to protect any critical section.
            d. remove the created semaphore
Date: 1st Oct, 2025
==============================================================================================================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/sem.h>
int main(int argc, char *argv[]) {
    if(argc!=2) {
        fprintf(stderr, "Usage: %s <semid>\n", argv[0]);
        exit(1);
    }
    int semid = atoi(argv[1]);
    if(semctl(semid, 0, IPC_RMID)==-1) {
        perror("semctl remove failed");
        exit(1);
    }
    printf("Semaphore %d removed successfully.\n", semid);
    return 0;
}

/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q32$ ipcs -s

    ------ Semaphore Arrays --------
    key        semid      owner      perms      nsems     
    0x4b0715e0 0          suchir-okr 666        1         
    0x550715e0 1          suchir-okr 666        1         

    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q32$ gcc 32d.c -o rmsem
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q32$ ./rmsem
    Usage: ./rmsem <semid>
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q32$ ./rmsem 1
    Semaphore 1 removed successfully.
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q32$ ipcs -s

    ------ Semaphore Arrays --------
    key        semid      owner      perms      nsems     
    0x4b0715e0 0          suchir-okr 666        1 
==============================================================================================================================
*/