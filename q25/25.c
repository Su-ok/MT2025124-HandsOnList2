/*
==============================================================================================================================
Name: 25.c
Author: Suchir Okram
Description: Write a program to print a message queue's (use msqid_ds and ipc_perm structures) 
            a. access permission 
            b. uid, gid 
            c. time of last message sent and received 
            d. time of last change in the message queue 
            e. size of the queue 
            f. number of messages in the queue 
            g. maximum number of bytes allowed 
            h. pid of the msgsnd and msgrcv
Date: 1st Oct, 2025
==============================================================================================================================
*/
#define _POSIX_C_SOURCE 200809L 
#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/types.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
static void print_perms(mode_t mode) {
    char str[10]="---------";
    const mode_t masks[9] = {0400, 0200, 0100,
        0040, 0020, 0010, 
        0004, 0002, 0001};
    for(int i=0; i<9; i++) {
        if(mode & masks[i]) {
            str[i]="rwx"[i%3];
        }
    }
    printf("Access (perm): %s\n", str);
}
static void print_time(time_t t, const char *label) {
    if(t==0) {
        printf("%-28s : (none)\n", label);
        return;
    }
    struct tm tm;
    char buf[64];
    if(!localtime_r(&t, &tm)) {
        printf("%-28s : (invalid time)\n", label);
        return;
    }
    if(strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S %z", &tm)==0)
        strncpy(buf, "(time formatting error)", sizeof(buf));
    printf("%-28s : %s\n", label, buf);
}

struct msg_buffer {
    long mtype;
    char mtext[100];
};
int main(int argc, char *argv[]) {
    key_t k;
    int msqid;
    struct msqid_ds ds;

    if(argc==2) {
        char *end;
        long v=strtol(argv[1], &end, 10);
        if(*end=='\0') {
            msqid=(int)v;
            if(msgctl(msqid, IPC_CREAT, &ds)==-1) {
                fprintf(stderr, "msgctl(IPC_STAT) failed for msqid %d: %s\n", msqid, strerror(errno));
                return 1;
            }
        }
        else {
            k=ftok(argv[1], 'Q');
            if(k==-1) {
                perror("ftok");
                return 1;
            }
            msqid=msgget(k, 0666|IPC_CREAT);
            if(msqid==-1) {
                perror("msgget");
                return 1;
            }
            if(msgctl(msqid, IPC_STAT, &ds)==-1) {
                perror("msgctl");
                return 1;
            }
        }
    }
    else {
        k=ftok(".", 'Q');
        if(k==-1) {
            perror("ftok");
            return 1;
        }
        msqid=msgget(k, 0666|IPC_CREAT);
        if(msqid==-1) {
            perror("msgget");
            return 1;
        }

        //Send a message
        struct msg_buffer msg;
        msg.mtype=1;
        strcpy(msg.mtext, "Hello via msg queue!");
        if(msgsnd(msqid, &msg, sizeof(msg.mtext), 0)==-1) {
            perror("msgsnd");
            return 1;
        }
        sleep(1);
        msgctl(msqid, IPC_STAT, &ds);

        //Receive a message
        struct msg_buffer recv_msg;
        if(msgrcv(msqid, &recv_msg, sizeof(recv_msg.mtext), 1, 0)==-1) {
            perror("msgrcv");
            return 1;
        }
        //Since msgrcv removes the message from the queue, I commented msgctl(msqid, IPC_STAT, &ds);
    }

    printf("Message queue info for msqid = %d\n", msqid);
    printf("-----------------------------------------------\n");

#if defined(__linux__)
    printf("Key (ftok-style): %u\n", (unsigned)ds.msg_perm.__key);
#else
    printf("Key (ftok-style) : (platform-dependent; use ftok separately if needed)\n");
#endif
    print_perms(ds.msg_perm.mode);
    printf("Owner UID: %u", (unsigned)ds.msg_perm.uid);
    struct passwd *pw = getpwuid(ds.msg_perm.uid);
    if(pw) printf(" (%s)", pw->pw_name);
    printf("\n");

    printf("Owner GID: %u", (unsigned)ds.msg_perm.gid);
    struct group *gr = getgrgid(ds.msg_perm.gid);
    if(gr) printf(" (%s)", gr->gr_name);
    printf("\n");

    print_time(ds.msg_stime, "Time of last message sent: ");
    print_time(ds.msg_rtime, "Time of last message received: ");
    print_time(ds.msg_ctime, "Time of last change in the message queue: ");

    printf("Size of the queue: %lu\n", (unsigned long)ds.__msg_cbytes);
    printf("Number of messages in queue: %lu\n", (unsigned long)ds.msg_qnum);
    printf("Maximum number of bytes allowed: %lu\n", (unsigned long)ds.msg_qbytes);

    printf("PID of the msgsnd: %d\n", ds.msg_lspid);
    printf("PID of the msgrcv: %d\n", ds.msg_lrpid);

    printf("--------------------------------------------------\n");
    return 0;
}
/*
==============================================================================================================================
SAMPLE OUTPUT: 
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q25$ gcc 25.c -o 25
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q25$ ./25
    Message queue info for msqid = 0
    -----------------------------------------------
    Key (ftok-style): 1359418960
    Access (perm): rw-rw-rw-
    Owner UID: 1000 (suchir-okram)
    Owner GID: 1000 (suchir-okram)
    Time of last message sent:   : 2025-10-01 11:43:29 +0530
    Time of last message received:  : 2025-10-01 11:41:24 +0530
    Time of last change in the message queue:  : 2025-10-01 10:59:29 +0530
    Size of the queue: 100
    Number of messages in queue: 1
    Maximum number of bytes allowed: 16384
    PID of the msgsnd: 6300
    PID of the msgrcv: 6273
    --------------------------------------------------
==============================================================================================================================
*/