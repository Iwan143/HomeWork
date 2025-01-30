#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct {
    char name[10];
    char second_name[10];
    char tel[10];
} abonent;

// ��������� ���� ����������� ������
typedef struct Node {
    abonent data;
    struct Node* prev;
    struct Node* next;
} Node;

// ���������� ���������� ��� ���������� �������
Node* head = NULL;  // ��������� �� ������ ������
Node* tail = NULL;  // ��������� �� ����� ������


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
    printf("1) �������� ��������\n"
        "2) ������� ��������\n"
        "3) ����� ��������� �� �����\n"
        "4) ����� ���� �������\n"
        "5) �����\n");
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
            printf("�������.\n");
            break;
        default:
            printf("������. ������ �������� �� 1 �� 5\n");
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
                    printf("������� ����� ��������. �������� ������.\n");
                    continue;
                }
            }
            break;
        }
        else {
            printf("������ �����. �������� ������.\n");
            clearbuffer();
        }
    }
}


void new_abonent() {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("������ ��������� ������.\n");
        return;
    }

    safeinput(new_node->data.name, 10, "����� ���: ");
    safeinput(new_node->data.second_name, 10, "����� �������: ");
    safeinput(new_node->data.tel, 10, "����� ����� ��������: ");

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

    printf("������� ��������.\n");
}


void del() {
    char name[10], second_name[10];
    safeinput(name, 10, "������� ���: ");
    safeinput(second_name, 10, "������� �������: ");

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
            printf("������� ������.\n");
            found = 1;
            break;
        }
        current = current->next;
    }

    if (!found) {
        printf("�������� � ����� ������ �� �������.\n");
    }
}


void searc() {
    char name[10], second_name[10];
    safeinput(name, 10, "������� ���: ");
    safeinput(second_name, 10, "������� �������: ");

    Node* current = head;
    int found = 0;

    while (current != NULL) {
        if (strcmp(current->data.name, name) == 0 && strcmp(current->data.second_name, second_name) == 0) {
            printf("���: %s, �������: %s, �������: %s\n", current->data.name, current->data.second_name, current->data.tel);
            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("�������� � ����� ������ �� �������.\n");
    }
}


void printall() {
    Node* current = head;
    int found = 0;

    while (current != NULL) {
        printf("���: %s, �������: %s, �������: %s\n", current->data.name, current->data.second_name, current->data.tel);
        found = 1;
        current = current->next;
    }

    if (!found) {
        printf("���������� ����.\n");
    }
}

// ������������ ������
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