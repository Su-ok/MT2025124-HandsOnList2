/*
==============================================================================================================================
Name: 13b.c
Author: Suchir Okram
Description: Write two programs: first program is waiting to catch SIGSTOP signal, the second program
            will send the signal (using kill system call). Find out whether the first program is able to catch
            the signal or not. (2nd)
Date: 1st Oct, 2025
==============================================================================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
int main() {

    int pid;
    printf("Enter pid of process to stop: \n");
    scanf("%d", &pid);

    printf("Sending SIGSTOP signal to process: %d\n", pid);
    kill(pid, SIGSTOP);

    printf("SIGSTOP signal sent\n");
    printf("Exiting current process (sender)\n");
    return 0;
}
/*
==============================================================================================================================
SAMPLE OUTPUT:
    In terminal 1:
        suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q13$ gcc 13a.c -o 13a
        suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q13$ gcc 13b.c -o 13b
        suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q13$ ./13a
        The PID of process: 19189

        [1]+  Stopped                 ./13a

    In terminal 2:
        suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q13$ ./13b
    Enter pid of process to stop: 
    19189
    Sending SIGSTOP signal to process: 19189
    SIGSTOP signal sent
    Exiting current process (sender)


==============================================================================================================================
*/