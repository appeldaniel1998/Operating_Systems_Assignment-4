#include "utils.h"

pthread_mutex_t mutexCond;//we create a mutexCond variable 'mutexCond'
pthread_cond_t cond;//we create a condition variable 'cond'
int global_flag = 0;

void* thread_func(void* arg) {
    /*'thread_func' function waits on the condition variable using 'pthread_cond_wait'.
    It will block until the condition variable is signaled.*/
    pthread_mutex_lock(&mutexCond);
    while (global_flag == 0) {
        pthread_cond_wait(&cond, &mutexCond);//when calling pthread_cond_wait, the mutexCond must be locked
    }
    /*
     * The mutexCond is automatically released while the thread is waiting and is reacquired before pthread_cond_wait returns.
     * This is important because it allows other threads to acquire the mutexCond and signal the condition variable while the current thread is waiting.
     */
    pthread_mutex_unlock(&mutexCond);
    return NULL;
}

void condFunc() {
    pthread_t thread;//we create a thread that runs 'thread_func'
    pthread_mutex_init(&mutexCond, NULL);// A destroyed condition variable object can be reinitialized using pthread_cond_init()
    pthread_cond_init(&cond, NULL);

    long startTime = returnTimeNs();
    for(int i = 0; i < NUM_OF_ITERATIONS; i++) {
        pthread_create(&thread, NULL, thread_func, NULL);

        // Set the global flag and signal the condition variable
        pthread_mutex_lock(&mutexCond);
        global_flag = 1;
        pthread_cond_signal(&cond);//This causes the thread to unblock and continue execution.
        pthread_mutex_unlock(&mutexCond);
        pthread_join(thread, NULL);
    }
    long endTime = returnTimeNs();
    long timeDiff = endTime - startTime;
    if (timeDiff < 0) timeDiff *= -1;
    printf("Time taken for cond signal 1M times: %ld\n", timeDiff);

    //destroy the given condition variable specified by cond; the object becomes, in effect, uninitialized.
    pthread_mutex_destroy(&mutexCond);
    pthread_cond_destroy(&cond);
}
