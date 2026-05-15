#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t semaphore;

void *th_print(void *args) {

    printf("Thread %d: waiting for printer...\n", *(int*)args);

    sem_wait(&semaphore);
    printf("Thread %d: printing...\n", *(int*)args);
    sleep(10);
    sem_post(&semaphore);
    printf("Thread %d: finished printing\n", *(int*)args);
    return NULL;
}

int main() {
    const int threads_num = 8;
    pthread_t threads[threads_num];
    int thread_ctr[threads_num];

    sem_init(&semaphore, 0, 2); // Max two the at the same time
    for(int i = 0; i < threads_num; i++) {
        thread_ctr[i] = i;
        pthread_create(&threads[i], NULL, th_print, &thread_ctr[i]);
    }

    for(int i = 0; i < threads_num; i++)
        pthread_join(threads[i], NULL);

    sem_destroy(&semaphore);

    printf("All workers done!");

    return 0;
}