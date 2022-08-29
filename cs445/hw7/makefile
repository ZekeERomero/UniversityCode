BIN = parser
CC = g++
OP = ourgetopt
SYM = symbolTable
SEM = semantic
IO = ioruntime
ERR = yyerror
EMIT = emitcode
GEN = gencode

DOCS = $(OP).cpp $(OP).h
SYMS = $(SYM).cpp $(SYM).h
SEMS = $(SEM).cpp $(SEM).h
SRCS = $(BIN).y  $(BIN).l
IOS = $(IO).cpp $(IO).h
ERRS = $(ERR).cpp $(ERR).h
EMITS = $(EMIT).cpp $(EMIT).h
GENS = $(GEN).cpp $(GEN).h
HDRS = scanType.h

OBJS = lex.yy.o $(BIN).tab.o
OPT = $(OP).cpp
SYMB = $(SYM).cpp
SEMN = $(SEM).cpp
IOR = $(IO).cpp
YYERR = $(ERR).cpp
EMITC = $(EMIT).cpp
GENC = $(GEN).cpp

$(BIN) : $(OBJS) $(OPT)
	$(CC) $(OBJS) $(OPT) $(SYMB) $(SEMN) $(IOR) $(YYERR) $(EMITC) $(GENC) -o c-

lex.yy.c : $(BIN).l $(BIN).tab.h $(HDR)
	flex $(BIN).l

$(BIN).tab.h $(BIN).tab.c : $(BIN).y
	bison -v -t -d $(BIN).y

clean :
	rm -f *~ $(OBJS) $(BIN) lex.yy.c $(BIN).tab.h $(BIN).tab.c $(BIN).output

tar : $(HDR) $(SRCS) makefile
	tar -cvf hw7.tar $(HDRS) $(SRCS) $(DOCS) $(SYMS) $(SEMS) $(IOS) $(ERRS) $(EMITS) $(GENS) makefile
