#define TEST "getpid-implicit-syscall"
#define BEGIN() 0
#define HOT() \
    syscall(__NR_getpid);
#define END() 0
#define NUM_ITER (1<<25)

#define _GNU_SOURCE
#include <sys/syscall.h>
#include <unistd.h>
#include <harness.c>
