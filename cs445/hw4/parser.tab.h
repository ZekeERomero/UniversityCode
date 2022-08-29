/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
    OPERATION = 266,
    KEYWORD = 267,
    BOOL = 268,
    CHAR = 269,
    INT = 270,
    EQ = 271,
    GREATER = 272,
    LESSER = 273,
    SEMICOLON = 274,
    COMMA = 275,
    LCURLY = 276,
    RCURLY = 277,
    LBRACKET = 278,
    RBRACKET = 279,
    LPAREN = 280,
    RPAREN = 281,
    COLON = 282,
    QUESTION = 283,
    MATHOP = 284,
    ADDASS = 285,
    SUBASS = 286,
    MULASS = 287,
    DIVASS = 288,
    INC = 289,
    DEC = 290,
    LEQ = 291,
    GEQ = 292,
    NEQ = 293,
    ASGN = 294,
    ADD = 295,
    SUB = 296,
    MUL = 297,
    DIV = 298,
    MOD = 299,
    BREAK = 300,
    TO = 301,
    BY = 302,
    IF = 303,
    THEN = 304,
    ELSE = 305,
    WHILE = 306,
    DO = 307,
    FOR = 308,
    NOT = 309,
    STATIC = 310,
    OR = 311,
    AND = 312,
    RETURN = 313,
    CHSIGN = 314,
    SIZEOF = 315
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 59 "parser.y" /* yacc.c:1909  */

	ExpType type;
	TokenData *tokenData;
	TreeNode *treeNode;

#line 121 "parser.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
