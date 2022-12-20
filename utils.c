#include "utils.h"

//function measure time and return value in nanoSec
// The function was adapted from: https://www.educba.com/clock_gettime/
long returnTimeNs() {
    struct timespec currTime;
    if (clock_gettime(CLOCK_REALTIME, &currTime) == -1) {
        perror("clock gettime");
    }
    return currTime.tv_nsec;
}