#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *factorial(void *arg) {
    unsigned int *num = (unsigned int *)arg;
    unsigned long long *ret = malloc(sizeof(unsigned long long));
    *ret = 1;

    for(int i = 1; i <= *num; i++)
        *ret *= i;

    return ret;
}

int main() {
    pthread_t factorial_calc;
    unsigned int num = 4;
    pthread_create(&factorial_calc, NULL, factorial, &num);

    unsigned long long *ret;
    pthread_join(factorial_calc, (void **)&ret);
    printf("Factorial of %u is %llu\n", num, *ret);

    return 0;
}