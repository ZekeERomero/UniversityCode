/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    QUIT = 258,
    NUMCONST = 259,
    ID = 260,
    STRINGCONST = 261,
    CHARCONST = 262,
    BOOLCONST = 263,
    NONCHAR = 264,
    ILLEGALCHAR = 265,
    KEYWORD = 266,
    BOOL = 267,
    CHAR = 268,
    INT = 269,
    EQ = 270,
    GREATER = 271,
    LESSER = 272,
    SEMICOLON = 273,
    COMMA = 274,
    LCURLY = 275,
    RCURLY = 276,
    LBRACKET = 277,
    RBRACKET = 278,
    LPAREN = 279,
    RPAREN = 280,
    COLON = 281,
    QUESTION = 282,
    MATHOP = 283,
    ADDASS = 284,
    SUBASS = 285,
    MULASS = 286,
    DIVASS = 287,
    INC = 288,
    DEC = 289,
    LEQ = 290,
    GEQ = 291,
    NEQ = 292,
    ASGN = 293,
    ADD = 294,
    SUB = 295,
    MUL = 296,
    DIV = 297,
    MOD = 298,
    BREAK = 299,
    TO = 300,
    BY = 301,
    IF = 302,
    THEN = 303,
    ELSE = 304,
    WHILE = 305,
    DO = 306,
    FOR = 307,
    NOT = 308,
    STATIC = 309,
    OR = 310,
    AND = 311,
    RETURN = 312,
    CHSIGN = 313,
    SIZEOF = 314
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 94 "parser.y"

	ExpType type;
	TokenData *tokenData;
	TreeNode *treeNode;

#line 123 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
