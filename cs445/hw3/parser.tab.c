/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

#include "scanType.h"  // TokenData Type
#include "ourgetopt.h"
#include "symbolTable.h"
#include "semantic.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

double vars[26];    

extern int yylex();
extern FILE *yyin;
extern int line;         // ERR line number from the scanner!!
extern int numErrors, numWarnings;    // ERR err count

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
TreeNode *newExpNode(ExpKind kind, TokenData *token, TreeNode *c0 = NULL, TreeNode *c1 = NULL, TreeNode *c2 = NULL);
TreeNode *newStmtNode(StmtKind kind, TokenData* token, TreeNode *c0 = NULL, TreeNode *c1 = NULL, TreeNode *c2 = NULL);
TreeNode *newDeclNode(DeclKind kind, ExpType type, TokenData* token = NULL, TreeNode *c0 = NULL, TreeNode *c1 = NULL, TreeNode *c2 = NULL);
void printToken(OpKind token, const char *tokenString);
static void printSpaces(void);
void printTree(TreeNode *tree, int childNum, bool types);
void setSibling(TreeNode *tree);


// prints out errors
#define YYERROR_VERBOSE
void yyerror(const char *msg)
{
	printf("ERROR(%d): %s\n", line, msg);
	numErrors++;
}

void mainError(char *msg)
{
	printf("ERROR(LINKER): %s\n", msg);
	numErrors++;
}

void fileError(char *file)
{
	printf("ERROR(ARGLIST): source file \"%s\" could not be opened.\n", file);
	numErrors++;
}


#line 124 "parser.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.h".  */
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
#line 60 "parser.y" /* yacc.c:355  */

	ExpType type;
	TokenData *tokenData;
	TreeNode *treeNode;

#line 231 "parser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 248 "parser.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   436

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  61
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  116
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  182

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   315

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    87,    87,    90,   103,   106,   107,   110,   120,   129,
     132,   145,   148,   149,   153,   156,   162,   165,   166,   167,
     170,   181,   187,   197,   204,   207,   220,   223,   233,   246,
     249,   252,   258,   259,   262,   263,   264,   265,   266,   267,
     270,   271,   274,   275,   278,   281,   283,   285,   288,   300,
     303,   315,   318,   324,   327,   332,   335,   344,   347,   356,
     359,   365,   366,   370,   373,   377,   380,   383,   386,   387,
     388,   389,   390,   393,   397,   400,   404,   407,   410,   413,
     417,   420,   421,   422,   423,   424,   425,   428,   432,   435,
     436,   439,   443,   446,   447,   448,   451,   459,   462,   463,
     464,   467,   468,   471,   472,   479,   480,   481,   484,   488,
     493,   496,   508,   511,   514,   517,   521
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "QUIT", "NUMCONST", "ID", "STRINGCONST",
  "CHARCONST", "BOOLCONST", "NONCHAR", "ILLEGALCHAR", "OPERATION",
  "KEYWORD", "BOOL", "CHAR", "INT", "EQ", "GREATER", "LESSER", "SEMICOLON",
  "COMMA", "LCURLY", "RCURLY", "LBRACKET", "RBRACKET", "LPAREN", "RPAREN",
  "COLON", "QUESTION", "MATHOP", "ADDASS", "SUBASS", "MULASS", "DIVASS",
  "INC", "DEC", "LEQ", "GEQ", "NEQ", "ASGN", "ADD", "SUB", "MUL", "DIV",
  "MOD", "BREAK", "TO", "BY", "IF", "THEN", "ELSE", "WHILE", "DO", "FOR",
  "NOT", "STATIC", "OR", "AND", "RETURN", "CHSIGN", "SIZEOF", "$accept",
  "program", "declList", "decl", "varDecl", "scopedVarDecl", "varDeclList",
  "varDeclInit", "varDeclId", "id", "typeSpec", "funDecl", "parms",
  "parmList", "parmTypeList", "parmIdList", "parmId", "stmt",
  "matchedStmt", "openStmt", "expStmt", "compoundStmt", "localDecls",
  "stmtList", "matchedSelectStmt", "openSelectStmt", "matchedIterStmt",
  "openIterStmt", "iterRange", "returnStmt", "breakStmt", "exp",
  "assignop", "simpleExp", "andExp", "unaryRelExp", "relExp", "relop",
  "sumExp", "sumop", "mulExp", "mulop", "unaryExp", "unaryop", "factor",
  "mutable", "immutable", "call", "args", "argList", "constant", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315
};
# endif

