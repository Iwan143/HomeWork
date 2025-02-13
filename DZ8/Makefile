# Компилятор
CC = gcc
# Флаги компиляции
CFLAGS = -fPIC -Wall -Wextra
# Имя динамической библиотеки
LIB_NAME = libcalc.so
# Имя исполняемого файла
BIN_NAME = main

all: $(LIB_NAME) $(BIN_NAME)

# Сборка динамической библиотеки
$(LIB_NAME): add.o div.o mul.o sub.o
	$(CC) -shared -o $@ $^

# Компиляция объектных файлов
%.o: %.c calc.h
	$(CC) $(CFLAGS) -c $< -o $@

# Сборка основной программы
$(BIN_NAME): main.c
	$(CC) main.c -o $@ -L. -lcalc

# Очистка собранных файлов
clean:
	rm -f *.o $(LIB_NAME) $(BIN_NAME)

# Установка библиотеки в систему (опционально)
install:
	sudo cp $(LIB_NAME) /usr/lib/
	sudo ldconfig

.PHONY: all clean install
