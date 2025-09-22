/*
==============================================================================================================================
Name: 24.c
Author: Suchir Okram
Description: Write a program to create a message queue and print the key and message queue id.
Date: 22nd Sep, 2025
==============================================================================================================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
int main() {
    key_t k;
    int msgid;
    k=ftok(".", 65);
    if(k==-1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    msgid=msgget(k, 0666|IPC_CREAT);
    if(msgid==-1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    printf("Message Queue created successfully!\n");
    printf("Key: %d\n", k);
    printf("Message Queue ID: %d\n", msgid);
    
    return 0;
}
/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q24$ gcc 24.c -o 24
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q24$ ls
    24  24.c
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q24$ ./24
    Message Queue created successfully!
    Key: 1090983499
    Message Queue ID: 0
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q24$ ipcs -q

    ------ Message Queues --------
    key        msqid      owner      perms      used-bytes   messages    
    0x4107164b 0          suchir-okr 666        0            0
==============================================================================================================================
*/