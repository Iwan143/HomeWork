# Упрощённый Makefile с подсказками для пользователя
CC = gcc
CFLAGS = -Wall -Wextra

.PHONY: all run test clear help

all: main send
	@echo "===================================="
	@echo "✅ Программы успешно скомпилированы:"
	@echo "- main (блокировка SIGINT)"
	@echo "- send (отправка сигналов)"
	@echo "===================================="
	@echo "Используйте:"
	@echo "make run  - запуск main"
	@echo "make test - отправить сигнал"
	@echo "make clear - удалить программы"

main: main.c
	@echo "🔧 Компиляция main..."
	$(CC) $(CFLAGS) $< -o $@

send: send.c
	@echo "🔧 Компиляция send..."
	$(CC) $(CFLAGS) $< -o $@

run: main
	@echo "🚀 Запуск main в фоновом режиме..."
	./main & echo $$! > pid.txt
	@echo "🔄 PID сохранён в pid.txt: $$(cat pid.txt)"
	@echo "ℹ️ Используйте 'make test' для отправки сигнала"

test: send
	@if [ -f pid.txt ]; then \
		echo "📤 Отправка сигнала на PID $$(cat pid.txt)..."; \
		./send $$(cat pid.txt); \
	else \
		echo "❌ Ошибка: сначала выполните 'make run'"; \
		exit 1; \
	fi

clear:
	@echo "🧹 Очистка..."
	rm -f main send pid.txt
	@echo "✅ Все скомпилированные файлы удалены"

help:
	@echo "Доступные команды:"
	@echo "make all   - скомпилировать все программы (по умолчанию)"
	@echo "make run   - запустить main"
	@echo "make test  - отправить сигнал"
	@echo "make clear - удалить программы"
	@echo "make help  - показать эту справку"
