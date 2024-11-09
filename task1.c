#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <locale.h>


int main() {
    setlocale(LC_ALL, "Rus");
    int n, i;
    int started = 0;
    printf("¬ведите число : ");
    scanf("%d", &n);
    if (n<0)
        printf("только положительные числа");
    else
    {
        for (int i = 31; i >= 0; i--) {
            if (n & (1 << i)) {
                printf("1");
                started = 1;
            }
            else if (started) {
                printf("0");
            }
        }
        if (!started) {
            printf("0");
        }
    }
   return 0;
}
