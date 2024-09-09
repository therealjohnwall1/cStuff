#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

int g = 0;

// The function to be executed by all threads
void* myThreadFun(void* vargp)
{
    // Store the value argument passed to this thread
    int myid = getpid();

    // Let us create a static variable to observe its
    // changes
    static int s = 0;

    // Change static and global variables
    ++s;
    ++g;

    // Print the argument, static and global variables
    printf("Thread ID: %d, Static: %d, Global: %d\n", myid,
           ++s, ++g);
}

int main()
{
    int i;
    pthread_t tid;

    for (i = 0; i < 10; i++)
        pthread_create(&tid, NULL, myThreadFun, NULL);

    pthread_exit(NULL);
    return 0;
}

