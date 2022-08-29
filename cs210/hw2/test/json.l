%{
// The quick brown fox jumped over the lazy dog.
#include <stdio.h>
#include "json.tab.h"
%}

%option yylineno
%option noyywrap

%%

[ \n]           { /* skip */ }
"\""[^\\"]*"\""|"\""\\[bfnrtu]"\"" {return STRING;}
"true"		{return TRUE;}
"false"		{return FALSE;}
null            {return NUL; }
[0-9]+|[0-9]+.[0-9]+	{return NUM;}
"{"             {return '{'; }
"}"             {return '}';}
","             {return ',';}
":"             {return ':';}
"["             {return '[';}
"]"             {return ']';}
"/"		{return '/';}
"-"		{return '-';}
"+"		{return '+';}
"e"		{return 'e';}
"E"		{return 'E';}
