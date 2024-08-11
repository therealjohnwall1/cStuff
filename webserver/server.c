#include <sys/socket.h>
#include <sys/types.h>
#include <sys/sendfile.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include<string.h>

#define hostPort 6969
#define hostIP "127.0.0.1" 
#define BACKLOG_AMT 10 // amt of pending connections to socket


// param = fd of client socket 
void* threadCreate(void *vargp) {
    int pid = getpid(); // for debugging 
    printf("new thread running: pid: %d\n", pid);
    int* clientP = (int*) vargp;
    int clientFd = *clientP;

    // load client req into buffer
    char clientMsg [256] = {0}; 
	

    int rec = recv(clientFd, &clientMsg, 256, 0);

    if (rec >=0) {
        printf("receives");
    }

    // GET /..file.html or something idk
    // skip 5 bytes to hop to file, change later 

    char* file = clientMsg + 5;
    *strchr(file, ' ') = 0; // null term

    // actual file client requests
    int openFd= open(file, O_RDONLY);  
    printf("sent file to client\n");

    sendfile(clientFd, openFd, 0,256);
    close(clientFd);
    close(openFd);
}

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

    int listenSuc = listen(sockfd, BACKLOG_AMT);
	// only use id, don't keep track after thread is finished
    pthread_t tid;
	int ct = 0;
    while (1) {
		// pointer allows each thread to have their own client
		int* clientFd = (int*) malloc(sizeof(int));
        printf("hit");
       *clientFd = accept(sockfd, 0, 0);
        if (*clientFd >= 0) {
            if(pthread_create(&tid, NULL, threadCreate,clientFd)!=0) {
                perror("failed to make thread");
				free(clientFd);
                exit(1);
            }
        }
	pthread_detach(tid);
    }
    return 0;
}