#define YYPACT_NINF -134

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-134)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      66,  -134,  -134,  -134,  -134,    19,    66,  -134,  -134,     2,
      27,  -134,  -134,  -134,    10,    88,  -134,    18,    62,    37,
      27,    36,    49,  -134,  -134,    27,   382,    68,    40,   130,
    -134,    54,    72,  -134,    37,    91,  -134,    59,  -134,  -134,
    -134,  -134,   382,  -134,  -134,  -134,   382,    96,    44,    55,
    -134,  -134,    73,    74,  -134,     9,  -134,  -134,  -134,  -134,
    -134,   104,    37,    89,  -134,  -134,   101,   382,   382,    27,
      91,   267,  -134,  -134,    27,  -134,  -134,  -134,  -134,  -134,
     185,   240,  -134,  -134,  -134,  -134,  -134,  -134,   110,    44,
      64,   109,    27,  -134,  -134,   105,  -134,   382,   357,   382,
     382,  -134,  -134,  -134,  -134,  -134,  -134,  -134,  -134,     9,
       9,  -134,  -134,  -134,     9,  -134,  -134,  -134,    37,  -134,
       8,    13,   100,    27,  -134,   121,  -134,  -134,   295,  -134,
    -134,  -134,  -134,  -134,  -134,  -134,  -134,  -134,  -134,   382,
    -134,  -134,  -134,   117,  -134,  -134,   116,   126,    55,  -134,
      82,    74,  -134,  -134,   326,   326,   382,   107,  -134,  -134,
    -134,  -134,  -134,   382,  -134,    97,  -134,  -134,   108,   -18,
    -134,  -134,   326,   326,   382,  -134,  -134,  -134,  -134,     0,
     382,    44
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    16,    17,    18,    19,     0,     2,     4,     5,     0,
       0,     6,     1,     3,     0,     0,    11,    12,    14,     0,
       0,     0,    24,    26,     7,     0,     0,     0,     0,     0,
      23,    30,    27,    29,     0,     0,    10,    14,   113,   115,
     114,   116,     0,   100,    98,    99,     0,   103,    13,    74,
      76,    78,    80,    88,    92,     0,    97,   101,   102,   106,
     107,     0,     0,     0,    43,    47,     0,     0,     0,     0,
       0,     0,     9,    49,     0,    51,    32,    33,    34,    35,
       0,     0,    37,    40,    36,    41,    38,    39,     0,    67,
     101,     0,     0,    21,    25,     0,    77,     0,     0,     0,
       0,    85,    83,    81,    82,    84,    86,    89,    90,     0,
       0,    93,    94,    95,     0,    96,    15,    22,     0,    63,
       0,     0,     0,     0,    61,     0,    46,    48,     0,    45,
      50,    42,    69,    70,    71,    72,    65,    66,    68,     0,
      31,    28,   105,     0,   109,   112,     0,   110,    73,    75,
      79,    87,    91,    20,     0,     0,     0,     0,    62,    44,
      64,   104,   108,     0,    53,    32,    55,    57,     0,     0,
       8,   111,     0,     0,     0,    52,    54,    56,    58,    59,
       0,    60
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -134,  -134,  -134,   147,   -19,    77,    38,   134,  -134,     1,
       6,  -134,   135,  -134,   127,  -134,    75,   -76,  -124,  -133,
    -134,   -16,  -134,    84,  -134,  -134,  -134,  -134,  -134,  -134,
    -134,   -38,  -134,   -24,    67,   -37,  -134,  -134,    56,  -134,
      58,  -134,   -47,  -134,  -134,   -26,  -134,  -134,  -134,  -134,
    -134
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     5,     6,     7,     8,    73,    15,    16,    17,    47,
      20,    11,    21,    22,    23,    32,    33,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,   168,    86,
      87,    88,   139,    89,    49,    50,    51,   109,    52,   110,
      53,   114,    54,    55,    56,    90,    58,    59,   146,   147,
      60
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      57,     9,    48,    30,    95,   130,    10,     9,   115,    96,
      72,    18,    10,    38,     1,    39,    40,    41,    93,    12,
      57,    31,   167,     2,     3,     4,    37,    14,   174,    57,
     165,   166,     1,   125,    42,    74,    19,    43,    99,   176,
     178,    57,    57,   120,   121,    26,   117,   180,   175,   177,
      44,    45,   130,     2,     3,     4,    99,   154,    29,   143,
     145,    72,    34,   149,    99,   155,    62,   152,    35,    99,
     122,     1,    61,    57,    57,    37,   123,    91,   164,     2,
       3,     4,    27,    57,    57,    27,    74,    28,    57,   101,
     102,   103,    92,    31,   132,   133,   134,   135,   136,   137,
      99,   160,   153,   138,     2,     3,     4,    24,    25,   104,
     105,   106,   100,   107,   108,   118,   111,   112,   113,    97,
     119,    98,   107,   108,    37,   171,   170,    25,   116,   131,
      57,   142,   169,   140,    38,     1,    39,    40,    41,   156,
     158,   161,   162,     2,     3,     4,   163,   172,    57,    64,
     179,    29,    65,    13,    57,    42,   181,   127,    43,    36,
     173,   157,    94,    63,   128,   150,   148,   141,   151,     0,
       0,    44,    45,     0,     0,    66,     0,     0,    67,     0,
       0,    68,     0,    69,    46,    70,     0,     0,    71,    38,
       1,    39,    40,    41,     0,     0,     0,     0,     2,     3,
       4,     0,     0,     0,    64,     0,    29,   126,     0,     0,
      42,     0,     0,    43,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    44,    45,     0,     0,
      66,     0,     0,    67,     0,     0,    68,     0,    69,    46,
      70,     0,     0,    71,    38,     1,    39,    40,    41,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    64,
       0,    29,   129,     0,     0,    42,     0,     0,    43,     0,
       0,    38,     1,    39,    40,    41,     0,     0,     0,     0,
       0,    44,    45,     0,     0,    66,   124,     0,    67,     0,
       0,    68,    42,    69,    46,    43,     0,     0,    71,    38,
       1,    39,    40,    41,     0,     0,     0,     0,    44,    45,
       0,     0,     0,     0,    64,     0,    29,   159,     0,     0,
      42,    46,     0,    43,     0,     0,     0,     0,     0,     0,
      38,     1,    39,    40,    41,     0,    44,    45,     0,     0,
      66,     0,     0,    67,     0,    64,    68,    29,    69,    46,
       0,    42,     0,    71,    43,     0,     0,     0,     0,     0,
       0,    38,     1,    39,    40,    41,     0,    44,    45,     0,
       0,    66,     0,     0,    67,     0,     0,    68,     0,    69,
      46,     0,    42,   144,    71,    43,    38,     1,    39,    40,
      41,     0,     0,     0,     0,     0,     0,     0,    44,    45,
       0,     0,     0,     0,     0,     0,     0,    42,     0,     0,
      43,    46,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    44,    45,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    46
};

