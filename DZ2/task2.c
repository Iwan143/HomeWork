#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Rus");
    int n, i;
    float chek;
    while (1) {
        printf("������� ������ �������: ");
        if ((!scanf("%f", &chek)) || (chek != (int)chek) || (chek <= 0)) {
            printf("������������ ����. ���������� ��� ���.\n");
            while (getchar() != '\n');
        }
        else {
            n = (int)chek;
            break;
        }
    }
    int *arr = (int**)malloc(n * sizeof(int*));
    for (i = 0; i < n; i++) {
        arr[i] = (int*)malloc(n * sizeof(int));
    }
    int val = 1;
    for (i = 0; i < n; i++) { 
            arr[i]= val++;
    }
    printf("��� ������:\n");
    for (i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    int *arr_2 = (int**)malloc(n * sizeof(int*));
    for (i = 0; i < n; i++) {
        arr_2[i] = arr[n - i - 1];
    }
    printf("������ � �������� �������:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", arr_2[i]);
    }

        return 0;
    }

