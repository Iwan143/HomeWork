#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    pid_t pid = fork();

    if (pid == 0){
        printf("Дочерний процесс: pid = %d, ppid = %d, gid = %d\n", getpid(), getppid(), getgid());
        exit(0);
    } else{
        printf("Родительский процесс: pid = %d, ppid = %d, gid = %d\n", getpid(), getppid(), getgid());
    

    int status;
    wait(&status);

    printf ("Дочерний процесс завершился со статусом: %d\n", WEXITSTATUS(status));
}

    return 0;
}