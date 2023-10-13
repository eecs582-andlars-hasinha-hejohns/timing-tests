#define TEST "getcpu-explicit-vdso"
#define BEGIN() \
    void *vdso = dlopen("linux-vdso.so.1", RTLD_NOW); \
    if(!vdso){ \
        dlerror(); \
        return EXIT_FAILURE; \
    } \
    int (*getcpu_)(unsigned int *, unsigned int *) = dlsym(vdso, "__vdso_getcpu"); \
    if(!getcpu_){ \
        dlerror(); \
        return EXIT_FAILURE; \
    } \
    if(getcpu_(NULL, NULL)){ \
        perror("getcpu"); \
        return EXIT_FAILURE; \
    }
#define HOT() \
    getcpu_(NULL, NULL);
#define END() 0
#define NUM_ITER (1<<30)

#define _GNU_SOURCE
#include <dlfcn.h>
#include "getcpu.base.c"
