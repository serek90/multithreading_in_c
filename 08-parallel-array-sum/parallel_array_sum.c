#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

typedef struct thread_args
{
    int *arr;
    int start;
    int end;
    long long partial_sum;
} thread_args_t;

void *arr_sum(void *args) {
    thread_args_t *th_arg = args;

    int start = th_arg->start;
    while(start < th_arg->end) {
        th_arg->partial_sum += th_arg->arr[start];
        start++;
    }
    return NULL;
}

int main() {
    const int threads_num = 20;
    pthread_t threads[threads_num];
    thread_args_t th_args[threads_num];
    const int array_size = 100000000;
    int *array = malloc(array_size * sizeof(int));

    for(int i = 0; i < array_size; i++)
        array[i] = rand()%100;
    
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for(int i = 0; i < threads_num; i++) {
        th_args[i].arr = array;
        th_args[i].start = array_size / threads_num * i;
        th_args[i].end= array_size / threads_num * (i + 1);
        th_args[i].partial_sum = 0;
        pthread_create(&threads[i], NULL, arr_sum, &th_args[i]);
    }

    for(int i = 0; i < threads_num; i++)
        pthread_join(threads[i], NULL);

    clock_gettime(CLOCK_MONOTONIC, &end);
    unsigned long long sum = 0;
    for(int i = 0; i < threads_num; i++) {
        printf("Thread %d partial sum: %llu\n", i, th_args[i].partial_sum);
        sum += th_args[i].partial_sum;
    }

    printf("Final sum: %llu\n", sum);

    double elapsed =
    (end.tv_sec - start.tv_sec) +
    (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Execution time: %f seconds\n", elapsed);

    return 0;
}