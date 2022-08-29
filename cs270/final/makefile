CC	= gcc
RM	= rm -f

default: all

all: main \
	reverse \
	final

main: main.c
	$(CC) -c main.c reverse.h

reverse: reverse.c
	$(CC) -c reverse.c reverse.h

final: main.o reverse.o
	$(CC) -o final main.o reverse.o

clean veryclean:
	$(RM) main
	$(RM) reverse
	$(RM) final
