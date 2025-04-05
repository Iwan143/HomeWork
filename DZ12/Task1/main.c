#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

int main(){
    int p[2];
    pid_t pid;
    pipe(p);
    pid = fork();

    if (pid == 0){
        close(p[1]);
        char b[100];
        read(p[0], b, 100);
        printf("Получено: %s\n",b);
        close(p[0]);    
    }else{
        close(p[0]);
        write(p[1], "Hi!", 3);
        close(p[1]);
        wait(NULL);
    }
    return 0;
}