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

    int msgid = msgget(key, 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    struct msgbuf msg;
    
    msg.mtype = SERVER_MSG_TYPE;
    strcpy(msg.mtext, "Hello!");
    if (msgsnd(msgid, &msg, sizeof(msg.mtext), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }
    printf("Клиент: Сообщение отправлено\n");

    if (msgrcv(msgid, &msg, sizeof(msg.mtext), CLIENT_MSG_TYPE, 0) == -1) {
        perror("msgrcv");
        exit(1);
    }
    printf("Клиент: Получено сообщение: '%s'\n", msg.mtext);

    return 0;
}
