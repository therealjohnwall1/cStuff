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
#include <string.h>
/*#include <semaphore.h>*/

#include "queue.h"

#define hostPort 6969
#define hostIP "127.0.0.1" 
#define BACKLOG_AMT 50 // amt of pending connections to socket
#define THREAD_CT 10 

// stuff for threading 
/*sem_t sema;*/
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t pool [THREAD_CT];
workQueue* queue;

// param = fd of client socket 
void clientConnection(int* clientFdP) {
    int clientFd = *clientFdP;
    int pid = getpid(); // for debugging 
    printf("new thread running: pid: %d\n", pid);
    /*int* clientP = (int*) vargp;*/
    /*int clientFd = *clientP;*/

    // load client req into buffer
    char clientMsg [256] = {0}; 
    int rec = recv(clientFd, &clientMsg, 256, 0);

    if (rec >=0) {
        printf("receives\n");
    }

    // GET /..file.html or something idk
    // skip 5 bytes to hop to file, change later 

    char* file = clientMsg + 5;
    *strchr(file, ' ') = 0; // null term

    // actual file client requests
    int openFd= open(file, O_RDONLY);  
    printf(" sent file to client\n");

    sendfile(clientFd, openFd, 0,256);
    close(clientFd);
    close(openFd);
}

// threadpool version
void* threadCreate(void *vargp) {
    while(1) {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex);
        int* curr = pop(queue); 
        pthread_mutex_unlock(&mutex);
        
        if (curr != NULL) {
            clientConnection(curr);
        }
    }
}

int main(void) {
    // init queue
    queue = (workQueue*) malloc(sizeof(workQueue*));
    queue->head = NULL;
    queue->tail = NULL;

    // init semaphore
    /*sem_init(&sema, 0, 1);*/

    //init thread pool first
    for(int i = 0; i < THREAD_CT; i++ ) {
        pthread_create(&pool[i], NULL, threadCreate, NULL); 
    }

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

    listen(sockfd, BACKLOG_AMT);

    while (1) {
        // pointer allows each thread to have their own client
        int* clientFd = (int*) malloc(sizeof(int));
        *clientFd = accept(sockfd, 0, 0);
        pthread_mutex_lock(&mutex);
        pthread_cond_signal(&cond);
        append(queue, *clientFd);
        pthread_mutex_unlock(&mutex);
    }
    return 0;
}

