#include <stdio.h>
#include <pthread.h>

unsigned long long global_ctr;

pthread_mutex_t mutex;

void *thread_func(void *args) {
    pthread_mutex_lock(&mutex);
    for(int i = 0; i < 100000; i++)
        global_ctr++;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    const int threads_num = 10;
    pthread_t threads[threads_num];

    for(int i = 0; i < threads_num; i++)
        pthread_create(&threads[i], NULL, thread_func, NULL);

    for(int i = 0; i < threads_num; i++)
        pthread_join(threads[i], NULL);

    printf("All workers done!\nglobal counter = %llu\n", global_ctr);    
    return 0;
}