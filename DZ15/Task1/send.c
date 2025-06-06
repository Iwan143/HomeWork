#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Использование: %s <PID получателя>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t pid = (pid_t)atoi(argv[1]);
    printf("Отправка SIGUSR1 процессу %d...\n", pid);
    if (kill(pid, SIGUSR1) == -1) {
        perror("Ошибка kill");
        exit(EXIT_FAILURE);
    }

    return 0;
}
