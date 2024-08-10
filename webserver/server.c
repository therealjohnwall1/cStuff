#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include<string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/sendfile.h>

#define hostPort 6969
#define hostIP "127.0.0.1" //localhost

int main(void) {
    struct sockaddr_in sockaddr;    
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(hostPort);
    int bindIP = inet_pton(AF_INET,hostIP, &sockaddr.sin_addr);
    if (bindIP > 1){
        if(bindIP == 0){
            perror("does not contain string with valid address");
        }
        else {
            perror("no valid addr family");
        }
        exit(1);
    }
    
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM,0);
    
    int bindSuc = bind(sockfd, (struct sockaddr*) &sockaddr, sizeof(sockaddr));
    if (bindSuc == -1) {
       perror("cannot bind socket, check port");
       exit(1);
    } 
    // 10 -> backlog: queue of pending connections for socket
    int listenSuc = listen(sockfd, 10);

    // fd of client socket
    int clientFd = accept(sockfd, 0, 0);

    // load client req into buffer
    char clientMsg [256]; 
   
    recv(clientFd, &clientMsg, 256, 0);

    // GET /..file.html or something idk
    // skip 5 bytes to hop to file, change later 

    char* file = clientMsg + 5;
    *strchr(file, ' ') = 0; // null term
    
    // actual file client requests
    int openFd= open(file, O_RDONLY);  

    sendfile(clientFd, openFd, 0,256);

    close(clientFd);
    close(sockfd);
    close(openFd);

    return 0;
}




