#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct {
    char name[10];
    char second_name[10];
    char tel[10];
} abonent;

// The node structure of a doubly linked list
typedef struct Node {
    abonent data;
    struct Node* prev;
    struct Node* next;
} Node;

// Global variables for list management
Node* head = NULL;  // Pointer to the beginning of the list
Node* tail = NULL;  // Pointer to the end of the list


void printmenu();
void menusetup();
void clearbuffer();
void safeinput(char* input, size_t size, const char* prompt);
void new_abonent();
void del();
void searc();
void printall();
void free_list();

void printmenu() {
    printf("1) Добавить абонента\n"
        "2) Удалить абонента\n"
        "3) Поиск абонентов по имени\n"
        "4) Вывод всех записей\n"
        "5) Выход\n");
}


void menusetup() {
    int choice;
    do {
        printmenu();
        scanf("%d", &choice);
        clearbuffer();  

        switch (choice) {
        case 1:
            new_abonent();
            break;
        case 2:
            del();
            break;
        case 3:
            searc();
            break;
        case 4:
            printall();
            break;
        case 5:
            printf("Выходим.\n");
            break;
        default:
            printf("Ошибка. Выбери значение от 1 до 5\n");
            break;
        }
    } while (choice != 5);
}


void clearbuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
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


void new_abonent() {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Ошибка выделения памяти.\n");
        return;
    }

    safeinput(new_node->data.name, 10, "Введи имя: ");
    safeinput(new_node->data.second_name, 10, "Введи фамилию: ");
    safeinput(new_node->data.tel, 10, "Введи номер телефона: ");

    new_node->prev = NULL;
    new_node->next = NULL;

    if (head == NULL) {
        head = tail = new_node;
    }
    else {
        tail->next = new_node;
        new_node->prev = tail;
        tail = new_node;
    }

    printf("Абонент добавлен.\n");
}


void del() {
    char name[10], second_name[10];
    safeinput(name, 10, "Введите имя: ");
    safeinput(second_name, 10, "Введите фамилию: ");

    Node* current = head;
    int found = 0;

    while (current != NULL) {
        if (strcmp(current->data.name, name) == 0 && strcmp(current->data.second_name, second_name) == 0) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            }
            else {
                head = current->next;
            }

            if (current->next != NULL) {
                current->next->prev = current->prev;
            }
            else {
                tail = current->prev;
            }

            free(current);
            printf("Абонент удален.\n");
            found = 1;
            break;
        }
        current = current->next;
    }

    if (!found) {
        printf("Абоненты с таким именем не найдены.\n");
    }
}


void searc() {
    char name[10], second_name[10];
    safeinput(name, 10, "Введите имя: ");
    safeinput(second_name, 10, "Введите фамилию: ");

    Node* current = head;
    int found = 0;

    while (current != NULL) {
        if (strcmp(current->data.name, name) == 0 && strcmp(current->data.second_name, second_name) == 0) {
            printf("Имя: %s, Фамилия: %s, Телефон: %s\n", current->data.name, current->data.second_name, current->data.tel);
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("Абоненты с таким именем не найдены.\n");
    }
}


void printall() {
    Node* current = head;
    int found = 0;

    while (current != NULL) {
        printf("Имя: %s, Фамилия: %s, Телефон: %s\n", current->data.name, current->data.second_name, current->data.tel);
        found = 1;
        current = current->next;
    }

    if (!found) {
        printf("Справочник пуст.\n");
    }
}

// Freeing up memory
void free_list() {
    Node* current = head;
    Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    head = tail = NULL;
}


int main() {
    setlocale(LC_ALL, "Rus");
    menusetup();
    free_list();  
    return 0;
}