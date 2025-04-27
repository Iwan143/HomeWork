all:receiver sender
	./receiver & \
	sleep 0.1; \
	./sender $$(pgrep -o receiver)  

receiver: rec.c
	gcc rec.c -o receiver

sender: send.c
	gcc send.c -o sender

clear:
	rm -f receiver sender

.PHONY: clear