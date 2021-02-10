CC=gcc
CFLAGS = -I

all: tcpClient.c tcpServer.c
	gcc -I tcpClient.c tcpServer.c

client: tcpClient.c
	gcc -o client tcpClient.c

server: tcpServer.c
	gcc -o server tcpServer.c

clean: 
	rm -f *.o client server