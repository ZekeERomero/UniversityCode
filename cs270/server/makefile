CC	= gcc -o
RM	= rm -f

default: all

all: server \
	client

server: server.c
	$(CC) server server.c

client: client.c
	$(CC) client client.c

clean veryclean:
	$(RM) server
	$(RM) client
