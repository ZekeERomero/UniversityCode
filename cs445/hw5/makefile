BIN = parser
CC = g++
OP = ourgetopt
SYM = symbolTable
SEM = semantic
IO = ioruntime
ERR = yyerror

DOCS = $(OP).cpp $(OP).h
SYMS = $(SYM).cpp $(SYM).h
SEMS = $(SEM).cpp $(SEM).h
SRCS = $(BIN).y  $(BIN).l
IOS = $(IO).cpp $(IO).h
ERRS = $(ERR).cpp $(ERR).h
HDRS = scanType.h

OBJS = lex.yy.o $(BIN).tab.o
OPT = $(OP).cpp
SYMB = $(SYM).cpp
SEMN = $(SEM).cpp
IOR = $(IO).cpp
YYERR = $(ERR).cpp

$(BIN) : $(OBJS) $(OPT)
	$(CC) $(OBJS) $(OPT) $(SYMB) $(SEMN) $(IOR) $(YYERR) -o c-

lex.yy.c : $(BIN).l $(BIN).tab.h $(HDR)
	flex $(BIN).l

$(BIN).tab.h $(BIN).tab.c : $(BIN).y
	bison -v -t -d $(BIN).y

clean :
	rm -f *~ $(OBJS) $(BIN) lex.yy.c $(BIN).tab.h $(BIN).tab.c $(BIN).output

tar : $(HDR) $(SRCS) makefile
	tar -cvf hw5.tar $(HDRS) $(SRCS) $(DOCS) $(SYMS) $(SEMS) $(IOS) $(ERRS) makefile
