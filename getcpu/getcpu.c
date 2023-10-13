// measure latency for `getcpu`, which should be a vdso userspace call
#define _GNU_SOURCE
#include <stdlib.h>
#include <time.h>
#include <sched.h>

#include <stdio.h>
#include <assert.h>

#define NUM_ITER (1<<30)

int main(){
    struct sched_param sched;
    if((sched.sched_priority = sched_get_priority_max(SCHED_FIFO)) == -1){
        perror("sched_get_priority_max");
        return EXIT_FAILURE;
    }
    if(sched_setscheduler(0, SCHED_FIFO, &sched) == -1){
        perror("sched_setscheduler");
        return EXIT_FAILURE;
    }
    cpu_set_t cpu_mask;
    CPU_ZERO(&cpu_mask);
    CPU_SET(0, &cpu_mask);
    assert(CPU_COUNT(&cpu_mask) == 1);
    if(sched_setaffinity(0, sizeof(cpu_mask), &cpu_mask)){
        perror("sched_setaffinity");
        return EXIT_FAILURE;
    }
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
