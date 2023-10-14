#define TEST "sched_yield A"
#define BEGIN() \
    sleep(5); \
    int fd; \
    if((fd = open("./xaa", O_RDWR)) == -1){ \
        perror("open"); \
        return EXIT_FAILURE; \
    } \
    char *map; \
    if((map = mmap((void *)0x0000700000000000, 1<<26, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == (void *)-1){ \
        perror("mmap"); \
        return EXIT_FAILURE; \
    } \
    for(char *p = map; p < map + (1<<26); p++){ \
        *p = 'x'; \
    }
#define HOT() \
    sched_yield();
#define END() 0
#define NUM_ITER (1<<26)

#define _GNU_SOURCE
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <harness.c>
