all: sender receiver
sender: sender.c
	gcc sender.c -pthread -o sender
receiver: receiver.c
	gcc receiver.c -pthread -o receiver
clean:
	rm sender receiver
