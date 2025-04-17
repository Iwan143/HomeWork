#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

#define MSG_SIZE 128
#define SERVER_MSG_TYPE 1
#define CLIENT_MSG_TYPE 2

struct msgbuf {
    long mtype;
    char mtext[MSG_SIZE];
};

int main() {
    key_t key = ftok(".", 'A');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    int msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Сервер: Очередь создана (ID: %d)\n", msgid);

    struct msgbuf msg;
    while (1) {
        // Получение сообщения от клиента
        if (msgrcv(msgid, &msg, sizeof(msg.mtext), SERVER_MSG_TYPE, 0) == -1) {
            perror("msgrcv");
            break;
        }
        printf("Сервер: Получено сообщение: '%s'\n", msg.mtext);

        // Отправка подтверждения клиенту
        msg.mtype = CLIENT_MSG_TYPE;
        strcpy(msg.mtext, "Hi!");
        if (msgsnd(msgid, &msg, sizeof(msg.mtext), 0) == -1) {
            perror("msgsnd");
            break;
        }
        printf("Сервер: Подтверждение отправлено\n");
    }

    // Удаление очереди
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(1);
    }
    printf("Сервер: Очередь успешно удалена\n");

    return 0;
}
