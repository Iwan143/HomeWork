#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

int main(){
    const char *fifo = "my_fifo";
    unlink(fifo);

    if (mkfifo(fifo, 0666) == -1){
        perror("ошибка при создании fifo");
        return -1;
    }

    int fd = open(fifo, O_WRONLY);
    if (fd == -1){
        perror("ошибка при открытие fifo");
        return -1;
    }
     const char *mess = "HI! about server";
     if (write(fd, mess, strlen(mess) + 1) == -1){
        perror("ошибка при записи в fifo");
        close(fd);
        return 1;
    }

    close(fd);
    printf("сервер завершил работу.\n");
    return 0;
}