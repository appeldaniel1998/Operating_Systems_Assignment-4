#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#define NUM_OF_ITERATIONS (1000*1000)

long returnTimeNs();
void fcntlFunc();
void mutexFunc();
void condFunc();
void pipeFunc();