static const yytype_int16 yycheck[] =
{
      26,     0,    26,    19,    42,    81,     0,     6,    55,    46,
      29,    10,     6,     4,     5,     6,     7,     8,    34,     0,
      46,    20,   155,    13,    14,    15,    25,    25,    46,    55,
     154,   155,     5,    71,    25,    29,    26,    28,    56,   172,
     173,    67,    68,    67,    68,    27,    62,    47,   172,   173,
      41,    42,   128,    13,    14,    15,    56,    49,    21,    97,
      98,    80,    26,   100,    56,    52,    26,   114,    19,    56,
      69,     5,     4,    99,   100,    74,    70,    23,   154,    13,
      14,    15,    23,   109,   110,    23,    80,    25,   114,    16,
      17,    18,    20,    92,    30,    31,    32,    33,    34,    35,
      56,   139,   118,    39,    13,    14,    15,    19,    20,    36,
      37,    38,    57,    40,    41,    26,    42,    43,    44,    23,
      19,    25,    40,    41,   123,   163,    19,    20,    24,    19,
     156,    26,   156,    24,     4,     5,     6,     7,     8,    39,
      19,    24,    26,    13,    14,    15,    20,    50,   174,    19,
     174,    21,    22,     6,   180,    25,   180,    80,    28,    25,
      52,   123,    35,    28,    80,   109,    99,    92,   110,    -1,
      -1,    41,    42,    -1,    -1,    45,    -1,    -1,    48,    -1,
      -1,    51,    -1,    53,    54,    55,    -1,    -1,    58,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    -1,    13,    14,
      15,    -1,    -1,    -1,    19,    -1,    21,    22,    -1,    -1,
      25,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,
      45,    -1,    -1,    48,    -1,    -1,    51,    -1,    53,    54,
      55,    -1,    -1,    58,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,
      -1,    21,    22,    -1,    -1,    25,    -1,    -1,    28,    -1,
      -1,     4,     5,     6,     7,     8,    -1,    -1,    -1,    -1,
      -1,    41,    42,    -1,    -1,    45,    19,    -1,    48,    -1,
      -1,    51,    25,    53,    54,    28,    -1,    -1,    58,     4,
       5,     6,     7,     8,    -1,    -1,    -1,    -1,    41,    42,
      -1,    -1,    -1,    -1,    19,    -1,    21,    22,    -1,    -1,
      25,    54,    -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,
       4,     5,     6,     7,     8,    -1,    41,    42,    -1,    -1,
      45,    -1,    -1,    48,    -1,    19,    51,    21,    53,    54,
      -1,    25,    -1,    58,    28,    -1,    -1,    -1,    -1,    -1,
      -1,     4,     5,     6,     7,     8,    -1,    41,    42,    -1,
      -1,    45,    -1,    -1,    48,    -1,    -1,    51,    -1,    53,
      54,    -1,    25,    26,    58,    28,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,
      28,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,    13,    14,    15,    62,    63,    64,    65,    70,
      71,    72,     0,    64,    25,    67,    68,    69,    70,    26,
      71,    73,    74,    75,    19,    20,    27,    23,    25,    21,
      82,    70,    76,    77,    26,    19,    68,    70,     4,     6,
       7,     8,    25,    28,    41,    42,    54,    70,    94,    95,
      96,    97,    99,   101,   103,   104,   105,   106,   107,   108,
     111,     4,    26,    73,    19,    22,    45,    48,    51,    53,
      55,    58,    65,    66,    71,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    90,    91,    92,    94,
     106,    23,    20,    82,    75,    92,    96,    23,    25,    56,
      57,    16,    17,    18,    36,    37,    38,    40,    41,    98,
     100,    42,    43,    44,   102,   103,    24,    82,    26,    19,
      94,    94,    70,    71,    19,    92,    22,    66,    84,    22,
      78,    19,    30,    31,    32,    33,    34,    35,    39,    93,
      24,    77,    26,    92,    26,    92,   109,   110,    95,    96,
      99,   101,   103,    82,    49,    52,    39,    67,    19,    22,
      92,    24,    26,    20,    78,    79,    79,    80,    89,    94,
      19,    92,    50,    52,    46,    79,    80,    79,    80,    94,
      47,    94
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    61,    62,    63,    63,    64,    64,    65,    66,    66,
      67,    67,    68,    68,    69,    69,    70,    71,    71,    71,
      72,    72,    72,    72,    73,    74,    74,    75,    76,    76,
      77,    77,    78,    78,    79,    79,    79,    79,    79,    79,
      80,    80,    81,    81,    82,    82,    82,    82,    83,    83,
      84,    84,    85,    86,    86,    87,    87,    88,    88,    89,
      89,    90,    90,    91,    92,    92,    92,    92,    93,    93,
      93,    93,    93,    94,    94,    95,    95,    96,    96,    97,
      97,    98,    98,    98,    98,    98,    98,    99,    99,   100,
     100,   101,   101,   102,   102,   102,   103,   103,   104,   104,
     104,   105,   105,   106,   106,   107,   107,   107,   108,   108,
     109,   110,   110,   111,   111,   111,   111
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     4,     1,
       3,     1,     1,     3,     1,     4,     1,     1,     1,     1,
       6,     5,     5,     4,     1,     3,     1,     2,     3,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     4,     3,     3,     2,     2,     1,
       2,     1,     6,     4,     6,     4,     6,     4,     6,     3,
       5,     2,     3,     2,     3,     2,     2,     1,     1,     1,
       1,     1,     1,     3,     1,     3,     1,     2,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     3,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     4,     3,     1,     1,     4,     3,
       1,     3,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 87 "parser.y" /* yacc.c:1646  */
    { fullTree = (yyvsp[0].treeNode); }
#line 1523 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 90 "parser.y" /* yacc.c:1646  */
    { TreeNode *t = (yyvsp[-1].treeNode);
				  if (t != NULL)
				  {
					while (t->sibling != NULL)
						t = t->sibling;
					t->sibling = (yyvsp[0].treeNode);
					(yyval.treeNode) = (yyvsp[-1].treeNode);
				  }
				  else
				  {
					(yyval.treeNode) = (yyvsp[0].treeNode);
				  }
				}
#line 1541 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 103 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1547 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 106 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1553 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 107 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1559 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 110 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[-1].treeNode);
							  if ((yyvsp[-2].tokenData)->tokenclass == INT)
							  	(yyval.treeNode)->expType = Integer;
							  else if ((yyvsp[-2].tokenData)->tokenclass == BOOL)
								(yyval.treeNode)->expType = Boolean;
							  else if ((yyvsp[-2].tokenData)->tokenclass == CHAR)
								(yyval.treeNode)->expType = Char;
							  setSibling((yyval.treeNode)); }
#line 1572 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 120 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[-1].treeNode);
							  if ((yyvsp[-2].tokenData)->tokenclass == INT)
								(yyval.treeNode)->expType = Integer;
							  else if ((yyvsp[-2].tokenData)->tokenclass == BOOL)
								(yyval.treeNode)->expType = Boolean;
							  else if ((yyvsp[-2].tokenData)->tokenclass == CHAR)
							  	(yyval.treeNode)->expType = Char;
							  (yyval.treeNode)->isStatic = true;
							  setSibling((yyval.treeNode)); }
