/*
==============================================================================================================================
Name: 30.c
Author: Suchir Okram
Description: Write a program to create a shared memory.
            a. write some data to the shared memory
            b. attach with O_RDONLY and check whether you are able to overwrite.
            c. detach the shared memory
            d. remove the shared memory
Date: 1st Oct, 2025
==============================================================================================================================
*/
#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<signal.h>
#include<setjmp.h>
#define SHM_SIZE 1024

static sigjmp_buf env;
void segv_handler(int sno) {
    printf("Caught SIGSEGV: write protection works!\n");
    siglongjmp(env,1);
}

int main() {
    key_t k = IPC_PRIVATE;
    int shmid;
    char *d;

    // Create shared memory
    shmid = shmget(k, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget failed");
        exit(EXIT_FAILURE);
    }
    printf("Shared memory created with shmid = %d\n", shmid);
    d = (char *)shmat(shmid, NULL, 0);
    if(d == (char *)-1) {
        perror("shmat RW failed");
        exit(EXIT_FAILURE);
    }

    // a. Write some data to the shared memory
    const char *msg="Hello from shared memory!";
    strncpy(d, msg, SHM_SIZE);
    printf("Wrote to shared memory: %s\n", msg);

    // b. Attach with O_RDONLY
    char *ro_d=(char *)shmat(shmid, NULL, SHM_RDONLY);
    if(ro_d==(char *)-1) {
        perror("shmat RO failed");
        exit(EXIT_FAILURE);
    }

    printf("Read from shared memory (RO attach): %s\n", ro_d);

    signal(SIGSEGV, segv_handler);

    // Trying to overwrite
    if(sigsetjmp(env,1)==0) {
        printf("Attempting to overwrite in RO attach...\n");
        fflush(stdout);
        ro_d[0] = 'X';
        printf("Unexpected: write succeeded!\n");
    }
    else {
        printf("Continuing after catching SIGSEGV.\n");
    }

    // c. Detach the shared memory
    if(shmdt(d)==-1) {
        perror("shmdt RW failed");
    } 
    else {
        printf("Detached RW successfully.\n");
    }

    if(shmdt(ro_d) == -1) {
        perror("shmdt RO failed");
    }
    else {
        printf("Detached RO successfully.\n");
    }

    // d. Remove the shared memory
    if(shmctl(shmid, IPC_RMID, NULL)==-1) {
        perror("shmctl(IPC_RMID) failed");
        exit(EXIT_FAILURE);
    }

    printf("Shared memory removed successfully.\n");
    return 0;
}

/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q30$ ipcs -m

    ------ Shared Memory Segments --------
    key        shmid      owner      perms      bytes      nattch     status      
    0x00000000 5          suchir-okr 600        524288     2          dest         
    0x00000000 10         suchir-okr 606        5784480    2          dest         
    0x00000000 11         suchir-okr 606        5784480    2          dest         

    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q30$ gcc 30.c -o 30
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q30$ ./30
    Shared memory created with shmid = 16
    Wrote to shared memory: Hello from shared memory!
    Read from shared memory (RO attach): Hello from shared memory!
    Attempting to overwrite in RO attach...
    Caught SIGSEGV: write protection works!
    Continuing after catching SIGSEGV.
    Detached RW successfully.
    Detached RO successfully.
    Shared memory removed successfully.
==============================================================================================================================
*/