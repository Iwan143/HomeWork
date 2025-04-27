#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Использование: %s <PID>\n", argv[0]);
        return 1;
    }
    pid_t pid = atoi(argv[1]);
    kill(pid, SIGUSR1);
    printf("Сигнал отправлен к PID %d\n", pid);
    return 0;
}
