#include <stdio.h>
#include <pthread.h>

#define N 4

long a = 0;
pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;

void *thread_calc(void *args){
    int *ptr = (int *) args;
    int i;
    ptr ++;
    for(i = 0; i < 45000000; i++){
        pthread_mutex_lock(&m1);
        a = a + 1;
        pthread_mutex_unlock(&m1);
    }
    return NULL;
}

int main(void){
    int i, i1;
    int *s;
    pthread_t thread[N];

    for(i = 0; i < N; i++){
        pthread_create(&thread[i], NULL, thread_calc, NULL);
    }
    for(i1 = 0; i1 < N; i1 ++){
        pthread_join(thread[i1], (void **) &s);
    }
    printf("mutex,a = %ld\n", a);
    return 0;
}