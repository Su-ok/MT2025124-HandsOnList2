/*
==============================================================================================================================
Name: 34a.c
Author: Suchir Okram
Description: Write a program to create a concurrent server.
            a. use fork
Date: 1st Oct, 2025
==============================================================================================================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#define PORT 8080

int main() {
    int server_fd, new_sckt;
    struct sockaddr_in adrss;
    int adrsslen = sizeof(adrss);
    char buf[1024] = {0};
    const char *greet = "Greetings from server\n";

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    adrss.sin_family = AF_INET;
    adrss.sin_addr.s_addr = INADDR_ANY;
    adrss.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&adrss, sizeof(adrss));

    listen(server_fd, 3) ;

    while(1) {
        new_sckt = accept(server_fd, (struct sockaddr *)&adrss, (socklen_t*)&adrsslen);
        if(fork()==0) {
            read(new_sckt, buf, 1024);
            printf("Client: %s\n", buf);
            send(new_sckt, greet, strlen(greet), 0);
            close(new_sckt);
            exit(0);
        }
    }
    return 0;
}

/*
==============================================================================================================================
SAMPLE OUTPUT:
    Terminal 1(before establishing telnet session):
        suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q34$ gcc 34a.c -o 34a
        suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q34$ ./34a

    Terminal 2(telnet session):
        suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2$ telnet localhost 8080
        Trying 127.0.0.1...
        Connected to localhost.
        Escape character is '^]'.
        Hello! Greetings from MT2025124-Suchir Okram.
        Greetings from server

    Terminal 1(after establishing telnet session):
        suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q34$ ./34a
        Client: Hello! Greetings from MT2025124-Suchir Okram.


    // using escape character by pressing 'Ctrl + ]', typing 'quit', then pressing 'Enter' to end session
    Terminal 2:
        Trying 127.0.0.1...
        Connected to localhost.
        Escape character is '^]'.
        Hello! Greetings from MT2025124-Suchir Okram.
        Greetings from server^]
        telnet> quit
        Connection closed.

==============================================================================================================================
*/