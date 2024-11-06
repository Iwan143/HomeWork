#define _CRT_SECURE_NO_WARNINGS //����� �� ����� ������ �� scanf
#include <stdio.h>
#include <locale.h>


void printBinary(unsigned int num) {
    // ������� ���������� ����� � �����
    int bits = sizeof(num) * 8; // 8 ��� � �����
    int started = 0; // ����, ����� �� �������� ������� ����

    for (int i = bits - 1; i >= 0; i--) {
        // ���������, ���������� �� i-� ���
        if (num & (1 << i)) {
            printf("1");
            started = 1; // ������ �������� �������� �������������
        }
        else if (started) {
            printf("0");
        }
    }

    // ���� ����� ����� ����, ������� 0
    if (!started) {
        printf("0");
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    unsigned int number;

    printf("������� ������������� ����� �����: ");
    scanf("%u", &number);

    printf("�������� ������������� ����� %u: ", number);
    printBinary(number);
    printf("\n");

    return 0;
}