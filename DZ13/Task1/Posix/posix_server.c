#include <stdio.h>
#include <mqueue.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#define SERVER_QUEUE "/server_queue_20250417"
#define CLIENT_QUEUE "/client_queue_20250417"
#define MAX_MSG_SIZE 256
#define MSG_PRIORITY 1

struct mq_attr attr = {
    .mq_flags = 0,
    .mq_maxmsg = 10,
    .mq_msgsize = MAX_MSG_SIZE,
    .mq_curmsgs = 0
};

int main() {
    // Создаем очереди с явными атрибутами
    mqd_t server_q = mq_open(SERVER_QUEUE, O_CREAT | O_RDWR, 0666, &attr);
    mqd_t client_q = mq_open(CLIENT_QUEUE, O_CREAT | O_RDWR, 0666, &attr);
    
    if (server_q == (mqd_t)-1 || client_q == (mqd_t)-1) {
        perror("Ошибка создания очереди");
        return 1;
    }

    printf("Сервер: Отправляю сообщение...\n");
    const char* msg = "Hi!";
    if (mq_send(server_q, msg, strlen(msg)+1, MSG_PRIORITY) == -1) {
        perror("Ошибка отправки");
        return 1;
    }

    printf("Сервер: Ожидание подтверждения...\n");
    char ack[MAX_MSG_SIZE];
    if (mq_receive(client_q, ack, MAX_MSG_SIZE, NULL) == -1) {
        perror("Ошибка получения подтверждения");
        return 1;
    }
    printf("Сервер: Получено сообщение: '%s'\n", ack);

    // Даем клиенту время завершить работу
    sleep(2);

    // Аккуратно закрываем и удаляем очереди
    mq_close(server_q);
    mq_close(client_q);
    mq_unlink(SERVER_QUEUE);
    mq_unlink(CLIENT_QUEUE);
    printf("Сервер: Очереди успешно удалены\n");

    return 0;
}