#line 1586 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 129 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1592 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 132 "parser.y" /* yacc.c:1646  */
    { TreeNode *t = (yyvsp[-2].treeNode);
						  if (t != NULL)
						  {
							while (t->sibling != NULL)
								t = t->sibling;
							t->sibling = (yyvsp[0].treeNode);
							(yyval.treeNode) = (yyvsp[-2].treeNode);
						  }
						  else
						  {
							(yyval.treeNode) = (yyvsp[0].treeNode);
						  } 
						}
#line 1610 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 145 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1616 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 148 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1622 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 149 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[-2].treeNode);
						  (yyval.treeNode)->child[0] = (yyvsp[0].treeNode); }
#line 1629 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 153 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode);
							  (yyval.treeNode)->nodekind = DeclK;
							  (yyval.treeNode)->subkind.decl = VarK; }
#line 1637 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 156 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[-3].treeNode);
							  (yyval.treeNode)->nodekind = DeclK;
							  (yyval.treeNode)->subkind.decl = VarK;
							  (yyval.treeNode)->isArray = true; }
#line 1646 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 162 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = newExpNode(IdK, (yyvsp[0].tokenData));
			  (yyval.treeNode)->attr.name = (yyvsp[0].tokenData)->id; }
#line 1653 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 165 "parser.y" /* yacc.c:1646  */
    { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 1659 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 166 "parser.y" /* yacc.c:1646  */
    { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 1665 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 167 "parser.y" /* yacc.c:1646  */
    { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 1671 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 170 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[-4].treeNode);
								  (yyval.treeNode)->nodekind = DeclK;
								  (yyval.treeNode)->subkind.decl = FuncK;
								  if ((yyvsp[-5].tokenData)->tokenclass == INT)
									(yyval.treeNode)->expType = Integer;
								  else if ((yyvsp[-5].tokenData)->tokenclass == BOOL)
									(yyval.treeNode)->expType = Boolean;
								  else if ((yyvsp[-5].tokenData)->tokenclass == CHAR)
									(yyval.treeNode)->expType = Char;
								  (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode); 
								  (yyval.treeNode)->child[1] = (yyvsp[0].treeNode); }
#line 1687 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 181 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[-4].treeNode);
								  (yyval.treeNode)->nodekind = DeclK;
								  (yyval.treeNode)->subkind.decl = FuncK;
								  (yyval.treeNode)->expType = Void;
								  (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
								  (yyval.treeNode)->child[1] = (yyvsp[0].treeNode); }
#line 1698 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 187 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[-3].treeNode);
								  (yyval.treeNode)->nodekind = DeclK;
								  (yyval.treeNode)->subkind.decl = FuncK;
								  if ((yyvsp[-4].tokenData)->tokenclass == INT)
									(yyval.treeNode)->expType = Integer;
								  else if ((yyvsp[-4].tokenData)->tokenclass == BOOL)
									(yyval.treeNode)->expType = Boolean;
								  else if ((yyvsp[-4].tokenData)->tokenclass == CHAR)
									(yyval.treeNode)->expType = Char;
								  (yyval.treeNode)->child[1] = (yyvsp[0].treeNode); }
#line 1713 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 197 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[-3].treeNode);
								  (yyval.treeNode)->nodekind = DeclK;
								  (yyval.treeNode)->subkind.decl = FuncK;
								  (yyval.treeNode)->expType = Void;
								  (yyval.treeNode)->child[1] = (yyvsp[0].treeNode); }
#line 1723 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 204 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1729 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 207 "parser.y" /* yacc.c:1646  */
    { TreeNode *t = (yyvsp[-2].treeNode);
							  if (t != NULL)
							  {
								while (t->sibling != NULL)
									t = t->sibling;
								t->sibling = (yyvsp[0].treeNode);
								(yyval.treeNode) = (yyvsp[-2].treeNode);
							  }
							  else
							  {
								(yyval.treeNode) = (yyvsp[0].treeNode);
							  } 
							}
#line 1747 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 220 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1753 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 223 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode);
					  if ((yyvsp[-1].tokenData)->tokenclass == INT)
						(yyval.treeNode)->expType = Integer;
					  else if ((yyvsp[-1].tokenData)->tokenclass == BOOL)
						(yyval.treeNode)->expType = Boolean;
					  else if ((yyvsp[-1].tokenData)->tokenclass == CHAR)
						(yyval.treeNode)->expType = Char;
					  setSibling((yyval.treeNode)); }
#line 1766 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 233 "parser.y" /* yacc.c:1646  */
    { TreeNode *t = (yyvsp[-2].treeNode);
						  if (t != NULL)
						  {
							while (t->sibling != NULL)
								t = t->sibling;
							t->sibling = (yyvsp[0].treeNode);
							(yyval.treeNode) = (yyvsp[-2].treeNode);
						  }
						  else
						  {
							(yyval.treeNode) = (yyvsp[0].treeNode);
						  }
						}
#line 1784 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 246 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1790 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 249 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode);
					  (yyval.treeNode)->nodekind = DeclK;
					  (yyval.treeNode)->subkind.decl = ParamK; }
#line 1798 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 252 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[-2].treeNode);
					  (yyval.treeNode)->nodekind = DeclK;
					  (yyval.treeNode)->subkind.decl = ParamK;
					  (yyval.treeNode)->isArray = true; }
#line 1807 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 258 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1813 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 259 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1819 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 262 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1825 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 263 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1831 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 264 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1837 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 265 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1843 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 266 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1849 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 267 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1855 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 270 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1861 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 271 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1867 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 274 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[-1].treeNode); }
#line 1873 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 275 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = newStmtNode(NullK, (yyvsp[0].tokenData)); }
#line 1879 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 278 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = newStmtNode(CompoundK, (yyvsp[-3].tokenData));
							  (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
							  (yyval.treeNode)->child[1] = (yyvsp[-1].treeNode); }
#line 1887 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 281 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = newStmtNode(CompoundK, (yyvsp[-2].tokenData));
							  (yyval.treeNode)->child[1] = (yyvsp[-1].treeNode); }
