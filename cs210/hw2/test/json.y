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

%type <n> json element elements value object members member array number negative exponent
%token <n> STRING
%token <n> NUM
%token <n> NUL
%token <n> FALSE
%token <n> TRUE
%token <n> '{'
%token <n> '}'
%token <n> '['
%token <n> ']'
%token <n> ','
%token <n> ':'
%token <n> '/'
%token <n> '-'
%token <n> '+'
%token <n> 'e'
%token <n> 'E'

%%

json : element {
		$$ = calloc(1,sizeof(struct treenode));
		add_node($$,0,1,$1,NULL,NULL);
	}
;

element : value {
		$$ = calloc(1,sizeof(struct treenode));
		add_node($$,1,1,$1,NULL,NULL);
	}
;

value : object {	
		$$ = calloc(1,sizeof(struct treenode));
        	add_node($$,2,1,$1,NULL,NULL);
	}
|	array {
                $$ = calloc(1,sizeof(struct treenode));
                add_node($$,3,1,$1,NULL,NULL);
        }

|	STRING {
                $$ = calloc(1,sizeof(struct treenode));
                add_node($$,4,1,$1,NULL,NULL);
        }
|	number {
                $$ = calloc(1,sizeof(struct treenode));
                add_node($$,5,1,$1,NULL,NULL);
        }
|	TRUE {
                $$ = calloc(1,sizeof(struct treenode));
                add_node($$,6,1,$1,NULL,NULL);
        }
|	FALSE {
                $$ = calloc(1,sizeof(struct treenode));
                add_node($$,7,1,$1,NULL,NULL);
        }
|	NUL {
                $$ = calloc(1,sizeof(struct treenode));
                add_node($$,8,1,$1,NULL,NULL);
        }
;

object : '{' members '}' {
		$$ = calloc(1,sizeof(struct treenode));
		add_node($$,9,3,$1,$2,$3);
	}
;

members : member {
		$$ = calloc(1,sizeof(struct treenode));
		add_node($$,10,1,$1,NULL,NULL);
	}
|	member ',' members {
                $$ = calloc(1,sizeof(struct treenode));
                add_node($$,11,3,$1,$2,$3);
        }
;

member : STRING ':' element {
		$$ = calloc(1,sizeof(struct treenode));
		add_node($$,12,3,$1,$2,$3);
	}
;

array : '[' elements ']' {
		$$ = calloc(1,sizeof(struct treenode));
		add_node($$,13,3,$1,$2,$3);
	}
;

elements : element {
		$$ = calloc(1,sizeof(struct treenode));
		add_node($$,14,1,$1,NULL,NULL);
	}
|	element ',' elements {
        	$$ = calloc(1,sizeof(struct treenode));
        	add_node($$,15,3,$1,$2,$3);
        }
;

number : NUM {
		$$ = calloc(1,sizeof(struct treenode));
		add_node($$,16,1,$1,NULL,NULL);
	}
|	negative {
                $$ = calloc(1,sizeof(struct treenode));
                add_node($$,17,1,$1,NULL,NULL);
        }
|	exponent {
		$$ = calloc(1,sizeof(struct treenode));
                add_node($$,18,1,$1,NULL,NULL);
        }
;

negative : '-' NUM {
		$$ = calloc(1,sizeof(struct treenode));
		add_node($$,19,2,$1,$2,NULL);
	}
;

exponent : number 'e' number {
		$$ = calloc(1,sizeof(struct treenode));
		add_node($$,20,3,$1,$2,$3);
	}
|	number 'E' number {
                $$ = calloc(1,sizeof(struct treenode));
                add_node($$,21,3,$1,$2,$3);
        }
;

%%

int yyerror(char* error){
	printf("%s on line ",error);
}
