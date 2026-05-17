#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

/***********************************
* queue API functions
************************************/
typedef struct queue_s {
    int *buff;
    int size;
    int head;
    int tail;
} queue_t;

bool queue_empty(queue_t *q) {
    return q->head == q->tail;
}

bool queue_full(queue_t *q) {
    return ((q->head + 1) % q->size) == q->tail;
}

int queue_push(queue_t *q, int num) {
    if(queue_full(q))
        return -1;

    q->head = (q->head + 1) % q->size;

    q->buff[q->head] = num;
    return 0;
}

int queue_pop(queue_t *q, int *num) {
    if(queue_empty(q))
        return -1;

    *num = q->buff[q->tail];
    q->tail = (q->tail + 1) % q->size;

    return 0;
}

queue_t *queue_init(int size) {
    queue_t *q = malloc(sizeof(queue_t));
    q->size = size;
    q->tail = 0;
    q->head = 0;
    q->buff = malloc(sizeof(int) * size);
    return q;
}

void queue_destroy(queue_t *q) {
    free(q->buff);
    free(q);
}

/***********************************
* producer & consumer functions
************************************/

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *producer_fn(void *args) {
    const int num_number = 20;
    int num_to_print[num_number];

    // Fill the array
    printf("Producer: Numers to send:\n\t");
    for(int i = 0; i < num_number; i++) {
        num_to_print[i] = rand() % 100;
        printf("%d-", num_to_print[i]);
    }
    printf("\n");

    queue_t *q = (queue_t*)args;
    for(int i = 0; i < num_number; i++) {
        pthread_mutex_lock(&lock);
        int ret = queue_push(q, num_to_print[i]);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
        int time = rand() % 3;
        printf("Producer: Push number %d into the queue\n", num_to_print[i]);
        sleep(time);
    }
    return NULL;
}

void *consumer_fn(void *args) {
    queue_t *q = (queue_t *)args;
    
    while(1) {
        int num;
        pthread_mutex_lock(&lock);
        pthread_cond_wait(&cond, &lock);
        int ret = queue_pop(q, &num);
        pthread_mutex_unlock(&lock);
        
        printf("Consumer: Get numer %d\n", num);

        sleep(rand() % 2);
    }
    return NULL;
}

int main() {
    pthread_t consumer, producer;
    queue_t *q = queue_init(10);

    pthread_create(&consumer, NULL, consumer_fn, q);
    pthread_create(&producer, NULL, producer_fn, q);

    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    printf("All workers done!");

    return 0;
}