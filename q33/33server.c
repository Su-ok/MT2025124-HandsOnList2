/*
==============================================================================================================================
Name: 33server.c
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
    int server_fd, new_socket;
    struct sockaddr_in adrss;
    int addrlen = sizeof(adrss);
    char *msg = "Greetings message from the server.";

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    adrss.sin_family = AF_INET;
    adrss.sin_addr.s_addr = INADDR_ANY;
    adrss.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&adrss, sizeof(adrss));

    listen(server_fd, 3);

    printf("Server is listening on port %d...\n", PORT);

    new_socket = accept(server_fd, (struct sockaddr *)&adrss, (socklen_t *)&addrlen); // Accept a client connection

    send(new_socket, msg, strlen(msg), 0);
    printf("Message sent successfully to client.\n");

    close(new_socket);
    close(server_fd);
    return 0;
}

/*
==============================================================================================================================
SAMPLE OUTPUT:
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q33$ gcc 33server.c -o server
    suchir-okram@Suchir-OMEN:~/Documents/MT2025124-HOL2/q33$ ./server
    Server is listening on port 8080...
    Message sent successfully to client.
==============================================================================================================================
*/