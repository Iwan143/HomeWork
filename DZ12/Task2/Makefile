all: server client
	./server &  
	./client    

server: server.c
	gcc server.c -o server

client: client.c
	gcc client.c -o client

clear:
	rm -f server client my_fifo

.PHONY: clear
