#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Rus");
    int n, i, j;
    float chek;
    int** matrix;
    while (1) {
        printf("Введите размер квадратной матрицы: ");
        if ((!scanf("%f", &chek)) || (chek != (int)chek) || (chek <= 0)) {
            printf("Некорректный ввод. Попробуйте еще раз.\n");
            while (getchar() != '\n');
        }
        else {
            n = (int)chek;
            break;
        }
    }
    matrix = (int**)malloc(n * sizeof(int*));
    for (i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }
    int val = 1;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            matrix[i][j] = val++;
        }
    }
    printf("Ваша матрица:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}
