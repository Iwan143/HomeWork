#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>

int main() {
    int n, i;
    printf("Vvedite chislo : ");
    scanf("%d", &n);
    if (n > 0)
        printf("tolko otricatelniy chisla");
    else
    {
        for (int i = 31; i >= 0; i--) {
            printf("%d", (n >> i) & 1);
        }
        
    }
    return 0;
}
