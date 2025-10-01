/*
==============================================================================================================================
Name: 12.c
Author: Suchir Okram
Description: Write a program to create an orphan process. Use kill system call to send SIGKILL signal to
                the parent process from the child process.
Date: 1st Oct, 2025
==============================================================================================================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
int main() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        printf("Child process (PID: %d), killing parent (PID: %d)\n", getpid(), getppid());
        kill(getppid(), SIGKILL); 
        sleep(2);
        printf("Child process (PID: %d) is now orphan, adopted by init (PID: %d)\n", getpid(), getppid());
    } else {
        sleep(10);
    }    
    return 0;
}
/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q12$ gcc 12.c -o 12
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q12$ ./12
    Child process (PID: 18851), killing parent (PID: 18850)
    Killed
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q12$ Child process (PID: 18851) is now orphan, adopted by init (PID: 2749)

==============================================================================================================================
*/