all: main
	./main

main: main.c
	gcc spinlock.c -o spinlock -pthread
	gcc sequentialcode.c -o sequentialcode
	gcc mutex.c -o mutex -pthread
	gcc multithreadedcode.c -o multithreadedcode -pthread
	gcc mapreduce2.c -o mapreduce2 -pthread
	gcc mapreduce.c -o mapreduce -pthread
	gcc -o main main.c
clear:
	rm -f spinlock sequentialcode mutex multithreadedcode mapreduce2 mapreduce main

.PHONY: clear