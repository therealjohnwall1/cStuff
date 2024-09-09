#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_THREADS 5

// Declare a semaphore
sem_t semaphore;

void* thread_function(void* arg) {
    int thread_num = *(int*)arg;

    // Wait (decrement) the semaphore
    sem_wait(&semaphore);

    // Critical section
    printf("Thread %d is entering the critical section.\n", thread_num);
    sleep(5);  // Simulate some work in the critical section
    printf("Thread %d is leaving the critical section.\n", thread_num);

    // Signal (increment) the semaphore
    sem_post(&semaphore);

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_nums[NUM_THREADS];

    // Initialize the semaphore with a value of 2 (allowing 2 threads to enter the critical section at once)
    sem_init(&semaphore, 0, 2);

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_nums[i] = i + 1;
        pthread_create(&threads[i], NULL, thread_function, &thread_nums[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the semaphore
    sem_destroy(&semaphore);

    return 0;
}

