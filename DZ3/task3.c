#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <locale.h>
#define MAX_LENGTH 100

char* find_substring(const char* str, const char* substr);
setlocale(LC_ALL, "Rus");
int main() {
    char str[MAX_LENGTH];
    char substr[MAX_LENGTH];

    printf("Введите строку: ");
    fgets(str, MAX_LENGTH, stdin);
    str[strcspn(str, "\n")] = '\0';

    printf("Введите подстроку: ");
    fgets(substr, MAX_LENGTH, stdin);
    substr[strcspn(substr, "\n")] = '\0';

    char* result = find_substring(str, substr);

    if (result) {
        printf("Подстрока %c... найдена, начиная с индекса %ld (%p)\n", *result,
            result - str, result);
    }
    else {
        printf("Подстрока не найдена\n");
    }

    return 0;
}

char* find_substring(const char* str, const char* substr) {
    if (*substr == '\0')
        return (char*)str;

    for (const char* p = str; *p != '\0'; p++) {
        const char* p1 = p;
        const char* p2 = substr;

        while (*p1 == *p2 && *p2 != '\0') {
            p1++;
            p2++;
        }

        if (*p2 == '\0') {
            return (char*)p;
        }
    }

    return NULL;
}