/*
==============================================================================================================================
Name: 28.c
Author: Suchir Okram
Description: Write a program to change the exiting message queue permission. (use msqid_ds structure)
Date: 1st Oct, 2025
==============================================================================================================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<unistd.h>
#include<getopt.h>

static void print_perm(const struct msqid_ds *ds) {
    printf("msg_perm.cuid=%u, msg_perm.cgid=%u, msg_perm.uid=%u, msg_perm.gid=%u, mode=0%o\n",
           (unsigned)ds->msg_perm.cuid,
           (unsigned)ds->msg_perm.cgid,
           (unsigned)ds->msg_perm.uid,
           (unsigned)ds->msg_perm.gid,
           ds->msg_perm.mode & 0777);
}

int main(int argc, char **argv) {
    if(argc < 2) {
        fprintf(stderr, "Usage: %s <msqid> [-m octal_mode] [-u uid] [-g gid]\n", argv[0]);
        return 2;
    }

    int msqid = -1;
    char *endptr = NULL;
    msqid = (int)strtol(argv[1], &endptr, 10);
    if (*endptr != '\0') {
        fprintf(stderr, "Invalid msqid: %s\n", argv[1]);
        return 2;
    }

    int opt;
    int set_md = 0, set_uid = 0, set_gid = 0;
    int new_md = 0;
    uid_t n_uid = 0;
    gid_t n_gid = 0;

    optind = 2;
    while((opt = getopt(argc, argv, "m:u:g:"))!=-1) {
        switch(opt) {
        case('m'):
            errno = 0;
            new_md = (int)strtol(optarg, NULL, 8);
            if(errno != 0) {
                fprintf(stderr, "Invalid mode: %s\n", optarg);
                return 2;
            }
            set_md = 1;
            break;
        case('u'):
            errno = 0;
            n_uid = (uid_t)strtoul(optarg, NULL, 10);
            if(errno != 0) {
                fprintf(stderr, "Invalid uid: %s\n", optarg);
                return 2;
            }
            set_uid = 1;
            break;
        case('g'):
            errno = 0;
            n_gid = (gid_t)strtoul(optarg, NULL, 10);
            if(errno != 0) {
                fprintf(stderr, "Invalid gid: %s\n", optarg);
                return 2;
            }
            set_gid = 1;
            break;
        default:
            fprintf(stderr, "Unknown option\n");
            return 2;
        }
    }

    if(!set_md && !set_uid && !set_gid) {
        fprintf(stderr, "Nothing to change: supply at least -m, -u or -g\n");
        return 2;
    }

    struct msqid_ds ds;

    if(msgctl(msqid, IPC_STAT, &ds) == -1) {
        fprintf(stderr, "IPC_STAT failed for msqid=%d: %s\n", msqid, strerror(errno));
        return 1;
    }

    printf("Before:\n");
    print_perm(&ds);

    if(set_md) {
        ds.msg_perm.mode = (ds.msg_perm.mode & ~0777)|(new_md & 0777);
    }
    if(set_uid) {
        ds.msg_perm.uid = n_uid;
    }
    if(set_gid) {
        ds.msg_perm.gid = n_gid;
    }
    if(msgctl(msqid, IPC_SET, &ds)==-1) {
        fprintf(stderr, "IPC_SET failed for msqid=%d: %s\n", msqid, strerror(errno));
        return 1;
    }

    if(msgctl(msqid, IPC_STAT, &ds)==-1) {
        fprintf(stderr, "IPC_STAT (after) failed for msqid=%d: %s\n", msqid, strerror(errno));
        return 1;
    }

    printf("After:\n");
    print_perm(&ds);

    return 0;
}
/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q28$ gcc 28.c -o 28
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q28$ ./28
    Usage: ./28 <msqid> [-m octal_mode] [-u uid] [-g gid]
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q28$ ./28 1
    Nothing to change: supply at least -m, -u or -g
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q28$ ./28 1 -m 0640
    Before:
    msg_perm.cuid=1000, msg_perm.cgid=1000, msg_perm.uid=1000, msg_perm.gid=1000, mode=0666
    After:
    msg_perm.cuid=1000, msg_perm.cgid=1000, msg_perm.uid=1000, msg_perm.gid=1000, mode=0640
==============================================================================================================================
*/