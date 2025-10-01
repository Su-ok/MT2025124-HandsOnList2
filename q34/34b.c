/*
==============================================================================================================================
Name: 34b.c
Author: Suchir Okram
Description: Write a program to create a concurrent server.
            b. use pthread_create
Date: 1st Oct, 2025
==============================================================================================================================
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<pthread.h>
#define PORT 8080

void *handle_client(void *sckt_desc) {
    int new_sckt = *(int*)sckt_desc;
    char buf[1024] = {0};
    const char *greet = "Greetings from server";

    read(new_sckt, buf, 1024);
    printf("Client: %s\n", buf);
    send(new_sckt, greet, strlen(greet), 0);
    close(new_sckt);
    free(sckt_desc);
    pthread_exit(NULL);
}

int main() {
    int server_fd, new_sckt;
    struct sockaddr_in adrss;
    int adrsslen = sizeof(adrss);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    adrss.sin_family = AF_INET;
    adrss.sin_addr.s_addr = INADDR_ANY;
    adrss.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&adrss, sizeof(adrss));

    listen(server_fd, 3);

    while(1) {
        new_sckt = accept(server_fd, (struct sockaddr *)&adrss, (socklen_t*)&adrsslen);

        pthread_t thread_id;
        int *new_sock = malloc(sizeof(int));
        *new_sock = new_sckt;
        pthread_create(&thread_id, NULL, handle_client, (void*)new_sock);
    }
    return 0;
}

/*
==============================================================================================================================
SAMPLE OUTPUT:
    Terminal 1(before establishing telnet session):
        suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q34$ gcc 34b.c -o 34b
        suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q34$ ./34b

    Terminal 2(telnet session):
        suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2$ telnet localhost 8080
        Trying 127.0.0.1...
        Connected to localhost.
        Escape character is '^]'.
        Hello 34b.c! Greetings from MT2025124-Suchir Okram.
        Greetings from serverConnection closed by foreign host.

    Terminal 1(after establishing telnet session):
        suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q34$ ./34b
        Client: Hello 34b.c! Greetings from MT2025124-Suchir Okram.

==============================================================================================================================
*/