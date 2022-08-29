%{
// this *order* of these includes is important
#include "scanType.h"  // TokenData Type
#include "parser.tab.h"  // token definitions from the bison
#include "yyerror.h"
#include <string>

int line = 1;
int numErrors;		//error count
int numWarnings;	//warning count

char* lastToken;

void removeChar(char *s);
void uppercase(char *s);

void clearBuffer()
{
	YY_FLUSH_BUFFER;
}

static int setValue(int linenum, int tokenClass, char *svalue)
{
	// create a new TokenData node
	yylval.tokenData = new TokenData;
	
	// fill it up with properties
	yylval.tokenData->linenum = linenum;
	yylval.tokenData->tokenstr = strdup(svalue);  // duplicating string
	yylval.tokenData->tokenclass = tokenClass;

	lastToken = svalue;
  
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
	else if (tokenClass == CHARCONST)
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

		//Remove extra '\'
		removeChar(string);

		yylval.tokenData->svalue = string;
	}
	else if (tokenClass == ID)
	{
		//uppercase(svalue);
		yylval.tokenData->id = strdup(svalue);
	}
	
	// return the tokenclass
	return tokenClass;
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

// this function is responsible for eating escape characters '\char'
void removeChar(char* s)
{
        char c = '\\';
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

%}

%option noyywrap

%%

\"(([^"\n])*"\\\""([^"\n])*)*[^"\\\n]("\\\\")*("\\\"")?\"|\"("\\\\")*("\\\"")?\"	{ return setValue(line, STRINGCONST, yytext); }
\"([^"\n])*[^"\\\n]("\\\\")*("\\\"")?\"|\"("\\\\")*("\\\"")?\"						{ return setValue(line, STRINGCONST, yytext); }
"true"|"false"																		{ return setValue(line, BOOLCONST, yytext); }
'\\.'																				{ return setValue(line, CHARCONST, yytext); }
'([^'])'																			{ return setValue(line, CHARCONST, yytext); }
'([^'\n])+'																			{ printf("WARNING(%d): character is %d characters long and not a single character: '%s'.  The first char will be used.\n", line, strlen(yytext) - 2, yytext); numWarnings++; return setValue(line, CHARCONST, yytext); }

"stop"|"quit"|"exit"																{ return setValue(line, QUIT, yytext); }
[0-9]+|[0-9]*\.[0-9]+																{ return setValue(line, NUMCONST, yytext); }

"+="																				{ return setValue(line, ADDASS, strdup("ADDASS")); }
"-="																				{ return setValue(line, SUBASS, strdup("SUBASS")); }
"*="																				{ return setValue(line, MULASS, strdup("MULASS")); }
"/="																				{ return setValue(line, DIVASS, strdup("DIVASS")); }
"++"																				{ return setValue(line, INC, strdup("INC")); }
"--"																				{ return setValue(line, DEC, strdup("DEC")); }
"<="																				{ return setValue(line, LEQ, strdup("LEQ")); }
">="																				{ return setValue(line, GEQ, strdup("GEQ")); }
"><"																				{ return setValue(line, NEQ, strdup("NEQ")); }
":="                     											               	{ return setValue(line, ASGN, strdup("ASGN")); }
">"																					{ return setValue(line, GREATER, yytext); }
"<"																					{ return setValue(line, LESSER, yytext); }
";"                   												                { return setValue(line, SEMICOLON, yytext); }
"{"																					{ return setValue(line, LCURLY, yytext); }
"}"																					{ return setValue(line, RCURLY, yytext); }
"["                                         									    { return setValue(line, LBRACKET, yytext); }
"]"     									                                        { return setValue(line, RBRACKET, yytext); }
"("                 									                            { return setValue(line, LPAREN, yytext); }
")"               																	{ return setValue(line, RPAREN, yytext); }
":"                																	{ return setValue(line, COLON, yytext); }
"?"                																	{ return setValue(line, QUESTION, yytext); }
","																					{ return setValue(line, COMMA, yytext); }

"="																					{ return setValue(line, EQ, yytext); }

"+"																					{ return setValue(line, ADD, yytext); }
"-"																					{ return setValue(line, SUB, yytext); }
"*"																					{ return setValue(line, MUL, yytext); }
"/"																					{ return setValue(line, DIV, yytext); }
"%"																					{ return setValue(line, MOD, yytext); }

"int"																				{ return setValue(line, INT, yytext); }
"bool"																				{ return setValue(line, BOOL, yytext); }
"char"																				{ return setValue(line, CHAR, yytext); }

"if"																				{ return setValue(line, IF, yytext); }
"then"																				{ return setValue(line, THEN, yytext); }
"else"																				{ return setValue(line, ELSE, yytext); }

"break"																				{ return setValue(line, BREAK, yytext); }
"to"																				{ return setValue(line, TO, yytext); }
"by"																				{ return setValue(line, BY, yytext); }
"while"																				{ return setValue(line, WHILE, yytext); }
"do"																				{ return setValue(line, DO, yytext); }
"for"																				{ return setValue(line, FOR, yytext); }
"not"																				{ return setValue(line, NOT, yytext); }
"static"																			{ return setValue(line, STATIC, yytext); }
"or"																				{ return setValue(line, OR, yytext); }
"and"																				{ return setValue(line, AND, yytext); }
"return"																			{ return setValue(line, RETURN, yytext); }

[ \t]																				;
\/\/.*																				;
\/\*.*\*\/																			;
[\n]																				{ line++; }
([A-Za-z])+([A-Za-z0-9\_])*															{ return setValue(line, ID, yytext); }
''																					{ printf("ERROR(%d): Empty character ''.  Characters ignored.\n", line); numErrors++; }
.																					{ printf("ERROR(%d): Invalid or misplaced input character: '%c'. Character Ignored.\n", line, yytext[0]); numErrors++; }

%%
