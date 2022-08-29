%{
#include "tree.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define YYDEBUG 1
//struct node *yyroot;
%}

%union {
    struct node *n;
}

%type <n> ml element elements value function call list integer variable expression expressions ifstatement
%token <n> STRING
%token <n> FUN
%token <n> COLONCOLON
%token <n> @
%token <n> INTLITERAL
%token <n> '('
%token <n> ')'
%token <n> '['
%token <n> ']'
%token <n> ','
%token <n> ':'
%token <n> '/'
%token <n> '-'
%token <n> '+'
%token <n> '*'
%token <n> '='
%token <n> VAL
%token <n> IF
%token <n> THEN
%token <n> ELSE

%%

ml : element;

element : list | STRING | INTLITERAL | expression | '(' elements ')' | '(' elements COLONCOLON elements ')' | '(' elements @ element ')' ;

elements : element | element ',' elements;

function : 'fun' FUN '(' elements ')';

call : function;

list : '[' elements ']';

listname : VAL element '=' list;

integer : VAL element '=' INTLITERAL;

variable : VAL element '=' elements;

expression : elements | assignment | expression '+' expression | expression '-' expression | expression '*' expression | element '/' element;

expressions : expression | assignment;

assignment : element '=' expression;

ifstatement : IF '(' expressions '=' expressions ')' THEN expressions ELSE expressions;
