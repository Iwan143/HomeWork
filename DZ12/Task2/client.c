#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(){
    const char *fifo = "my_fifo";

    int fd = open(fifo, O_RDONLY);
    if (fd == -1){
        perror("ошибка при открытие fifo");
        return 1;
    }

    char buf[100];
    ssize_t byte_read = read(fd, buf, sizeof(buf));
    if (byte_read == -1){
        perror("ошибка при чтении из fifo");
        close(fd);
        return 1;
    } 

    printf("получено: %s\n", buf);

    close(fd);
    printf("клиент завершил работу.\n");
    return 0;
}