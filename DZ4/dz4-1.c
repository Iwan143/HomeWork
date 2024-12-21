#include <stdio.h>
#include <string.h>
#include <locale.h>
#define N 100
typedef struct {
    char name[10];
    char second_name[10];
    char tel[10];
}abonent;

void menusetup();
void printmenu();

void init(abonent* abonents);
int freeindex(abonent* abonents);
void clearbuffer();
void safeinput(char* input, size_t size, const char* prompt);
void new_abonent(abonent* abonents);
void del(abonent* abonents);
void searc(abonent* abonents);
void printall(abonent* abonents);


void printmenu() {
    printf("1) Добавить абонента\n"
        "2) Удалить абонента\n"
        "3) Поиск абонентов по имени\n"
        "4) Вывод всех записей\n"
        "5) Выход\n");
}

void menusetup() {
    //setlocale(LC_ALL,"Rus");
    abonent abonents[N];
    int choice;
    init(abonents);
    do {
        printmenu();
        scanf("%d", &choice);


        switch (choice)
        {
        case 1:
            new_abonent(abonents);
            break;
        case 2:
            del(abonents);
            break;
        case 3:
            searc(abonents);
            break;
        case 4:
            printall(abonents);
            break;
        case 5:
            printf("Выходим.");
            break;

        default:
            printf("Ошибка. Выбери значение от 1 до 5\n");
            break;
        }
    } while (choice != 5);
}

void init(abonent* abonents) {
    for (int i = 0; i < N; i++) {
        abonents[i].name[0] = '\0';
        abonents[i].second_name[0] = '\0';
        abonents[i].tel[0] = '\0';
    }
}

int freeindex(abonent* abonents) {
    for (int i = 0; i < N; i++) {
        if (abonents[i].name[0] == '\0') {
            return i;
        }
    }
    return -1;
}

void clearbuffer() {
    int a;
    while ((a = getchar()) != '\n' && a != EOF);
}

void safeinput(char* input, size_t size, const char* prompt) {
    while (1) {
        printf("%s", prompt);
        if (scanf("%9s", input) == 1) {
            if (strlen(input) == size - 1) {
                int a = getchar();
                if (a != '\n' && a != EOF) {
                    clearbuffer();
                    printf("Введено много символов. Попробуй заново.\n");
                    continue;
                }
            }
            break;
        }
        else {
            printf("Ошибка ввода. Попробуй заново.\n");
            clearbuffer();
        }
    }
}

void new_abonent(abonent* abonents) {
    int index = freeindex(abonents);
    if (index == -1) {
        printf("Справочник переполнен. усё!\n");
        return;
    }
    safeinput(abonents[index].name, 10, "Введи имя: ");
    safeinput(abonents[index].second_name, 10, "Введи фамилию: ");
    safeinput(abonents[index].tel, 10, "Введи номер телефона: ");
    printf("Абонент добавлен.\n");
}
void del(abonent* abonents) {
    char name[10], second_name[10];
    safeinput(name, 10, "Введите имя: ");
    safeinput(second_name, 10, "Введите фамилию: ");

    int found = 0;
    for (int i = 0; i < N; i++) {
        if (strcmp(abonents[i].name, name) == 0 && strcmp(abonents[i].second_name, second_name) == 0) {
            abonents[i].name[0] = '\0';
            abonents[i].second_name[0] = '\0';
            abonents[i].tel[0] = '\0';
            printf("Абонент удален.\n");
            found = 1;
        }
    }
    if (!found) {
        printf("Абоненты с таким именем не найдены.\n");
    }
}

void searc(abonent* abonents) {
    char name[10], second_name[10];
    safeinput(name, 10, "Введите имя: ");
    safeinput(second_name, 10, "Введите фамилию: ");

    int found = 0;
    for (int i = 0; i < N; i++) {
        if (strcmp(abonents[i].name, name) == 0 && strcmp(abonents[i].second_name, second_name) == 0) {
            printf("Имя: %s, Фамилия: %s, Телефон: %s\n", abonents[i].name, abonents[i].second_name, abonents[i].tel);
            found = 1;
        }
    }
    if (!found) {
        printf("Абоненты с таким именем не найдены.\n");
    }
}

void printall(abonent* abonents) {
    int found = 0;
    for (int i = 0; i < N; i++) {
        if (abonents[i].name[0] != '\0') {
            printf("Имя: %s, Фамилия: %s, Телефон: %s\n", abonents[i].name, abonents[i].second_name, abonents[i].tel);
            found = 1;
        }
    }
    if (!found) {
        printf("Справочник пуст.\n");
    }
}
int main() {
    setlocale(LC_ALL,"Rus");
    menusetup();
    return 0;
}