#line 1894 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 283 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = newStmtNode(CompoundK, (yyvsp[-2].tokenData));
							  (yyval.treeNode)->child[0] = (yyvsp[-1].treeNode); }
#line 1901 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 285 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = newStmtNode(CompoundK, (yyvsp[-1].tokenData)); }
#line 1907 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 288 "parser.y" /* yacc.c:1646  */
    { TreeNode *t = (yyvsp[-1].treeNode);
						  if (t != NULL)
						  {
							while (t->sibling != NULL)
								t = t->sibling;
							t->sibling = (yyvsp[0].treeNode);
							(yyval.treeNode) = (yyvsp[-1].treeNode);
						  }
						  else
						  {
							(yyval.treeNode) = (yyvsp[0].treeNode);
						  } }
#line 1924 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 300 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1930 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 303 "parser.y" /* yacc.c:1646  */
    { TreeNode *t = (yyvsp[-1].treeNode);
				  if (t != NULL)
				  {
					while (t->sibling != NULL)
						t = t->sibling;
					t->sibling = (yyvsp[0].treeNode);
					(yyval.treeNode) = (yyvsp[-1].treeNode);
				  }
				  else
				  {
					(yyval.treeNode) = (yyvsp[0].treeNode);
				  } }
#line 1947 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 315 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1953 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 318 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = newStmtNode(IfK, (yyvsp[-5].tokenData));
									  (yyval.treeNode)->child[0] = (yyvsp[-4].treeNode);
									  (yyval.treeNode)->child[1] = (yyvsp[-2].treeNode);
									  (yyval.treeNode)->child[2] = (yyvsp[0].treeNode); }
#line 1962 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 324 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = newStmtNode(IfK, (yyvsp[-3].tokenData));
								  (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
								  (yyval.treeNode)->child[1] = (yyvsp[0].treeNode); }
#line 1970 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 327 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = newStmtNode(IfK, (yyvsp[-5].tokenData));
								  (yyval.treeNode)->child[0] = (yyvsp[-4].treeNode); 
								  (yyval.treeNode)->child[1] = (yyvsp[-2].treeNode);
								  (yyval.treeNode)->child[2] = (yyvsp[0].treeNode); }
#line 1979 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 332 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = newStmtNode(WhileK, (yyvsp[-3].tokenData));
							  (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
							  (yyval.treeNode)->child[1] = (yyvsp[0].treeNode); }
#line 1987 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 335 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = newStmtNode(ForK, (yyvsp[-5].tokenData));
							  (yyval.treeNode)->child[0] = (yyvsp[-4].treeNode);
							  (yyval.treeNode)->child[0]->nodekind = DeclK;
							  (yyval.treeNode)->child[0]->subkind.decl = VarK;
							  (yyval.treeNode)->child[0]->expType = Integer;
							  (yyval.treeNode)->child[1] = (yyvsp[-2].treeNode);
							  (yyval.treeNode)->child[2] = (yyvsp[0].treeNode); }
#line 1999 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 344 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = newStmtNode(WhileK, (yyvsp[-3].tokenData));
							  (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
							  (yyval.treeNode)->child[1] = (yyvsp[0].treeNode); }
#line 2007 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 347 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = newStmtNode(ForK, (yyvsp[-5].tokenData));
							  (yyval.treeNode)->child[0] = (yyvsp[-4].treeNode);
							  (yyval.treeNode)->child[0]->nodekind = DeclK;
							  (yyval.treeNode)->child[0]->subkind.decl = VarK;
							  (yyval.treeNode)->child[0]->expType = Integer;
							  (yyval.treeNode)->child[1] = (yyvsp[-2].treeNode);
							  (yyval.treeNode)->child[2] = (yyvsp[0].treeNode); }
#line 2019 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 356 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = newStmtNode(RangeK, (yyvsp[-1].tokenData));
							  (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
							  (yyval.treeNode)->child[1] = (yyvsp[0].treeNode); }
#line 2027 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 359 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = newStmtNode(RangeK, (yyvsp[-3].tokenData));
							  (yyval.treeNode)->child[0] = (yyvsp[-4].treeNode);
							  (yyval.treeNode)->child[1] = (yyvsp[-2].treeNode);
							  (yyval.treeNode)->child[2] = (yyvsp[0].treeNode); }
#line 2036 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 365 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = newStmtNode(ReturnK, (yyvsp[-1].tokenData)); }
#line 2042 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 366 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = newStmtNode(ReturnK, (yyvsp[-2].tokenData));
					  (yyval.treeNode)->child[0] = (yyvsp[-1].treeNode); }
#line 2049 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 370 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = newStmtNode(BreakK, (yyvsp[-1].tokenData)); }
#line 2055 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 373 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = newExpNode(AssignK, (yyvsp[-1].tokenData));
					  (yyval.treeNode)->attr.op = (yyvsp[-1].tokenData)->tokenclass;
					  (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
					  (yyval.treeNode)->child[1] = (yyvsp[0].treeNode); }
#line 2064 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 377 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = newExpNode(AssignK, (yyvsp[0].tokenData));
					  (yyval.treeNode)->attr.op = (yyvsp[0].tokenData)->tokenclass;
					  (yyval.treeNode)->child[0] = (yyvsp[-1].treeNode); }
#line 2072 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 380 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = newExpNode(AssignK, (yyvsp[0].tokenData));
					  (yyval.treeNode)->attr.op = (yyvsp[0].tokenData)->tokenclass;
					  (yyval.treeNode)->child[0] = (yyvsp[-1].treeNode); }
