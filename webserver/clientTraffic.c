#include "client.h"
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

#define requestsAtOnce 10

// make a bunch of clients to spam requests to test concurrency of server

void* threadCreate(void* argp) {
    int pid = getpid(); 

    if (clientSend(hostIP) == 1){
        printf("sent request from pid %d\n", pid);
    }
}


int main(void) {
	int i;
	pthread_t tids[requestsAtOnce];;

	for (i = 0; i < requestsAtOnce; i++) {
		printf("starting thread");
		pthread_create(&tids[i], NULL, threadCreate, NULL);
	}

	for (i = 0; i < requestsAtOnce; i++) {
		pthread_join(tids[i], NULL);
	}
	return 0;
}
    

