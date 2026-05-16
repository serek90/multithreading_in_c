#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdalign.h>
#include <stdint.h>
#include <unistd.h>

#define TRESHOLD (1000000000ULL)
void *th_func(void *args) {
    uint64_t *ctr = (uint64_t *)args;

    for(uint64_t i = 0; i < TRESHOLD; i++)
        *ctr += 1;
    return NULL;
}

int main() {
    uint64_t ctr1 = 0;
    uint64_t ctr2 = 0;

    /* Version 10 times faster, avoiding false sharing */
    long cache_line_size = sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
    //uint64_t alignas(cache_line_size) ctr1 = 0;
    //uint64_t alignas(cache_line_size) ctr2 = 0;

    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, th_func, &ctr1);
    pthread_create(&thread2, NULL, th_func, &ctr2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);


    printf("Size of cache level 1: %ld\n", cache_line_size);
    printf("Counter from thread 0: %lu\n", ctr1);
    printf("Counter from thread 1: %lu\n", ctr2);
    return 0;
}