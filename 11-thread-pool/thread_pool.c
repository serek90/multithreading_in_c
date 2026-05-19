#include <stdio.h>
#include <pthread.h>

typedef struct s_task {
    void (*task)(int);
    int arg;
} task_t;

#define POOL_SIZE 4
pthread_t thread_pool[POOL_SIZE];

void *thread_func(void *args) {
    return NULL;
}

void thread_run(void) {
    for(int i = 0; i < POOL_SIZE; i++) {
        pthread_create(&thread_pool[i], NULL, thread_func, NULL);
    }

    for(int i = 0; i < POOL_SIZE; i++)
        pthread_join(thread_pool[i], NULL);
}


int main() {
    return 0;
}