/*
==============================================================================================================================
Name: 32b.c
Author: Suchir Okram
Description: Write a program to implement semaphore to protect any critical section.
            b. protect shared memory from concurrent write access
Date: 1st Oct, 2025
==============================================================================================================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<sys/wait.h>
#define SHM_SIZE 128
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
    key_t k = ftok(".", 22);
    int semid, shmid;
    union semun arg;

    semid = semget(k, 1, IPC_CREAT | 0666);
    arg.val = 1; 
    semctl(semid, 0, SETVAL, arg);

    shmid = shmget(k, SHM_SIZE, IPC_CREAT | 0666);
    char *data = (char*)shmat(shmid, NULL, 0);

    if(fork() == 0) {
        sem_op(semid, -1);
        strcpy(data, "Hello from child 1");
        printf("Child 1 wrote: %s\n", data);
        sem_op(semid, +1);
        exit(0);
    }
    if(fork() == 0) {
        sem_op(semid, -1);
        strcpy(data, "Hello from child 2");
        printf("Child 2 wrote: %s\n", data);
        sem_op(semid, +1);
        exit(0);
    }

    while(wait(NULL)>0);
    printf("Final shared memory content: %s\n", data);

    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);
    return 0;
}

/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q32$ gcc 32b.c -o 32b
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q32$ ./32b
    Child 1 wrote: Hello from child 1
    Child 2 wrote: Hello from child 2
    Final shared memory content: Hello from child 2
==============================================================================================================================
*/