#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    
    if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1) {
        perror("Ошибка sigprocmask");
        return 1;
    }

    printf("Программа запущена с PID: %d\n", getpid());
    printf("SIGINT заблокирован. Проверьте:\n");
    printf("1. Через send.c: ./send %d\n", getpid());
    printf("2. Через kill: kill -INT %d\n", getpid());
    printf("Программа не должна завершаться при этих сигналах.\n");

    while (1) {
        sleep(1);
    }

    return 0;
}
