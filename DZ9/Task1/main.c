#include <stdio.h>
#include <string.h>

int main() {
    FILE *file = fopen("output.txt", "w");
    if (file != NULL) {
        fputs("String from file", file);
        fclose(file);
    }

    char a[100];
    file = fopen("output.txt", "r");
    if (file != NULL) {
        fgets(a, sizeof(a), file);
        fclose(file);
    }

    int len= strlen(a);
    for (int i = len - 1; i >= 0; i--) {
        printf("%c", a[i]);
    }

    return 0;
}
