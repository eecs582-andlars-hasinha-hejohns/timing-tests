#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <sys/auxv.h> // vdso
#include <dlfcn.h> // dlopen
#include <time.h>
#include <sched.h>

int NUM_ITER = 1<<30;

int main(){
    struct timespec start;
    struct timespec end;
    if(clock_gettime(CLOCK_MONOTONIC, &start)){
        perror("clock_gettime");
        return EXIT_FAILURE;
    }
    for(int i = 0; i < NUM_ITER; i++){
        getcpu(NULL, NULL);
    }
    if(clock_gettime(CLOCK_MONOTONIC, &end)){
        perror("clock_gettime");
        return EXIT_FAILURE;
    }
    double t1 = (end.tv_sec - start.tv_sec) + ((end.tv_nsec - start.tv_nsec) / 1e9);
    double t2 = (1e9 * (end.tv_sec - start.tv_sec)) + (end.tv_nsec - start.tv_nsec);
    printf("[getcpu] total time: %f seconds \naverage time: %f nanoseconds\n", t1, t2 / NUM_ITER);
    return EXIT_SUCCESS;
}
