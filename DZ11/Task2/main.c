#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 4

void run_spinlock() {
    system("/usr/bin/time -v ./spinlock");
}

void run_sequentialcode() {
    system("/usr/bin/time -v ./sequentialcode");
}

void run_mutex() {
    system("/usr/bin/time -v ./mutex");
}

void run_multithreadedcode() {
    system("/usr/bin/time -v ./multithreadedcode");
}

void run_mapreduce2() {
    system("/usr/bin/time -v ./mapreduce2");
}

void run_mapreduce() {
    system("/usr/bin/time -v ./mapreduce");
}


// Меню выбора
void display_menu() {
    printf("Выберите программу для запуска:\n");
    printf("1. spinlock\n");
    printf("2. sequentialcode\n");
    printf("3. mutex\n");
    printf("4. multithreadedcode\n");
    printf("5. mapreduce_spinlock\n");
    printf("6. mapreduce_mutex\n");
    printf("7. Выход\n");
}

int main() {
    int choice;
    while (1) {
        display_menu();
        printf("Ваш выбор: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: run_spinlock(); break;
            case 2: run_sequentialcode(); break;
            case 3: run_mutex(); break;
            case 4: run_multithreadedcode(); break;
            case 5: run_mapreduce2(); break;
            case 6: run_mapreduce(); break;
            case 7: printf("Выход из программы.\n"); return 0;
            default: printf("Неверный выбор.\n");
        }
    }

    return 0;
}
