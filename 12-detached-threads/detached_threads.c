#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thread_func(void *args) {
    printf("Starting thread %d\n", *(int *)args);
    sleep(3);
    printf("Finished thread %d\n", *(int *)args);
    return NULL;
}

int main() {
    const size_t threads_num = 5;
    pthread_t threads[threads_num];
    int threads_arg[threads_num];

    for(size_t i = 0; i < threads_num; i++) {
        threads_arg[i] = i;
        pthread_create(&threads[i], NULL, thread_func, &threads_arg[i]);
    }

    sleep(2);

    for(size_t i = 0; i < threads_num; i++) {
        pthread_detach(threads[i]);
    }
    printf("All workers are done!\n");
    return 0;
}