#define TEST "getcpu-implicit-vdso"
#define BEGIN() 0
#define HOT() \
    getcpu(NULL, NULL);
#define END() 0
#define NUM_ITER (1<<30)

#include <harness.c>
