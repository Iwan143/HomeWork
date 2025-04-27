all:main send
	./main & \
	sleep 0.1; \
	./send $$!  

main: main.c
	gcc main.c -o main

send: send.c
	gcc send.c -o send

clear:
	rm -f main send

.PHONY: clear