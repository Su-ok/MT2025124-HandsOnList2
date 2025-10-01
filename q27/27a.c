/*
==============================================================================================================================
Name: 27a.c
Author: Suchir Okram
Description: Write a program to receive messages from the message queue.
            a. with 0 as a flag
            b. with IPC_NOWAIT as a flag
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

    k = ftok("/home/suchir-okram/Documents/MT2025124-HOL2/q26/", 'Q');
    if (k == -1) {
        perror("ftok");
        exit(1);
    }

    msgid = msgget(k, 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    struct msg_buffer msg;

    if (msgrcv(msgid, &msg, sizeof(msg.mtext), 0, 0) == -1) {
        perror("msgrcv");
        exit(1);
    }

    printf("Message received (flag=0): %s\n", msg.mtext);
    return 0;
}
/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q27$ gcc 27a.c -o 27a
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q27$ ./27a
    Message received (flag=0): Hello from message queue. Nice to meet you!
==============================================================================================================================
*/