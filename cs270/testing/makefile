CC      = gcc
CFLAGS  = -g
RM      = rm -f


default: all

all: Hello \
	Test

Hello: Hello.c
	$(CC) -o Hello Hello.c

Test: Test.c
	$(CC) -o Test Test.c

clean veryclean:
	$(RM) Hello
	$(RM) Test
