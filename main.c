#include "utils.h"

void emptyThreadFunc();


/*In the code below - the main thread creates a new thread,
 which acquires the mutexCond, does some work, and then releases the mutexCond.
 The main thread waits for the new thread to finish and then destroys the mutexCond.*/
int main() {
    // All functions below were adapted from the code from: https://chat.openai.com/chat
    emptyThreadFunc();
    mutexFunc();
    fcntlFunc();
    condFunc();
    pipeFunc();
    return 0;
}


void *threadFuncWithOutLockMutex(void *arg) {
    return NULL;
}



void emptyThreadFunc() {
    pthread_mutex_t mutex;
    long startTime = returnTimeNs();
    for (int i = 0; i < NUM_OF_ITERATIONS; i++) {
        // Create a new thread
        pthread_t thread;
        pthread_create(&thread, NULL, threadFuncWithOutLockMutex, NULL);

        // Wait for the thread to finish
        pthread_join(thread, NULL);
    }
    long endTime = returnTimeNs();
    long timeDiff = endTime - startTime;
    if (timeDiff < 0) timeDiff *= -1;
    printf("Time taken for threads without  mutexCond lock 1M times: %ld\n", timeDiff);

    // Destroy the mutexCond
    pthread_mutex_destroy(&mutex);
}