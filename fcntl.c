#include "utils.h"

void fcntlFunc() {
    // Open the file
    int fd = open("file.txt", O_RDWR);

    // Set up the flock structure
    struct flock lock;
    lock.l_type = F_WRLCK;  // Set the type of lock to be a write lock
    lock.l_whence = SEEK_SET;  // Set the lock to start at the beginning of the file
    lock.l_start = 0;  // Offset from l_whence is 0
    lock.l_len = 0;  // Lock the entire file

    long startTime = returnTimeNs();
    for (int i = 0; i < NUM_OF_ITERATIONS; i++) {
        // Perform the lock
        fcntl(fd, F_SETLK, &lock);

        // Unlock the file
        lock.l_type = F_UNLCK;  // Set the type of lock to be an unlock
        fcntl(fd, F_SETLK, &lock);
    }
    long endTime = returnTimeNs();
    long timeDiff = endTime - startTime;
    if (timeDiff < 0) timeDiff *= -1;
    printf("Time taken for fcntl lock 1M times: %ld\n", timeDiff);

    // Close the file
    close(fd);
}