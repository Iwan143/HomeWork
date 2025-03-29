#include <stdio.h>

int main(void){
    int i;
    long a = 0;
    for(i = 0; i <180000000; i++){
        a++;
    }
    printf("Последовательный код, a = %ld\n", a);
    return 0;
}