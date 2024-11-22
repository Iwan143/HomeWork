#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
    setlocale(LC_ALL, "Rus");
    float chek;
    int n, i, j;
    int **matrix;
    while (1) {
        printf("vvedite size matrix: ");
        if ((!scanf("%f", &chek)) || (chek != (int)chek) || (chek <= 0)) {
            printf("tok polgitelniy chisla.\n");
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
    // Заполнение матрицы по спирали
    int value = 1;
    int startRow = 0, endRow = n - 1, startCol = 0, endCol = n - 1;

    while (startRow <= endRow && startCol <= endCol) {
        // Обход верхней строки
        for (int i = startCol; i <= endCol; i++) {
            matrix[startRow][i] = value++;
        }
        startRow++;

        // Обход правого столбца
        for (int i = startRow; i <= endRow; i++) {
            matrix[i][endCol] = value++;
        }
        endCol--;

        // Обход нижней строки
        if (startRow <= endRow) {
            for (int i = endCol; i >= startCol; i--) {
                matrix[endRow][i] = value++;
            }
            endRow--;
        }

        // Обход левого столбца
        if (startCol <= endCol) {
            for (int i = endRow; i >= startRow; i--) {
                matrix[i][startCol] = value++;
            }
            startCol++;
        }
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}