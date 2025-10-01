/*
==============================================================================================================================
Name: 33client.c
Author: Suchir Okram
Description: Write a program to communicate between two machines using socket.
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
    int sock=0;
    struct sockaddr_in srv_adrs;
    char buf[1024]={0};

    sock = socket(AF_INET, SOCK_STREAM, 0);

    srv_adrs.sin_family = AF_INET;
    srv_adrs.sin_port = htons(PORT);

    inet_pton(AF_INET, "127.0.0.1", &srv_adrs.sin_addr);

    connect(sock, (struct sockaddr *)&srv_adrs, sizeof(srv_adrs));

    read(sock, buf, sizeof(buf));
    printf("Message from server: %s\n", buf);

    close(sock);
    return 0;
}

/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q33$ gcc 33client.c -o client
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q33$ ./client
    Message from server: Greetings message from the server.
==============================================================================================================================
*/