#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main() {
    sigset_t mask;
    int sig;
    
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigprocmask(SIG_BLOCK, &mask, NULL);

    printf("EventLoop PID: %d\n", getpid());
    while (1) {
        sigwait(&mask, &sig);
        printf("[%d] Получен SIGUSR1\n", getpid());
    }
}
