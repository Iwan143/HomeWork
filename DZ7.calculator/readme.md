__Скомпилируем библиотеку:

gcc -c add.c sub.c mul.c div.c
ar rcs libcalc.a add.o sub.o mul.o div.o

__Сборка и запуск:

gcc main.c -o calculator -L. -lcalc -lncurses
./calculator
