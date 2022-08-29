BIN = parser
CC = g++

DOCS = getop.cpp getop.h
SRCS = $(BIN).y  $(BIN).l
HDRS = scanType.h
OBJS = lex.yy.o $(BIN).tab.o
OPT = getop.cpp

$(BIN) : $(OBJS) $(OPT)
	$(CC) $(OBJS) $(OPT) -o c-

lex.yy.c : $(BIN).l $(BIN).tab.h $(HDR)
	flex $(BIN).l

$(BIN).tab.h $(BIN).tab.c : $(BIN).y
	bison -v -t -d $(BIN).y

clean :
	rm -f *~ $(OBJS) $(BIN) lex.yy.c $(BIN).tab.h $(BIN).tab.c $(BIN).output

tar : $(HDR) $(SRCS) makefile
	tar -cvf hw2.tar $(HDRS) $(SRCS) $(DOCS) makefile
