/*
==============================================================================================================================
Name: 32c.c
Author: Suchir Okram
Description: Write a program to implement semaphore to protect any critical section.
            c. protect multiple pseudo resources ( may be two) using counting semaphore
Date: 1st Oct, 2025
==============================================================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>

union semun { 
    int val; 
    struct semid_ds *buf; 
    unsigned short *array; 
};

void sem_op(int semid, int op) {
    struct sembuf sb = {0, op, 0};
    if (semop(semid, &sb, 1) == -1) { 
        perror("semop"); 
        exit(1); 
    }
}

int main() {
    key_t k = ftok(".", 33);
    int semid;
    union semun arg;

    semid = semget(k, 1, IPC_CREAT | 0666);
    arg.val = 2; 
    semctl(semid, 0, SETVAL, arg);

    for(int i = 0; i < 4; i++) {
        if(fork() == 0) {
            sem_op(semid, -1);
            printf("Child %d using a resource\n", getpid());
            sleep(2);
            printf("Child %d releasing resource\n", getpid());
            sem_op(semid, +1);
            exit(0);
        }
    }
    while (wait(NULL)>0);

    semctl(semid, 0, IPC_RMID);
    return 0;
}

/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q32$ gcc 32c.c -o 32c
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q32$ ./32c
    Child 13381 using a resource
    Child 13382 using a resource
    Child 13381 releasing resource
    Child 13383 using a resource
    Child 13382 releasing resource
    Child 13384 using a resource
    Child 13383 releasing resource
    Child 13384 releasing resource
==============================================================================================================================
*/