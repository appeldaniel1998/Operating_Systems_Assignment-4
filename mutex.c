#include "utils.h"

pthread_mutex_t mutex;

void *threadFuncWithLockMutex(void *arg) {
    // Acquire the mutexCond
    pthread_mutex_lock(&mutex);

    // Do some work that requires exclusive access to the shared resource

    // Release the mutexCond
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void mutexFunc() {
    // Initialize the mutexCond
    pthread_mutex_init(&mutex, NULL);

    long startTime = returnTimeNs();
    for (int i = 0; i < NUM_OF_ITERATIONS; i++) {
        // Create a new thread
        pthread_t thread;
        pthread_create(&thread, NULL, threadFuncWithLockMutex, NULL);

        // Wait for the thread to finish
        pthread_join(thread, NULL);
    }
    long endTime = returnTimeNs();
    long timeDiff = endTime - startTime;
    if (timeDiff < 0) timeDiff *= -1;
    printf("Time taken for mutexCond lock 1M times: %ld\n", timeDiff);
}