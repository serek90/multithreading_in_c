#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *hello_thread_cb(void *arg) {
    printf("Hello from thread!\n");
    return NULL;
}

int main() {
    pthread_t hello_thread;
    pthread_create(&hello_thread, NULL, hello_thread_cb, NULL);
    pthread_join(hello_thread, NULL);
    printf("Thread finished. Bye!\n");
    return 0;
}