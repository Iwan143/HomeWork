#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>

int main() {
    int originalNumber; // Исходное число
    int newByteValue;   // Новое значение третьего байта
    printf("vvedite pologitelnoe cheloe chislo: ");
    scanf("%d", &originalNumber);
    if (originalNumber < 0) {
        printf("tolko pologitelniy chisla");
    }   
    else
    {
        printf("vvedite novoe znachenie dlya 3-go bayta (0-255): ");
        scanf("%u", &newByteValue);

         if (newByteValue > 255 | newByteValue < 0) {
                printf("oshibka: znachenie doljno bit' v diapazone 0-255.\n");
         }
         else {
             originalNumber &= 0xFF00FFFF; // Clearing the third byte (byte with index 2)
             originalNumber |= (newByteValue << 16); // Setting a new third byte
             printf("novoe chislo: %u\n", originalNumber);
             printf("dvoichnoe predstavlenie: ");
             for (int i = sizeof(originalNumber) * 8 - 1; i >= 0; i--) {
                 printf("%u", (originalNumber >> i) & 1);
             }
             printf("\n");
         }
    }
    return 0;
}