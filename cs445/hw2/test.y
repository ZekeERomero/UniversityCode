%{  
//Sam F
#include "scanType.h"  // TokenData Type
#include <stdio.h>
#include <string.h>
  

extern int yylex();
extern FILE *yyin;
extern int line;         
extern int numErrors;   

int valuesize;

#define YYERROR_VERBOSE
char * repString(char *text);
char formatCharConst(char *charString, int linenum);

void yyerror(const char *msg)
{
    printf("ERROR(%d): %s\n", line, msg);
    numErrors++;
}

%}

// this is included in the tab.h file
// so scanType.h must be included before the tab.h file!!!!
%union {
    TokenData *tokenData;
    double value;
}

%token <tokenData> BOOLCONST NUMBER ID KEYWORD OPERATOR STRINGCONST CHARCONST 
%token <tokenData> ASGN BOOL BREAK CHAR ELSE INT RETURN STATIC WHILE LEQ THEN IF FOR NOT DO TO BY
%token <tokenData> ADDASS DEC AND OR  INC GEQ NEQ SEMICOLON COMMA COLON LBRACKET RBRACKET LPAREN RPAREN LBRACE RBRACE 
%token <tokenData> ADDOP MINOP MULOP DIVOP SUBASS MULASS DIVASS EQ MOD QUESTION GTHAN LTHAN
/*
%type <value> program 
%type <value> declarationList
%type <value> declaration varDeclaration
%type <value> scoped-var-declaration
%type <value> varDeclarationList
%type <value> varDeclarationInitialize
%type <value> varDeclarationId
%type <value> typeSpecifier
%type <value> funDeclaration
%type <value> params
%type <value> paramList
%type <value> paramTypeList
%type <value> paramIdList
%type <value> paramId
%type <value> statement
%type <value> expStatement
%type <value> compoundStatement
%type <value> localDeclarations
%type <value> statementList
%type <value> selectStatement
%type <value> iterationStatement
%type <value> iterationRange
%type <value> returnStatement
%type <value> breakStatement
%type <value> expression
%type <value> assignop
%type <value> simpleExpression
%type <value> andExpression
%type <value> unaryRelExpression
%type <value> relExpression
%type <value> relop
%type <value> sumExpression
%type <value> sumop
%type <value> mulExpression
%type <value> mulop
%type <value> unaryExpression
%type <value> unaryOp
%type <value> factor
%type <value> mutable
%type <value> immutable
%type <value> call
%type <value> args
%type <value> argList
%type <value> constant
*/

%%

program: declarationList
       ;

declarationList: declarationList declaration
                | declaration
                ;

declaration: varDeclaration
           | funDeclaration
           ;

varDeclaration: typeSpecifier varDeclarationList SEMICOLON
               ;

scopedVarDeclaration: STATIC typeSpecifier varDeclarationList SEMICOLON
                      | typeSpecifier varDeclarationList SEMICOLON
                      ;

varDeclarationList: varDeclarationList COMMA varDeclarationInitialize 
                    | varDeclarationInitialize
                    ;

varDeclarationInitialize: varDeclarationId
                          | varDeclarationId COLON simpleExpression
                          ;

varDeclarationId: ID
           | ID LBRACKET NUMBER RBRACKET
           ;

typeSpecifier: INT
                | BOOL
                | CHAR
                ;

funDeclaration: typeSpecifier ID LPAREN params RPAREN compoundStatement
               | ID LPAREN params RPAREN compoundStatement
               | typeSpecifier ID LPAREN RPAREN compoundStatement
               | ID LPAREN RPAREN compoundStatement
               ; 

         
params: paramList
      ; 

paramList: paramList SEMICOLON paramTypeList
          | paramTypeList
          ;

paramTypeList: typeSpecifier paramIdList
             ;

paramIdList: paramIdList COMMA paramId
             | paramId
             ;

paramId: ID
        | ID LBRACKET RBRACKET 
        ;

statement: expStatement
         | compoundStatement
         | selectStatement
         | iterationStatement
         | returnStatement
         | breakStatement
         ;

expStatement: expression SEMICOLON
             | SEMICOLON
             ;

compoundStatement: LBRACE localDeclarations statementList RBRACE
                  | LBRACE localDeclarations RBRACE
                  | LBRACE statementList RBRACE
                  | LBRACE RBRACE
                  ;
         
