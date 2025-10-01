/*
==============================================================================================================================
Name: 26.c
Author: Suchir Okram
Description: Write a program to send messages to the message queue. Check $ipcs -q
Date: 1st Oct, 2025
==============================================================================================================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<errno.h>
struct msg_buffer {
    long mtype;
    char mtext[100];
};

int main() {
    key_t k;
    int msgid;
    k = ftok(".", 'Q');
    if(k==-1) {
        perror("ftok");
        exit(1);
    }

    msgid = msgget(k, 0666 | IPC_CREAT);
    if(msgid==-1) {
        perror("msgget");
        exit(1);
    }

    struct msg_buffer msg;
    msg.mtype = 1;
    strcpy(msg.mtext, "Hello from message queue. Nice to meet you!");

    if(msgsnd(msgid, &msg, sizeof(msg.mtext), 0)==-1) {
        perror("msgsnd");
        exit(1);
    }

    printf("Message sent successfully to queue with ID: %d\n", msgid);
    printf("Check with: ipcs -q\n");

    return 0;
}
/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q26$ gcc 26.c -o 26
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q26$ ./26
    Message sent successfully to queue with ID: 2
    Check with: ipcs -q
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q26$ ipcs -q

    ------ Message Queues --------
    key        msqid      owner      perms      used-bytes   messages    
    0x51071650 0          suchir-okr 666        0            0           
    0x510766cd 1          suchir-okr 666        0            0           
    0x51071651 2          suchir-okr 666        100          1
==============================================================================================================================
*/