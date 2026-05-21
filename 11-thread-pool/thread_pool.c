#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include "task_collection.h"

typedef struct s_task {
    void (*task)(int);
    int arg;
} task_t;

#define POOL_SIZE 4
#define QUEUE_SIZE 20

typedef struct queue_s {
    int front;
    int last;
    int size;
    int full;
    task_t *buff;
} queue_t;

void queue_init(queue_t *q, int size) {
    q->front = q->last = q->full = 0;
    q->size = size;
    q->buff = malloc(sizeof(task_t) * size);
}

bool queue_empty(queue_t *q) {
    return q->front == q->last;
}

void queue_push(queue_t *q, task_t task) {
    printf("queue push\n");
    q->buff[q->front] = task;
    q->front = (q->front + 1) % q->size;
}

task_t queue_pop(queue_t *q) {
    task_t task;
    printf("queue pop\n");
    if(!queue_empty(q)) {
        task = q->buff[q->last];
        q->last = (q->last + 1) % q->size;
    }
    return task;
}

void queue_destroy(queue_t *q) {
    free(q->buff);
}

typedef struct thread_pool_s {
    pthread_t workers[POOL_SIZE];
    queue_t queue;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    bool shutdown;
} thread_pool_t;

thread_pool_t thread_pool;

void *thread_func(void *args) {
    printf("Worker %d start performing tasks\n", *(int *)args);
    while(1) {
        pthread_mutex_lock(&thread_pool.mutex);
        if(queue_empty(&thread_pool.queue)) {
            printf("Worker %d: queue empty waiting to finish\n", *(int*)args);
            pthread_cond_wait(&thread_pool.cond, &thread_pool.mutex);
            pthread_mutex_unlock(&thread_pool.mutex);
            printf("Worker %d finished its job\n", *(int*)args);
            break;
        }
        task_t task = queue_pop(&thread_pool.queue);
        pthread_mutex_unlock(&thread_pool.mutex);
        sleep(10);
        task.task(task.arg);
    }
    return NULL;
}

void thread_pool_queue_fill(thread_pool_t *pool) {
    queue_init(&pool->queue, QUEUE_SIZE);
    pthread_mutex_init(&pool->mutex, NULL);
    pthread_cond_init(&pool->cond, NULL);
    for(int i = 0; i < QUEUE_SIZE - 4; i++) {
        task_t task;
        task.task = i%2 ? number_sum : number_mult;
        task.arg = i;
        queue_push(&pool->queue, task);
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
    // Need to fix this signal
    pthread_cond_signal(&thread_pool.cond);
    printf("All workers are done!\n");
    return 0;
}