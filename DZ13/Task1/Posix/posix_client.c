#include <stdio.h>
#include <mqueue.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#define SERVER_QUEUE "/server_queue_20250417"
#define CLIENT_QUEUE "/client_queue_20250417"
#define MAX_MSG_SIZE 256

int main() {
    mqd_t server_q = mq_open(SERVER_QUEUE, O_RDONLY);
    mqd_t client_q = mq_open(CLIENT_QUEUE, O_WRONLY);
    
    if (server_q == (mqd_t)-1 || client_q == (mqd_t)-1) {
        perror("Ошибка открытия очереди");
        return 1;
    }

    char buf[MAX_MSG_SIZE];
    ssize_t bytes_read = mq_receive(server_q, buf, MAX_MSG_SIZE, NULL);
    if (bytes_read == -1) {
        perror("Ошибка чтения сообщения");
        return 1;
    }
    printf("Клиент: Получено сообщение: '%s'\n", buf);

    const char* ack = "hello!";
    if (mq_send(client_q, ack, strlen(ack)+1, 1) == -1) {
        perror("Ошибка отправки подтверждения");
        return 1;
    }
    printf("Клиент: Подтверждение отправлено\n");

    mq_close(server_q);
    mq_close(client_q);

    return 0;
}
