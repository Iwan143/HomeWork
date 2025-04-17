all: server client
	./server & 
	sleep 5
	./client
	sleep 2
	wait    

server: posix_server.c
	gcc posix_server.c -o server -lrt


client: posix_client.c
	gcc posix_client.c -o client -lrt

clear:
	rm -f server client

.PHONY: clear