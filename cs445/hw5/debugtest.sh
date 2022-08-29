make clean
bison -v -t -d parser.y
flex parser.l
g++ -g -c -o lex.yy.o lex.yy.c
g++ -g -c -o parser.tab.o parser.tab.c
g++ -g lex.yy.o parser.tab.o ourgetopt.cpp symbolTable.cpp semantic.cpp ioruntime.cpp yyerror.cpp -o c-
