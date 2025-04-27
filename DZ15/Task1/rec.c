#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>

volatile bool received_signal = false;

void signal_handler(int sig) {
    printf("[PID %d] Получен сигнал SIGUSR1! Завершение через 2 секунды...\n", getpid());
    received_signal = true;
}

int main() {
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Ошибка sigaction");
        exit(EXIT_FAILURE);
    }

    printf("Ожидание сигнала SIGUSR1 (PID: %d)...\n", getpid());
    while (!received_signal) {
        pause();
    }

    sleep(2);
    printf("Программа завершена.\n");
    return 0;
}
