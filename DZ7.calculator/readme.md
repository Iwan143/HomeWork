**Скачиваем папку Calculator**

**В терминале, переходим в директорию Calculator**

**Компилируем библиотеку:**

gcc -c add.c sub.c mul.c div.c

ar rcs libcalc.a add.o sub.o mul.o div.o

**Сборка и запуск:**

gcc main.c -o calculator -L. -lcalc -lncurses
./calculator
