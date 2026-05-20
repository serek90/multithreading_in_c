#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "task_collection.h"

typedef struct s_task {
    void (*task)(int);
    int arg;
} task_t;

#define POOL_SIZE 4
#define QUEUE_SIZE 20

typedef struct thread_pool_s {
    pthread_t workers[POOL_SIZE];
    task_t task_queue[QUEUE_SIZE];
    int queue_idx;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} thread_pool_t;

thread_pool_t thread_pool;

void *thread_func(void *args) {
    printf("Worker %d start performing tasks\n", *(int *)args);
    while(1) {
        pthread_mutex_lock(&thread_pool.mutex);
        int idx = thread_pool.queue_idx;
        // if queue empty, write API to queue
        thread_pool.queue_idx++;
        pthread_mutex_unlock(&thread_pool.mutex);
        sleep(10);
        thread_pool.task_queue[idx].task(idx);
    }
    return NULL;
}

void thread_pool_queue_fill(thread_pool_t *pool) {
    for(int i = 0; i < QUEUE_SIZE; i++) {
        pool->task_queue[i].task = i%2 ? number_sum : number_mult;
        pool->task_queue[i].arg = i;
    }
}

void thread_pool_run(void) {

    int thread_args[POOL_SIZE];

    for(int i = 0; i < POOL_SIZE; i++) {
        thread_args[i] = i;
        pthread_create(&thread_pool.workers[i], NULL, thread_func, &thread_args[i]);
    }

    for(int i = 0; i < POOL_SIZE; i++)
        pthread_join(thread_pool.workers[i], NULL);
}


int main() {
    thread_pool_queue_fill(&thread_pool);
    thread_pool_run();
    return 0;
}