localDeclarations: localDeclarations scopedVarDeclaration
                  | scopedVarDeclaration
                  ;

statementList: statementList statement
              | statement
              ;

selectStatement: IF simpleExpression THEN statement
                | IF simpleExpression THEN statement ELSE statement
                ;

iterationStatement: WHILE simpleExpression DO statement
                   | FOR ID ASGN iterationRange DO statement
                   ;
               
iterationRange: simpleExpression TO simpleExpression
               | simpleExpression TO simpleExpression BY simpleExpression
               ;

returnStatement: RETURN SEMICOLON
                | RETURN expression SEMICOLON
                ;

breakStatement: BREAK SEMICOLON
               ;

expression: mutable assignop expression
          | mutable INC
          | mutable DEC
          | simpleExpression
          ;

assignop: ASGN
        | ADDASS
        | SUBASS
        | MULASS
        | DIVASS
        ;
   
simpleExpression: simpleExpression OR andExpression
                 | andExpression
                 ;

andExpression: andExpression AND unaryRelExpression
              | unaryRelExpression
              ;

unaryRelExpression: NOT unaryRelExpression
                    | relExpression
                    ;

relExpression: sumExpression relop sumExpression 
              | sumExpression
              ;

relop: LEQ
     | GEQ 
     | GTHAN
     | LTHAN 
     | EQ 
     | NEQ 
     ;

sumExpression: sumExpression sumop mulExpression
              | mulExpression
              ;

sumop: ADDOP
     | MINOP
     ;

mulExpression: mulExpression mulop unaryExpression
              | unaryExpression
              ;
            
mulop: MULOP
     | DIVOP 
     | MOD
     ;
   
unaryExpression: unaryOp unaryExpression
                | unaryExpression
                ;

unaryOp: MINOP
        | MULOP
        | QUESTION
        ;

factor: mutable
      | immutable
      ;

mutable: ID
       | ID LBRACKET expression RBRACKET
       ;

immutable: LPAREN expression RPAREN
         | call
         | constant
         ;

call: ID LPAREN args RPAREN
    ;

args: argList
    ;

argList: argList COMMA expression
        | expression
        ;
   
constant: NUMBER
        | CHARCONST
        | STRINGCONST
        | BOOLCONST 
        ;


   
         


%%
extern int yydebug;
int main(int argc, char *argv[])
{
    if (argc > 1 && (argc != 3))
     {
        if ((yyin = fopen(argv[1], "r"))) {
            // file open successful
        }
        else
         {
            // failed to open file
            printf("ERROR: failed to open \'%s\'\n", argv[1]);
            exit(1);
        }
    }

    // do the parsing
    numErrors = 0;
    yyparse();

    //printf("Number of errors: %d\n", numErrors);   // ERR

    return 0;
}

char* repString(char *text)
{
   int len = strlen(text);
   int x = 0;
   int y = 0;
   
   char* newS = new char;
   
   while(x < len)
   {
      if(text[x] == '\\')
      {
         if(text[x+1] == '\\')
         {
            newS[y] = '\\';
            y++;
            x += 2;
         }
         else if(text[x+1] == 'n')
         {
            newS[y] = '\n';
            y++;
            x += 2;
         }
         else if(text[x+1] == '0')
         {
            newS[y] = ' ';
            y++;
            x += 2;
         }
         else
         {
            newS[y] = text[x+1];
            y++;
            x += 2;
         }
      }
      else
      {
         newS[y] = text[x];
         x++;
         y++;
      }
   }
   newS[y] = '\0';
   valuesize = y - 2;
   return newS;
}
char formatCharConst(char *charString, int linenum) 
{
    int length = strlen(charString) - 2;
    
    char theChar;

    if(length == 1) 
    {
        theChar = charString[1];
    } 
    else if(charString[1] == '\\')
    {
      switch (charString[2]) 
      {
         case 'n':
            theChar = '\n';
            break;
         case '0':
            theChar = '\0';
            break;
         default:
            theChar = charString[2];
            break;
      }
    }
    else
    {
       printf("WARNING(%d): character is %d characters long and not a single character: '%s'.  The first char will be used.\n", linenum, length, charString);
       theChar = charString[1];
    }
    
    return theChar; 
}

