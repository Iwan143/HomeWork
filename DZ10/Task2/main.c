#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void print(const char *name){
    printf("%s: pid = %d, ppid = %d\n",name, getpid(), getppid());
}

void create(int num_child, const char *parent_name){
    for(int i = 0; i < num_child; i++){
        pid_t pid = fork();
        
        if (pid == 0){
            char child_name[20];
            snprintf(child_name, sizeof(child_name), "%s.%d", parent_name, i + 1);
            print(child_name);
            exit(0);
        } else if (pid < 0) {
            perror("fork");
            exit(1);
        }
    }

    for(int i = 0; i < num_child; i++){
        wait(NULL);
    }
}


int main(){
    print("Родительский процесс");

    pid_t pid1 = fork();
    while(pid1 == 0){
        print("Процесс1");
        create(2, "Процесс1");
        exit(0);
    }

    pid_t pid2 = fork();
    if (pid2 == 0){
        print("Процесс 2:");
        create(1, "Процесс2");
        exit(0);
    }

    wait(NULL);
    wait(NULL);

    printf("Родительский процесс завершен\n");
    return 0;
}