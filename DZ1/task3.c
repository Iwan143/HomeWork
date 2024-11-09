#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>


int main() {
    int n, i;
    int started = 0;
    int count = 0;
    printf("Vvedite chislo : ");
    scanf("%d", &n);
    if (n < 0) {
        printf("tolko pologitelniy chisla");
        return 1;
    }
    else
    {
        for (int i = 31; i >= 0; i--) {
            if (n & (1 << i)) {
                printf("1");
                started = 1;
                count += started;
                
            }
            else if (started) {
                printf("0");
            }
        }
        if (!started) {
            printf("0");
        }
        printf("\n");
        printf("kol edenic: %d", count);
    }
    return 0;
}