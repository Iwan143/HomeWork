#include <stdio.h>
#include <string.h>
char* findSubstring(char* str, char* subStr) {
    char* ptr = strstr(str, subStr);
    return ptr; // ���������� ��������� �� ������ ��������� ��� NULL
}
int main() {
    char str[100];   
    char subStr[50]; 
    printf("vvedite stroku: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = 0; // ������� ������ ����� ������, ���� �� ����
    printf("vvedite podstroku: ");
    fgets(subStr, sizeof(subStr), stdin);
    subStr[strcspn(subStr, "\n")] = 0; // ������� ������ ����� ������, ���� �� ����
    // ����� ���������
    char* result = findSubstring(str, subStr);
    if (result != NULL) {
        printf("podstroka naydena: %s\n", result);
    }
    else {
        printf("podstroka ne naydenan");
    }
    return 0;
}