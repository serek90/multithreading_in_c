#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_cb(void *args) {
    int *val = args;
    printf("Received value: %d\n", *val);
    return NULL;
}

int main() {
    pthread_t thread;
    int *args = malloc(sizeof(int));
    *args = 42;
    pthread_create(&thread, NULL, thread_cb, args);
    pthread_join(thread, NULL);
    printf("Finish operation successfully!\n");
    return 0;
}