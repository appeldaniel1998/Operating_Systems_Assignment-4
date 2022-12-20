#include "utils.h"

// Pipe file descriptors
int pipefd[2];

void *task() {
    // Send a signal to the task through the pipe
    // a == lock; b == unlock
    write(pipefd[1], "a",1);
    // Do something

    write(pipefd[1], "b",1);
    return NULL;
}

void pipeFunc() {
    //in this main we use a pipe as a simple communication mechanism between the main thread and the task.
    // Create the pipe
    pipe(pipefd);

    long startTime = returnTimeNs();
    for (int i = 0; i < NUM_OF_ITERATIONS; i++) {

        // To send a signal to the task, we use the write function to write a single character to the pipe.
        // This will cause the read function in the task to unblock and return.

        // Start the task
        pthread_t thread;
        pthread_create(&thread, NULL, task, NULL);

        char a;
        read(pipefd[0], &a, 1); //The task waits for a signal by reading from the pipe using the read function.

        char b;
        read(pipefd[0], &b, 1); //The task waits for a signal by reading from the pipe using the read function.

        // Wait for the task to complete
        pthread_join(thread, NULL);
    }
    long endTime = returnTimeNs();
    long timeDiff = endTime - startTime;
    if (timeDiff < 0) timeDiff *= -1;
    printf("Time taken for pipe signal 1M times: %ld\n", timeDiff);

    // Close the pipe
    close(pipefd[0]);
    close(pipefd[1]);
}