#line 2080 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 383 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2086 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 386 "parser.y" /* yacc.c:1646  */
    { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2092 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 387 "parser.y" /* yacc.c:1646  */
    { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2098 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 388 "parser.y" /* yacc.c:1646  */
    { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2104 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 389 "parser.y" /* yacc.c:1646  */
    { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2110 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 390 "parser.y" /* yacc.c:1646  */
    { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2116 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 393 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = newExpNode(OpK, (yyvsp[-1].tokenData));
					  (yyval.treeNode)->attr.op = (yyvsp[-1].tokenData)->tokenclass;
					  (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
					  (yyval.treeNode)->child[1] = (yyvsp[0].treeNode); }
#line 2125 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 397 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2131 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 400 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = newExpNode(OpK, (yyvsp[-1].tokenData));
						  (yyval.treeNode)->attr.op = (yyvsp[-1].tokenData)->tokenclass;
						  (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
						  (yyval.treeNode)->child[1] = (yyvsp[0].treeNode); }
#line 2140 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 404 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2146 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 407 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = newExpNode(OpK, (yyvsp[-1].tokenData));
					  (yyval.treeNode)->attr.op = (yyvsp[-1].tokenData)->tokenclass;
					  (yyval.treeNode)->child[0] = (yyvsp[0].treeNode); }
#line 2154 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 410 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2160 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 413 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = newExpNode(OpK, (yyvsp[-1].tokenData));
                                          (yyval.treeNode)->attr.op = (yyvsp[-1].tokenData)->tokenclass;
					  (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
                                          (yyval.treeNode)->child[1] = (yyvsp[0].treeNode); }
#line 2169 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 417 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2175 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 420 "parser.y" /* yacc.c:1646  */
    { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2181 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 421 "parser.y" /* yacc.c:1646  */
    { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2187 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 422 "parser.y" /* yacc.c:1646  */
    { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2193 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 423 "parser.y" /* yacc.c:1646  */
    { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2199 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 424 "parser.y" /* yacc.c:1646  */
    { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2205 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 425 "parser.y" /* yacc.c:1646  */
    { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2211 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 428 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = newExpNode(OpK, (yyvsp[-1].tokenData));
					  (yyval.treeNode)->attr.op = (yyvsp[-1].tokenData)->tokenclass;
					  (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
					  (yyval.treeNode)->child[1] = (yyvsp[0].treeNode); }
#line 2220 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 432 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2226 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 435 "parser.y" /* yacc.c:1646  */
    { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2232 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 436 "parser.y" /* yacc.c:1646  */
    { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2238 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 439 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = newExpNode(OpK, (yyvsp[-1].tokenData));
					  (yyval.treeNode)->attr.op = (yyvsp[-1].tokenData)->tokenclass;
					  (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode); 
					  (yyval.treeNode)->child[1] = (yyvsp[0].treeNode); }
#line 2247 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 443 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2253 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 446 "parser.y" /* yacc.c:1646  */
    { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2259 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 447 "parser.y" /* yacc.c:1646  */
    { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2265 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 448 "parser.y" /* yacc.c:1646  */
    { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2271 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 451 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = newExpNode(OpK, (yyvsp[-1].tokenData));
					  if ((yyvsp[-1].tokenData)->tokenclass == SUB)
						(yyval.treeNode)->attr.op = CHSIGN;
					  else if ((yyvsp[-1].tokenData)->tokenclass == MUL)
						(yyval.treeNode)->attr.op = SIZEOF;
					  else
					  	(yyval.treeNode)->attr.op = (yyvsp[-1].tokenData)->tokenclass;
					  (yyval.treeNode)->child[0] = (yyvsp[0].treeNode); }
#line 2284 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 459 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2290 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 462 "parser.y" /* yacc.c:1646  */
    { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2296 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 463 "parser.y" /* yacc.c:1646  */
    { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2302 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 464 "parser.y" /* yacc.c:1646  */
    { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2308 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 467 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2314 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 468 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2320 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 471 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2326 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 472 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = newExpNode(OpK, (yyvsp[-2].tokenData));
						  (yyval.treeNode)->attr.op = (yyvsp[-2].tokenData)->tokenclass;
						  (yyval.treeNode)->child[0] = (yyvsp[-3].treeNode);
						  (yyval.treeNode)->child[1] = (yyvsp[-1].treeNode);
						  (yyval.treeNode)->child[0]->isArray = true; }
#line 2336 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 479 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[-1].treeNode); }
#line 2342 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 480 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2348 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 481 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2354 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 484 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[-3].treeNode);
					  (yyval.treeNode)->nodekind = ExpK;
					  (yyval.treeNode)->subkind.exp = CallK;
					  (yyval.treeNode)->child[0] = (yyvsp[-1].treeNode); }
#line 2363 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 488 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[-2].treeNode);
					  (yyval.treeNode)->nodekind = ExpK;
					  (yyval.treeNode)->subkind.exp = CallK; }
#line 2371 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 493 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2377 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 496 "parser.y" /* yacc.c:1646  */
    { TreeNode *t = (yyvsp[-2].treeNode);
					  if (t != NULL)
					  {
						while (t->sibling != NULL)
							t = t->sibling;
						t->sibling = (yyvsp[0].treeNode);
						(yyval.treeNode) = (yyvsp[-2].treeNode);
					  }
					  else
					  {
						(yyval.treeNode) = (yyvsp[0].treeNode);
					  } }
#line 2394 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 508 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2400 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 511 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = newExpNode(ConstantK, (yyvsp[0].tokenData));
				  (yyval.treeNode)->attr.value = (yyvsp[0].tokenData)->nvalue;
				  (yyval.treeNode)->expType = Integer;}
#line 2408 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 514 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = newExpNode(ConstantK, (yyvsp[0].tokenData));
                                  (yyval.treeNode)->attr.cvalue = (yyvsp[0].tokenData)->cvalue;
				  (yyval.treeNode)->expType = Char; }
#line 2416 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 517 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = newExpNode(ConstantK, (yyvsp[0].tokenData));
                                  (yyval.treeNode)->attr.string = (yyvsp[0].tokenData)->svalue;
				  (yyval.treeNode)->expType = Char;
					(yyval.treeNode)->isArray = true; }
#line 2425 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 521 "parser.y" /* yacc.c:1646  */
    { (yyval.treeNode) = newExpNode(ConstantK, (yyvsp[0].tokenData));
                                  (yyval.treeNode)->attr.value = (yyvsp[0].tokenData)->nvalue;
				  (yyval.treeNode)->expType = Boolean; }
#line 2433 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 2437 "parser.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 526 "parser.y" /* yacc.c:1906  */

extern int yydebug;
int main(int argc, char *argv[])
{
	int c, optind;
	int pflg = 0, dflg = 0, Dflg = 0, Pflg = 0, hflg = 0;

	while (1)
	{
		// hunt for a string of options
        	while ((c = ourGetopt(argc, argv, (char *)"dDpPh")) != EOF)
		{
			switch (c) {
				case 'd':
					dflg = 1;
				break;
				case 'D':
					Dflg = 1;
				break;
				case 'p':
					pflg = 1;
				break;
				case 'P':
					Pflg = 1;
				break;
				case 'h':
					hflg = 1;
				break;
			}
		}
		
		// pick off a nonoption
		if (optind < argc)
			optind++;
		else
			break;

	}

	numErrors = 0;
	numWarnings = 0;

	if (hflg == 1)
	{
		printf("usage -c [options] [sourcefile]\noptions:\n-d - turn on parser debugging\n-D - turn on symbol table debugging\n-h - print this usage message\n-p - print the abstract syntax tree\n-P - print the abstract syntax tree plus type information\n");
		exit(1);
	}
	else if (argc > 1 && !(yyin = fopen(argv[argc - 1], "r"))) 
	{
		// failed to open file
		//printf("ERROR: failed to open \'%s\'\n", argv[1]);
		fileError(argv[1]);
	}
	
	if (numErrors == 0)
	{
		// do the parsing
		if (dflg == 1)
			yydebug = 1;

		yyparse();
	}

	if (numErrors == 0)
	{
		// PRINT TREE HERE
		if (pflg == 1)
			printTree(fullTree, 0, false);

		SymbolTable *symbolTable = new SymbolTable; //instatiate new symbol table

		if (Dflg == 1)
		{
			symbolTable->debug(true);
		}

		semanticAnalysis(fullTree, symbolTable); //perform semantic analysis (may find errors here)
		TreeNode *main = (TreeNode *)symbolTable->lookupGlobal("main");

		if (main != NULL && main->nodekind == DeclK && main->subkind.decl == FuncK)
		{
			if (main->child[0] != NULL)
			{
				mainError(strdup("A function named 'main()' must be defined."));
			}
		}
		else
		{
			mainError(strdup("A function named 'main()' must be defined."));
		}

		if (numErrors == 0)
		{
			if (Pflg == 1)
				printTree(fullTree, 0, true);
		}
	}

	printf("Number of warnings: %d\n", numWarnings);        //WARNINGS
	printf("Number of errors: %d\n", numErrors);		// ERROR

	return 0;
}

void setSibling(TreeNode *tree)
{
	while(tree->sibling != NULL)
	{
		tree->sibling->expType = tree->expType;
		tree->sibling->isStatic = tree->isStatic;
		tree = tree->sibling;
	}
}

TreeNode *newStmtNode(StmtKind kind, TokenData *token, TreeNode *c0, TreeNode *c1, TreeNode *c2)
{
	TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
	int i;

	t->child[0] = NULL;
	t->child[1] = NULL;
	t->child[2] = NULL;

	t->value = NULL;
	t->ignore = false;
	t->ignoreWarn = false;
	t->isUsed = false;
	t->notScope = false;
	t->isStatic = false;
	t->isArray = false;

	t->expType = UndefinedType;
	
	if (t == NULL)
	{
		printf("Out of memory error at line %d\n", line);
	}
	else
	{
		for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
		t->sibling = NULL;
		t->nodekind = StmtK;
		t->subkind.stmt = kind;
		t->lineno = token->linenum;
	}

	return t;
}

TreeNode *newDeclNode(DeclKind kind, ExpType type, TokenData *token, TreeNode *c0, TreeNode *c1, TreeNode *c2)
{
    TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
    int i;

	t->child[0] = NULL;
	t->child[1] = NULL;
	t->child[2] = NULL;

	t->value = NULL;
	t->ignore = NULL;
	t->ignoreWarn = false;
	t->isUsed = false;
	t->notScope = false;
	t->isStatic = false;
	t->isArray = false;

	t->expType = UndefinedType;

    if (t == NULL)
    {
            printf("Out of memory error at line %d\n", line);
    }
    else
    {
            for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
            t->sibling = NULL;
            t->nodekind = DeclK;
            t->subkind.decl = kind;
            t->lineno = token->linenum;
    }

    return t;
}

TreeNode *newExpNode(ExpKind kind, TokenData *token, TreeNode *c0, TreeNode *c1, TreeNode *c2)
{
	TreeNode *t = (TreeNode *) malloc(sizeof(TreeNode));
	int i;

	t->child[0] = NULL;
	t->child[1] = NULL;
	t->child[2] = NULL;

	t->value = NULL;
	t->ignore = NULL;
	t->ignoreWarn = false;
	t->isUsed = false;
	t->notScope = false;
	t->isStatic = false;
	t->isArray = false;

	t->expType = UndefinedType;

	if (t == NULL)
	{
		printf("Out of memory error at line %d\n", line);
	}
	else
	{
		for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
		t->sibling = NULL;
		t->nodekind = ExpK;
		t->subkind.exp = kind;
		t->lineno = token->linenum;
  	}
	
	return t;
}

static int indentno = -3;

#define INDENT indentno+=3
#define UNINDENT indentno-=3

void printToken(OpKind token)
{
	switch (token)
	{
		case IF:
		case THEN:
		case ELSE:
		case WHILE:
		case TO:
		case BREAK:
		case FOR:
		case INC: fprintf(stdout,"++"); break;
		case DEC: fprintf(stdout,"--"); break;
		case ASGN: fprintf(stdout,":="); break;
		case LESSER: fprintf(stdout,"<"); break;
		case GREATER: fprintf(stdout,">"); break;
		case EQ: fprintf(stdout,"="); break;
		case GEQ: fprintf(stdout,">="); break;
		case LEQ: fprintf(stdout,"<="); break;
		case NEQ: fprintf(stdout,"><"); break;
		case LPAREN: fprintf(stdout,"("); break;
		case RPAREN: fprintf(stdout,")"); break;
		case LBRACKET: fprintf(stdout,"["); break;
		case RBRACKET: fprintf(stdout,"]"); break;
		case LCURLY: fprintf(stdout,"{"); break;
		case RCURLY: fprintf(stdout,"}"); break;
		case SEMICOLON: fprintf(stdout,";"); break;
		case QUESTION: fprintf(stdout,"?"); break;
		case ADD: fprintf(stdout,"+"); break;
		case SUB: fprintf(stdout,"-"); break;
		case MUL: fprintf(stdout,"*"); break;
		case DIV: fprintf(stdout,"/"); break;
		case MOD: fprintf(stdout,"%%"); break;	
		case NOT: fprintf(stdout,"not"); break;
		case AND: fprintf(stdout,"and"); break;
		case OR: fprintf(stdout,"or"); break;
		case ADDASS: fprintf(stdout,"+="); break;
		case SUBASS: fprintf(stdout,"-="); break;
		case MULASS: fprintf(stdout,"*="); break;
		case DIVASS: fprintf(stdout,"/="); break;
		case CHSIGN: fprintf(stdout,"chsign"); break;
		case SIZEOF: fprintf(stdout,"sizeof"); break;
		default: /* should never happen */
			fprintf(stdout,"Unknown token: %d",token);
	}
}

static void printSpaces(void)
{
	int i;
	for (i = 0; i < indentno; i++)
	{
		if (i % 3 == 0)
			fprintf(stdout,".");
		fprintf(stdout," ");
	}
}

void printTree(TreeNode *tree, int childNum, bool types)
{
	int i;
	INDENT;
	while (tree != NULL)
	{
		if (tree->nodekind == StmtK)
		{
			if (tree->subkind.stmt != NullK)
			{
				printSpaces();
			}
		}
		else printSpaces();
	
		if (childNum >= 0 && tree != fullTree && ((tree->nodekind == StmtK && tree->subkind.stmt != NullK) || (tree->nodekind != StmtK)))
		{
			fprintf(stdout,"Child: %d  ", childNum);
		}
		else if (tree != fullTree && ((tree->nodekind == StmtK && tree->subkind.stmt != NullK) || (tree->nodekind != StmtK)))
		{
			fprintf(stdout,"Sibling: %d  ", abs(childNum));
		}
		
		char *expType;
		if (tree->expType == Integer)
			expType = strdup("int");
		else if (tree->expType == Boolean)
			expType = strdup("bool");
		else if (tree->expType == Char)
			expType = strdup("char");
		else if (tree->expType == Void)
			expType = strdup("void");

		char *arrayCheck;
		if (tree->isArray)
			arrayCheck = strdup("is array ");
		else
			arrayCheck = strdup("");

		char *staticCheck;
		if (tree->isStatic && !types)
			staticCheck = strdup("static ");
		else
			staticCheck = strdup("");

		if (tree->nodekind == StmtK)
		{
			switch (tree->subkind.stmt) {
				case IfK:
					fprintf(stdout,"If");
				break;
				case WhileK:
					fprintf(stdout,"While");
				break;
				case ForK:
					fprintf(stdout,"For");
				break;
				case CompoundK:
					fprintf(stdout,"Compound");
				break;
				case ReturnK:
					fprintf(stdout,"Return");
				break;
				case BreakK:
                                        fprintf(stdout,"Break");
                                break;
				case RangeK:
                                        fprintf(stdout,"Range");
                                break;
				case NullK:
					//do nothing
				break;
				default:
					fprintf(stdout,"Unknown ExpNode kind");
				break;
			}
		}
		else if (tree->nodekind == ExpK)
		{
			switch (tree->subkind.exp)
			{
				case OpK:
					fprintf(stdout,"Op: ");
					printToken(tree->attr.op);
				break;
				case ConstantK:
					fprintf(stdout,"Const ");
					switch(tree->expType)
					{
						case Integer:
							fprintf(stdout,"%d", tree->attr.value);
						break;
						case Boolean:
							if (tree->attr.value == 0)
								fprintf(stdout,"false");
							else
								fprintf(stdout,"true");
						break;
						case Char:
							if (!tree->isArray)
								fprintf(stdout,"'%c'", tree->attr.cvalue);
							else
								fprintf(stdout,"is array \"%s\"", tree->attr.string);
						break;
						case String:
							fprintf(stdout,"\"%s\"", tree->attr.string);
						break;
					}
				break;
				case IdK:
					fprintf(stdout,"Id: %s", tree->attr.name);
				break;
				case AssignK:
                                        fprintf(stdout,"Assign: ");
					printToken(tree->attr.op);
                                break;
				case CallK:
					fprintf(stdout,"Call: %s", tree->attr.name);
                                break;
				default:
					fprintf(stdout,"Unknown ExpNode kind");
				break;
			}
		}
		else if (tree->nodekind == DeclK)
		{
			switch(tree->subkind.decl)
			{
				case VarK:
					fprintf(stdout,"Var: %s %sof %stype %s", tree->attr.name, arrayCheck, staticCheck, expType);
				break;
				case FuncK:
					fprintf(stdout,"Func: %s returns %stype %s", tree->attr.name, arrayCheck, expType);
				break;
				case ParamK:
					fprintf(stdout,"Parm: %s %sof type %s", tree->attr.name, arrayCheck, expType);
				break;
				default:
					fprintf(stdout,"Unknown ExpNode kind");
				break;
			}
		}
		else
		{
			fprintf(stdout,"Unknown node kind");
		}

		if (tree->nodekind != DeclK && tree->nodekind != StmtK)
		{
			switch(tree->expType)
			{
				case Integer:
					fprintf(stdout, " of type int");
				break;
				case Char:
					fprintf(stdout, " of type char");
				break;
				case Boolean:
					fprintf(stdout, " of type bool");
				break;
				case String:
					fprintf(stdout, " of type string");
				break;
				case Void:
					fprintf(stdout, " of type void");
				break;
				default:
					fprintf(stdout, " of undefined type");
				break;
			}
		}

		if ((tree->nodekind == StmtK && tree->subkind.stmt != NullK) || (tree->nodekind != StmtK))
			fprintf(stdout," [line: %d]\n", tree->lineno);
		
		for (i=0;i<MAXCHILDREN;i++)
		{
			printTree(tree->child[i], i, types);
		}
		tree = tree->sibling;
		
//		if (tree->nodekind == StmtK && tree->subkind.stmt == NullK)
		//	continue;
{
		if (childNum <= -1)
			childNum--;
		else
			childNum = -1;
}
	}
	UNINDENT;
}

