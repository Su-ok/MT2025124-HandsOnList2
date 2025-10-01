/*
==============================================================================================================================
Name: 32a.c
Author: Suchir Okram
Description: Write a program to implement semaphore to protect any critical section.
            a. rewrite the ticket number creation program using semaphore
Date: 1st Oct, 2025
==============================================================================================================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/wait.h>

union semun { 
    int val; 
    struct semid_ds *buf; 
    unsigned short *array; 
};

void sem_op(int semid, int op) {
    struct sembuf sb = {0, op, 0};
    if (semop(semid, &sb, 1)==-1) { 
        perror("semop"); 
        exit(1); 
    }
}

int main() {
    key_t k= ftok(".", 11);
    int semid;
    union semun arg;

    semid=semget(k, 1, IPC_CREAT | 0666);
    arg.val=1; 
    semctl(semid, 0, SETVAL, arg);

    int tickets = 0;

    for(int i=0; i<3; i++) {
        if(fork()==0) {
            for(int j = 0; j < 2; j++) {
                sem_op(semid, -1);
                int my_ticket = ++tickets;
                printf("Child %d got ticket %d\n", getpid(), my_ticket);
                sem_op(semid, +1);
                sleep(1);
            }
            exit(0);
        }
    }
    while(wait(NULL) > 0);

    semctl(semid, 0, IPC_RMID);
    return 0;
}

/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q32$ gcc 32a.c -o 32a
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q32$ ./32a
    Child 13296 got ticket 1
    Child 13297 got ticket 1
    Child 13298 got ticket 1
    Child 13296 got ticket 2
    Child 13297 got ticket 2
    Child 13298 got ticket 2
==============================================================================================================================
*/