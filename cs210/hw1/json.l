%{
#include <stdio.h>
#define ASSIGN 1
#define SWAP 2
#define REV_ASSIGN 2
#define REV_SWAP 3
#define ADD 4
#define SUBTRACT 5
#define MULTIPLY 6
#define DIVIDE 7
#define MODULO 8
#define POWER 9
#define EQUAL 10
#define NOT_EQUAL 11
#define LESS_THAN 12
#define LESS_EQUAL 13
#define GREATER_THAN 14
#define GREATER_EQUAL 15
#define STRING_EQUAL 16
#define STRING_NOT_EQUAL 17
#define STRING_LESS_THAN 18
#define STRING_LESS_EQUAL 19
#define STRING_GREATER_THAN 20
#define STRING_GREATER_EQUAL 21
#define EQUIVALENT 22
#define NOT_EQUIVALENT 23
#define ADD_EQUAL 24
#define SUBTRACT_EQUAL 25
#define MULTIPLY_EQUAL 26
#define DIVIDE_EQUAL 27
%}

%option yylineno
%option noyywrap

%%

[ \n]           				{ /*do nothing*/ }
space                                           { /*do nothing*/ }
[#].*						{ /*do nothing*/ }

[a-zA-Z_][a-zA-Z0-9_]*[ ]*":="[ ]*.[^ ]*	{ return ASSIGN; }
[a-zA-Z_][a-zA-Z0-9_]*[ ]*":=:"[ ]*.[^ ]*       { return SWAP; }
[a-zA-Z_][a-zA-Z0-9_]*[ ]*"<-"[ ]*.[^ ]*        { return REV_ASSIGN; }
[a-zA-Z_][a-zA-Z0-9_]*[ ]*"<->"[ ]*.[^ ]*       { return REV_SWAP; }

[a-zA-Z_][a-zA-Z0-9_]*[ ]*"+:="[ ]*.*		{ return ADD_EQUAL; }
[a-zA-Z_][a-zA-Z0-9_]*[ ]*"-:="[ ]*.*		{ return SUBTRACT_EQUAL; }
[a-zA-Z_][a-zA-Z0-9_]*[ ]*"*:="[ ]*.*		{ return MULTIPLY_EQUAL; }
[a-zA-Z_][a-zA-Z0-9_]*[ ]*"/:="[ ]*.*		{ return DIVIDE_EQUAL; }

[a-zA-Z_][a-zA-Z0-9_]*[ ]*"+"[ ]*[a-zA-Z0-9_]*	{ return ADD; }
[a-zA-Z_][a-zA-Z0-9_]*[ ]*"-"[ ]*[a-zA-Z0-9_]*	{ return SUBTRACT; }
[a-zA-Z_][a-zA-Z0-9_]*[ ]*"*"[ ]*[a-zA-Z0-9_]*	{ return MULTIPLY; }
[a-zA-Z_][a-zA-Z0-9_]*[ ]*"/"[ ]*[a-zA-Z0-9_]*	{ return DIVIDE; }
[a-zA-Z_][a-zA-Z0-9_]*[ ]*"%"[ ]*[a-zA-Z0-9_]*  { return MODULO; }
[a-zA-Z_][a-zA-Z0-9_]*[ ]*"^"[ ]*[a-zA-Z0-9_]* 	{ return POWER; }

[a-zA-Z_][a-zA-Z0-9_]*[ ]*"~==="[ ]*.[^ )]*	{ return NOT_EQUIVALENT; }
[a-zA-Z_][a-zA-Z0-9_]*[ ]*"==="[ ]*.[^ )]*      { return EQUIVALENT; }

[a-zA-Z_][a-zA-Z0-9_]*[ ]*">>="[ ]*.[^ )]*      { return STRING_GREATER_EQUAL; }
[a-zA-Z_][a-zA-Z0-9_]*[ ]*">>"[ ]*.[^ )]*       { return STRING_GREATER_THAN; }
[a-zA-Z_][a-zA-Z0-9_]*[ ]*"<<="[ ]*.[^ )]*      { return STRING_LESS_EQUAL; }
[a-zA-Z_][a-zA-Z0-9_]*[ ]*"<<"[ ]*.[^ )]*       { return STRING_LESS_THAN; }
[a-zA-Z_][a-zA-Z0-9_]*[ ]*"~=="[ ]*.[^ )]*      { return STRING_NOT_EQUAL; }
[a-zA-Z_][a-zA-Z0-9_]*[ ]*"=="[ ]*.[^ )]*       { return STRING_EQUAL; }

[a-zA-Z_][a-zA-Z0-9_]*[ ]*">="[ ]*.[^ )]*       { return GREATER_EQUAL; }
[a-zA-Z_][a-zA-Z0-9_]*[ ]*">"[ ]*.[^ )]*        { return GREATER_THAN; }
[a-zA-Z_][a-zA-Z0-9_]*[ ]*"<="[ ]*.[^ )]*       { return LESS_EQUAL; }
[a-zA-Z_][a-zA-Z0-9_]*[ ]*"<"[ ]*.[^ )]*        { return LESS_THAN; }
[a-zA-Z_][a-zA-Z0-9_]*[ ]*"~="[ ]*.[^ )]*       { return NOT_EQUAL; }
[a-zA-Z_][a-zA-Z0-9_]*[ ]*"="[ ]*.[^ )]*      	{ return EQUAL; }

.               				{ /*do nothing */ }
