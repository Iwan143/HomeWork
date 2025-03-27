#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

pid_t gettid(){
    return syscall(SYS_gettid);
}

void* print_id(void* arg){
    int index = *((int*)arg);
    pid_t tid = gettid();
    pid_t pid = getpid();
    pid_t ppid = getppid();
    printf("Поток с индексом: %d, TID: %d, PID: %d, PPID: %d\n", index,tid,pid,ppid);
    pthread_exit(NULL);
}

int main (){
    pthread_t thereads[5];
    int indexs[5];

    for(int i = 0; i < 5; i++){
        indexs[i] = i;
        if (pthread_create(&thereads[i], NULL, print_id, &indexs[i]) != 0){
            perror("Ошибка при создании потока");
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i < 5; i++){
        pthread_join(thereads[i], NULL);
    }

    return 0;
}