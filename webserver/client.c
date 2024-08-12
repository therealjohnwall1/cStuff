#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include "client.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include<string.h>
#include <arpa/inet.h>

int clientSend(char* SERVER) {
    int sockfd;
    struct sockaddr_in serv_addr;

    // AF_INET -> IPV4, SOCK_STREAM,0 -> TCP
    sockfd = socket(AF_INET, SOCK_STREAM,0);

    if (sockfd < 0){
        perror("connection failed\n");
        exit(1);
    }

    // resolve hostname
    struct hostent *server;
    server = gethostbyname(SERVER);

    if (server == NULL) {
        fprintf(stderr, "Error, no host");
        exit(1);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(cPort);

    int result = inet_pton(AF_INET, SERVER, &serv_addr.sin_addr);
    if (result <= 0) {
            if (result == 0) {
                fprintf(stderr, "inet_pton error: Invalid IP address format\n");
            } else {
                perror("inet_pton error");
            }
            exit(1);
        } 

    // connect to server
    if(connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("connection failed");
        close(sockfd);
        exit(1);
    }

    //send GET request
    char request[1024];
    sprintf(request, "GET /%s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", targFile, SERVER);
    if (send(sockfd, request, strlen(request), 0) < 0) {
            perror("send failed");
            close(sockfd);
            exit(1);

    }

    // receive response
    char response [4096];
    int bytes_received;

    while ((bytes_received = recv(sockfd, response, sizeof(response) - 1, 0)) > 0) {
        response[bytes_received] = '\0';
        printf("%s", response);
    }

    if (bytes_received < 0) {
        perror("recv failed");
    }
    
    // display server response
    int MAXLINE = 1000;
    int n;
    char recvline [MAXLINE];
    memset(recvline, 0, MAXLINE);
    
    while((n=read(sockfd, recvline, MAXLINE))) {

        printf("%s", recvline);
    }
    close(sockfd);
    
    return 1;
}





