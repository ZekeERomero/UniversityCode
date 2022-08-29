%{
#include "scanType.h"  // TokenData Type
#include <stdio.h>
#include <string.h>
#include <ctype.h>

double vars[26];    

extern int yylex();
extern FILE *yyin;
extern int line;         // ERR line number from the scanner!!
extern int numErrors;    // ERR err count

// prints out character warnings ONLY for now
void yywarning(const char *token)
{
	int len = strlen(token) - 2;
	printf("WARNING(%d): character is %d characters long and not a single character: '%s'.  The first char will be used.\n", line, len, token);
	numErrors++;
}

// prototypes for regular output and an extra removeChar function
void yyoutput(TokenData *tokenData);
void removeChar(char*, char);

// prints out errors
#define YYERROR_VERBOSE
void yyerror(const char *msg)
{
	printf("ERROR(%d): %s\n", line, msg);
	numErrors++;
}

%}

// this is included in the tab.h file
%union {
	TokenData *tokenData;
	int * value;
}

%token <tokenData> QUIT NUMCONST ID STRINGCONST CHARCONST BOOLCONST NONCHAR ILLEGALCHAR OPERATION KEYWORD

%%
statementlist : statementlist statement
              | statement
              ;

statement     : '\n'
              | STRINGCONST	        { yyoutput($1); }
	      | NUMCONST		{ yyoutput($1); }
	      | QUIT	                { exit(0); }
              | BOOLCONST		{ yyoutput($1); }
	      | CHARCONST		{ yyoutput($1); }
              | OPERATION		{ yyoutput($1); }
	      | KEYWORD			{ yyoutput($1); }
              | NONCHAR			{ yywarning($1->tokenstr); yyoutput($1);}
              | ILLEGALCHAR		{ yyerror("'' is not a legal char"); }
              | ID			{ yyoutput($1); }
	      | ' '
              ; 

%%
extern int yydebug;
int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		if ((yyin = fopen(argv[1], "r"))) {
		// file has opened successful
	}
	else
	{
		// failed to open file
		printf("ERROR: failed to open \'%s\'\n", argv[1]);
		exit(1);
		}
	}

	// init variables a through z
	for (int i=0; i<26; i++) vars[i] = 0.0;

	// do the parsing
	numErrors = 0;
	yyparse();

	// printf("Number of errors: %d\n", numErrors);   // ERR

	return 0;
}

// this function is responsible for eating escape characters '\char'
void removeChar(char* s, char c)
{
	bool safe = false;
	int j, n = strlen(s);
	for (int i = j = 0; i < n; i++)
	{
        	if (s[i] != c || safe)
		{
			if (safe)
			{
				if (s[i] == 'n')
				{
					s[j++] = '\n';
				}
				else if (s[i] == '0')
				{
					s[j++] = ' ';
				}
				else
				{
					s[j++] = s[i];
				}
			}
			else
			{
				s[j++] = s[i];
			}
			safe = false;
		}
		else
		{
			safe = true;
		}
	}	
 
	s[j] = '\0';
}

// this function turns the entire string to upper case
void uppercase(char* s)
{
        int j, n = strlen(s);
        for (int i = j = 0; i < n; i++)
        {
		s[j++] = toupper(s[i]);
        }

        s[j] = '\0';
}

// this function acts as a regular output
void yyoutput(TokenData *tokenData)
{
	printf("Line %d Token: ", tokenData->linenum);
        if (tokenData->tokenclass == STRINGCONST)
	{
		removeChar(tokenData->svalue, '\\');
                printf("STRINGCONST Value: \"%s\"  Len: %ld  Input: %s\n", tokenData->svalue, yystrlen(tokenData->svalue), tokenData->tokenstr);
	}
	else if (tokenData->tokenclass == NUMCONST)
		printf("NUMCONST Value: %d  Input: %s\n", tokenData->nvalue, tokenData->tokenstr);
	else if (tokenData->tokenclass == CHARCONST || tokenData->tokenclass == NONCHAR)
		printf("CHARCONST Value: '%c'  Input: %s\n", tokenData->cvalue, tokenData->tokenstr);
	else if (tokenData->tokenclass == BOOLCONST)
		printf("BOOLCONST Value: %d  Input: %s\n", tokenData->nvalue, tokenData->tokenstr);
	else if (tokenData->tokenclass == OPERATION)
		printf("%s\n", tokenData->tokenstr);
	else if (tokenData->tokenclass == KEYWORD)
	{
		uppercase(tokenData->tokenstr);
               	printf("%s\n", tokenData->tokenstr);
	}
	else if (tokenData->tokenclass == ID)
                printf("ID Value: %s\n", tokenData->tokenstr);
}
