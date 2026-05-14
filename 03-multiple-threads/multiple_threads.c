#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void *thread_cb(void *args) {
    printf("I am thread %d\n", *(int*)args);
    return NULL;
}

int main() {
    const int thread_nb = 5;
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