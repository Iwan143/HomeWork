#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
    setlocale(LC_ALL, "Rus");
    float chek;
    int n, i, j;
    int** matrix;
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

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i + j >= n - 1) {
                matrix[i][j] = 1;
            }
            else {
                matrix[i][j] = 0;
            }
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