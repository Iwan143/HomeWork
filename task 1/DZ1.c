#define _CRT_SECURE_NO_WARNINGS //чтобы не кидал ошибки на scanf
#include <stdio.h>
#include <locale.h>


void printBinary(unsigned int num) {
    // Находим количество битов в числе
    int bits = sizeof(num) * 8; // 8 бит в байте
    int started = 0; // Флаг, чтобы не печатать ведущие нули

    for (int i = bits - 1; i >= 0; i--) {
        // Проверяем, установлен ли i-й бит
        if (num & (1 << i)) {
            printf("1");
            started = 1; // Начали выводить двоичное представление
        }
        else if (started) {
            printf("0");
        }
    }

    // Если число равно нулю, выводим 0
    if (!started) {
        printf("0");
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    unsigned int number;

    printf("Введите положительное целое число: ");
    scanf("%u", &number);

    printf("Двоичное представление числа %u: ", number);
    printBinary(number);
    printf("\n");

    return 0;
}