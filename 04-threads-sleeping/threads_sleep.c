#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_TIME 5

void *thread_cb(void * args) {
    int time = rand()%MAX_TIME;
    printf("Worker %d: starting, will work for %ds\n", *(int*)args, time);
    sleep(time);
    printf("Worker %d: done!", *(int*)args);
    return NULL;
}

int main() {
    const int thread_nb = 3;
    pthread_t threads[thread_nb];
    int thread_count[thread_nb];
    for(int i = 0; i < thread_nb; i++) {
        thread_count[i] = i;
        pthread_create(&threads[i], NULL, thread_cb, &thread_count[i]);
    }

    for(int i = 0; i < thread_nb; i++)
        pthread_join(threads[i], NULL);

    printf("All workers done!\n");
    return 0;
}