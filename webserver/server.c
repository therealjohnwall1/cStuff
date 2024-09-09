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
pthread_t pool[THREAD_CT];


void clientConnection(int clientFd) {
    // load client req into buffer
    char clientMsg[256] = {0}; 
    int rec = recv(clientFd, &clientMsg, 256, 0);

    if (rec >= 0) {
        printf("received\n");
    }
    char* file = clientMsg + 5;
    *strchr(file, ' ') = 0; // null term

    // actual file client requests
    int openFd = open(file, O_RDONLY);  

    if (openFd < 0) {
        perror("open failed");
        close(clientFd);
        return;
    }
    
    char* stuff = 
        "HTTP/1.1 200 Success\r\n"
        "Content-Type: text/html\r\n\r\n";
    
    int res = write(clientFd, stuff, strlen(stuff));
    if(res != (int)strlen(stuff)){
        exit(1);
    }

    sendfile(clientFd, openFd, 0, 256);
    close(clientFd);
    close(openFd);
}

// threadpool version
void* threadCreate(void *vargp) {
    while (1) {
        int curr;
        pthread_mutex_lock(&mutex);

        // no null, just use neg
        while ((curr = pop()) == -1) {
            pthread_cond_wait(&cond, &mutex);
        }

        pthread_mutex_unlock(&mutex);
        if (curr != -1) {
            clientConnection(curr);
        }
    }

    return NULL;
}

int main(void) {
    // init queue
    q = (workQueue*) malloc(sizeof(workQueue));
    q->head = NULL;
    q->tail = NULL;

    // init semaphore
    /*sem_init(&sema, 0, 1);*/

    // init thread pool first
    for (int i = 0; i < THREAD_CT; i++) {
        pthread_create(&pool[i], NULL, threadCreate, NULL); 
    }

    struct sockaddr_in sockaddr; 
    memset((char *)&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(hostPort);
    sockaddr.sin_addr.s_addr = INADDR_ANY;
    // int bindIP = inet_pton(AF_INET, hostIP, &sockaddr.sin_addr);
    // if (bindIP <= 0) {
    //     if (bindIP == 0) {
    //         perror("does not contain string with valid address");
    //     }
    //     else {
    //         perror("no valid addr family");
    //     }
    //     exit(1);
    // }
    
    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(1);
    }
    
    int bindSuc = bind(sockfd, (struct sockaddr*) &sockaddr, sizeof(sockaddr));
    if (bindSuc == -1) {
       perror("cannot bind socket, check port");
       exit(1);
    } 

    if (listen(sockfd, BACKLOG_AMT) < 0) {
        perror("listen failed");
        exit(1);
    }

    while (1) {
        int clientFd = accept(sockfd, NULL, NULL);
        printf("accepted %d\n", clientFd);
        if (clientFd < 0) {
            perror("accept failed");
            continue;
        }
        pthread_mutex_lock(&mutex);
        // printf("appending to queue\n");
        append(clientFd);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }

    return 0;
}
