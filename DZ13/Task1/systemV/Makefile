all: server client
	./server & 
	sleep 5
	./client
	sleep 2
	wait    

server: systemv_server.c
	gcc systemv_server.c -o server


client: systemv_client.c
	gcc systemv_client.c -o client

clear:
	rm -f server client

.PHONY: clear