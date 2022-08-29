%{
// this *order* of these includes is important
#include "scanType.h"  // TokenData Type
#include "parser.tab.h"  // token definitions from the bison
#include <string>

int line = 1;
int numErrors;    // error count

static int setValue(int linenum, int tokenClass, char *svalue)
{
	// create a new TokenData node
	yylval.tokenData = new TokenData;
	
	// fill it up with properties
	yylval.tokenData->linenum = linenum;
	yylval.tokenData->tokenstr = strdup(svalue);  // duplicating string
	yylval.tokenData->tokenclass = tokenClass;
  
	// integer case
	if (tokenClass == NUMCONST)
	{
		yylval.tokenData->nvalue = atof(svalue); 
	}
	// boolean case
	else if (tokenClass == BOOLCONST)
	{
		if (strcmp(svalue, "true"))
			yylval.tokenData->nvalue = 0;
		if (strcmp(svalue, "false"))
			yylval.tokenData->nvalue = 1;
	}
	// character case
	else if (tokenClass == CHARCONST || tokenClass == NONCHAR)
	{
		// checking if character has a backslash(\)
		if (svalue[1] == '\\')
		{
			// if a new line is called, char = '\n'
			if (svalue[2] == 'n')
			{
				yylval.tokenData->cvalue = '\n';
			}
			// if a nul character is called, char = '\0'
			else if (svalue[2] == '0')
			{
				yylval.tokenData->cvalue = '\0';
			}
			//if no operation is called, simply print the next char
			else
			{
				yylval.tokenData->cvalue = svalue[2];
			}
		}
		// if no backslash is present, print the correct character
		else
		{
			yylval.tokenData->cvalue = svalue[1];
		}
	}
	// string case
	else if (tokenClass == STRINGCONST)
	{
		int stringSize = strlen(svalue) - 1;

		char* string = (char *)malloc(stringSize*sizeof(char));
		int stringIndex = 0;

		for (int i = 1; i < stringSize; i++)
		{
         		string[stringIndex++] = svalue[i];
		}
	   	string[stringIndex] = '\0';

		yylval.tokenData->svalue = string;
	}

	// return the tokenclass
	return tokenClass;
}

%}

%option noyywrap

%%

\"(([^"\n])*"\\\""([^"\n])*)*[^"\\\n]("\\\\")*("\\\"")?\"|\"("\\\\")*("\\\"")?\"			{ return setValue(line, STRINGCONST, yytext); }
\"([^"\n])*[^"\\\n]("\\\\")*("\\\"")?\"|\"("\\\\")*("\\\"")?\"					{ return setValue(line, STRINGCONST, yytext); }
"true"|"false"					{ return setValue(line, BOOLCONST, yytext); }
'\\.'						{ return setValue(line, CHARCONST, yytext); }
'([^'])'					{ return setValue(line, CHARCONST, yytext); }
'([^'\n])+'					{ return setValue(line, NONCHAR, yytext); }
''						{ return setValue(line, ILLEGALCHAR, yytext); }
"stop"|"quit"|"exit"				{ return setValue(line, QUIT, yytext); }
[0-9]+|[0-9]*\.[0-9]+				{ return setValue(line, NUMCONST, yytext); }
[0-9]+\.[0-9]*					{ return setValue(line, NUMCONST, yytext); }
"+="						{ return setValue(line, OPERATION, strdup("ADDASS")); }
"-="						{ return setValue(line, OPERATION, strdup("SUBASS")); }
"*="                                    	{ return setValue(line, OPERATION, strdup("MULASS")); }
"/="                                    	{ return setValue(line, OPERATION, strdup("DIVASS")); }
"++"						{ return setValue(line, OPERATION, strdup("INC")); }
"--"                    			{ return setValue(line, OPERATION, strdup("DEC")); }
"<="						{ return setValue(line, OPERATION, strdup("LEQ")); }
">="						{ return setValue(line, OPERATION, strdup("GEQ")); }
"><"						{ return setValue(line, OPERATION, strdup("NEQ")); }
":="                                    	{ return setValue(line, OPERATION, strdup("ASGN")); }
[\<\>\;\%\{\}\:\<\>\?\,\[\]\=\+\-\*\/\(\)]	{ return setValue(line, OPERATION, yytext); }
"break"|"to"|"by"|"if"|"then"|"else"|"while"	{ return setValue(line, KEYWORD, yytext); }
"do"|"for"|"not"|"int"|"bool"|"char"|"static"	{ return setValue(line, KEYWORD, yytext); }
"or"|"and"|"return"				{ return setValue(line, KEYWORD, yytext); }
[ \t]						;
\/\/.*						;
\/\*.*\*\/					;
\n						{ line++; return setValue(line, yytext[0], yytext ); }
([A-Za-z])+([A-Za-z0-9])*			{ return setValue(line, ID, yytext); }
.						{ printf("ERROR(%d): Invalid or misplaced input character: '%c'. Character Ignored.\n", line, yytext[0]); numErrors++; }

%%
