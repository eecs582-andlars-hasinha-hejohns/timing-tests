#define TEST "sched_yield B"
#define BEGIN() \
    sleep(5);
#define HOT() \
    sched_yield();
#define END() 0
#define NUM_ITER (1<<26)

#define _GNU_SOURCE
#include <unistd.h>
#include <harness.c>
