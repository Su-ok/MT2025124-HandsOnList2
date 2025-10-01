/*
==============================================================================================================================
Name: 29.c
Author: Suchir Okram
Description: Write a program to remove the message queue.
Date: 1st Oct, 2025
==============================================================================================================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
int main(int argc, char *argv[]) {
    if(argc!=2) {
        fprintf(stderr, "Usage: %s <msqid>\n", argv[0]);
        return 2;
    }

    int msqid=atoi(argv[1]);
    if(msgctl(msqid, IPC_RMID, NULL)==-1) {
        perror("msgctl(IPC_RMID) failed");
        return 1;
    }

    printf("Message queue %d removed successfully.\n", msqid);
    return 0;
}
/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q29$ gcc 29.c -o 29
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q29$ ipcs -q

    ------ Message Queues --------
    key        msqid      owner      perms      used-bytes   messages    
    0x51071650 0          suchir-okr 666        0            0           
    0x510766cd 1          suchir-okr 640        0            0           
    0x51071651 2          suchir-okr 666        0            0           

    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q29$ ./29 1
    Message queue 1 removed successfully.
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q29$ ipcs -q

    ------ Message Queues --------
    key        msqid      owner      perms      used-bytes   messages    
    0x51071650 0          suchir-okr 666        0            0           
    0x51071651 2          suchir-okr 666        0            0
==============================================================================================================================
*/