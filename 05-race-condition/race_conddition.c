#include <stdio.h>
#include <pthread.h>

unsigned long long global_ctr;

void *thread_cb(void *args) {
    for(int i = 0; i < 100000; i++)
        global_ctr++;
    return NULL;
}

int main() {
    const int thread_nb = 10;
    pthread_t threads[thread_nb];
    for(int i = 0; i < thread_nb; i++)
        pthread_create(&threads[i], NULL, thread_cb, NULL);

        for(int i = 0; i < thread_nb; i++)
        pthread_join(threads[i], NULL);

    printf("All workers done!\n global counter = %llu\n", global_ctr);    
    return 0;
}