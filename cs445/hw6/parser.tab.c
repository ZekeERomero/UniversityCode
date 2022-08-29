/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include "scanType.h"  // TokenData Type
#include "ioruntime.h"
#include "ourgetopt.h"
#include "symbolTable.h"
#include "semantic.h"
#include "yyerror.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stack>

double vars[26];   

extern int yylex();
extern FILE *yyin;
extern int line;         // ERR line number from the scanner!!
extern int numErrors, numWarnings;    // ERR err count
extern int goffset;

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
void printToken(OpKind token, const char *tokenString);
static void printSpaces(void);
void printTree(TreeNode *tree, int childNum, bool types);
void printMemTree(TreeNode *tree, int childNum, bool types);
void setSibling(TreeNode *tree);
void IORuntime(SymbolTable* symbolTable);
char* removeDirectory(char* wholeName);

// prints out errors
#define YYERROR_VERBOSE
/*void yyerror(const char *msg)
{
	printf("ERROR(%d): %s\n", line, msg);
	numErrors++;
}*/

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

TreeNode* addSibling(TreeNode* tree, TreeNode* tree1)
{
	if (tree1 == NULL && numErrors == 0) {
        printf("ERROR(SYSTEM): never add a NULL to a sibling list.\n");
        exit(1);
    }
	if (tree != NULL)
	{
		TreeNode *t = tree;
		while (t->sibling != NULL)
			t = t->sibling;
		t->sibling = tree1;
		return tree;
	}

	return tree1;
}

ExpType setType(TokenData* node)
{
	ExpType returnType = UndefinedType;

	if (node->tokenclass == INT)
		returnType = Integer;
	else if (node->tokenclass == BOOL)
		returnType = Boolean;
	else if (node->tokenclass == CHAR)
		returnType = Char;

	return returnType;
}


#line 163 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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
#line 95 "parser.y"

	ExpType type;
	TokenData *tokenData;
	TreeNode *treeNode;

#line 281 "parser.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  18
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   837

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  165
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  267

#define YYUNDEFTOK  2
#define YYMAXUTOK   314


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      55,    56,    57,    58,    59
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   122,   122,   125,   126,   129,   130,   131,   134,   141,
     143,   146,   155,   162,   165,   170,   171,   172,   175,   176,
     182,   183,   186,   190,   195,   196,   199,   203,   204,   205,
     208,   214,   220,   225,   230,   231,   232,   233,   236,   239,
     240,   241,   242,   245,   252,   255,   256,   257,   258,   261,
     264,   270,   271,   274,   275,   276,   277,   278,   279,   282,
     283,   286,   287,   288,   291,   295,   298,   301,   305,   306,
     309,   310,   313,   317,   318,   319,   322,   325,   329,   330,
     333,   336,   346,   347,   348,   349,   352,   355,   365,   366,
     369,   372,   376,   377,   378,   381,   382,   384,   387,   390,
     394,   397,   400,   401,   402,   403,   404,   407,   408,   409,
     410,   411,   414,   418,   419,   422,   426,   427,   430,   433,
     434,   437,   441,   442,   445,   446,   447,   448,   449,   450,
     453,   457,   458,   461,   462,   465,   469,   470,   473,   474,
     475,   478,   486,   487,   490,   491,   492,   495,   496,   499,
     500,   507,   509,   510,   511,   514,   518,   521,   524,   527,
     529,   530,   533,   536,   539,   544
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "QUIT", "NUMCONST", "ID", "STRINGCONST",
  "CHARCONST", "BOOLCONST", "NONCHAR", "ILLEGALCHAR", "KEYWORD", "BOOL",
  "CHAR", "INT", "EQ", "GREATER", "LESSER", "SEMICOLON", "COMMA", "LCURLY",
  "RCURLY", "LBRACKET", "RBRACKET", "LPAREN", "RPAREN", "COLON",
  "QUESTION", "MATHOP", "ADDASS", "SUBASS", "MULASS", "DIVASS", "INC",
  "DEC", "LEQ", "GEQ", "NEQ", "ASGN", "ADD", "SUB", "MUL", "DIV", "MOD",
  "BREAK", "TO", "BY", "IF", "THEN", "ELSE", "WHILE", "DO", "FOR", "NOT",
  "STATIC", "OR", "AND", "RETURN", "CHSIGN", "SIZEOF", "$accept",
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
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314
};
# endif

#define YYPACT_NINF (-167)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-49)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     247,   490,  -167,  -167,  -167,  -167,    17,   544,  -167,  -167,
      -2,   125,  -167,   151,   124,  -167,     5,    23,  -167,  -167,
     121,    80,   210,   273,  -167,   358,  -167,   139,   443,   208,
      15,    31,   144,    58,    50,  -167,  -167,  -167,   182,    87,
    -167,  -167,  -167,  -167,   473,  -167,  -167,  -167,   481,   324,
      30,    57,  -167,  -167,    65,   200,  -167,    20,  -167,  -167,
    -167,  -167,  -167,   151,  -167,    87,    30,  -167,    97,   226,
    -167,   108,   126,   142,  -167,    34,   205,    15,    31,   155,
    -167,   499,   178,    30,   285,    87,  -167,   511,   250,   535,
     562,  -167,  -167,  -167,  -167,  -167,  -167,  -167,  -167,   146,
     769,  -167,  -167,  -167,   778,    87,  -167,  -167,   782,  -167,
    -167,   195,   573,   600,   167,   251,   304,  -167,   170,  -167,
    -167,  -167,  -167,  -167,   280,   334,  -167,  -167,  -167,  -167,
    -167,  -167,   202,   213,   196,  -167,  -167,  -167,  -167,  -167,
      31,  -167,  -167,  -167,  -167,  -167,  -167,  -167,   511,  -167,
    -167,  -167,   615,   499,   222,  -167,  -167,   224,   150,    87,
      57,    87,  -167,    87,   149,    87,   200,    87,  -167,  -167,
    -167,    28,    61,    -9,    11,  -167,   187,   199,   799,  -167,
     244,    89,   253,  -167,  -167,   388,  -167,  -167,  -167,  -167,
    -167,  -167,  -167,  -167,   499,  -167,  -167,  -167,   624,   158,
     419,   158,   158,   158,   665,   307,  -167,  -167,  -167,  -167,
    -167,   499,  -167,  -167,   219,   674,   689,   167,  -167,  -167,
     220,  -167,  -167,  -167,  -167,    -8,   231,     3,  -167,   158,
      43,    69,     6,   171,   258,   158,   288,   158,   158,   716,
    -167,  -167,   419,   419,   419,   419,   727,  -167,  -167,  -167,
    -167,  -167,  -167,  -167,    87,   -26,   257,   264,    -5,   248,
     754,   419,   419,   419,   419,    87,    30
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    26,    27,    28,    29,     0,     0,     4,     5,
       0,     0,     6,    17,     0,    15,    18,    22,     1,     3,
       0,    34,     0,    22,    25,     0,     9,     0,     0,     0,
      36,     0,     0,     0,    38,    40,    10,     8,     0,     0,
     162,   164,   163,   165,     0,   146,   144,   145,     0,   149,
      21,   113,   116,   119,   122,   131,   136,     0,   142,   147,
     148,   152,   153,    16,    14,    20,    19,    24,     0,     0,
      33,    44,    49,    43,    46,     0,     0,    35,     0,     0,
     157,   154,     0,   102,   147,   120,   118,     0,     0,     0,
       0,   128,   126,   124,   125,   127,   129,   133,   134,     0,
       0,   138,   139,   140,     0,   143,   141,    23,     0,    62,
      67,     0,     0,     0,     0,     0,     0,    69,     0,    71,
      51,    52,    53,    54,     0,     0,    56,    59,    55,    60,
      57,    58,     0,     0,     0,    37,    31,    41,    39,    32,
       0,   108,   109,   110,   111,   105,   106,   107,     0,   151,
     100,   101,     0,     0,     0,   156,   160,     0,   158,   114,
     112,   117,   115,   123,   121,   132,   130,   137,   135,    63,
      98,    73,     0,    83,     0,    85,     0,     0,     0,    95,
       0,    17,     0,    66,    68,     0,    65,    70,    61,    50,
      47,    45,    30,   103,   104,    99,   150,   155,     0,     0,
       0,     0,     0,     0,     0,     0,    97,    96,    13,    12,
      64,   161,   159,    78,    51,     0,     0,     0,    74,    76,
      51,    82,    88,    80,    86,     0,     0,     0,    11,     0,
      73,     0,    83,     0,     0,     0,     0,     0,     0,     0,
      75,    79,     0,     0,     0,     0,     0,    72,    77,    93,
      84,    89,    81,    87,    92,    90,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    94,    91
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -167,  -167,  -167,   295,  -167,   212,   -10,   302,  -167,     7,
       4,  -167,   305,  -167,   271,  -167,   215,  -115,  -106,  -166,
    -167,   -22,  -167,   227,  -167,  -167,  -167,  -167,   104,  -167,
    -167,   -38,   269,   -23,   267,   -35,  -167,  -167,   261,  -167,
     268,  -167,   -45,  -167,  -167,   -25,  -167,  -167,  -167,  -167,
    -167
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,     9,   117,    14,    15,    16,    49,
      32,    12,    33,    34,    35,    73,    74,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   226,   130,
     131,   132,   148,    83,    51,    52,    53,    99,    54,   100,
      55,   104,    56,    57,    58,    84,    60,    61,   157,   158,
      62
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      59,    22,    50,    59,    11,    66,    82,    10,    17,    70,
     187,    11,   106,    86,    10,    80,    80,    18,    23,    80,
     260,   105,    20,    59,    40,     2,    41,    42,    43,    89,
      80,    28,    59,   -42,    17,   135,   222,   224,   236,    72,
     -42,   236,   202,   237,    44,    29,   263,    45,   239,   154,
     156,    69,    80,   136,    69,   162,   139,   244,    89,   168,
      46,    47,   203,   241,    59,    59,    89,    80,    76,   248,
     187,   251,   253,   118,    59,    59,   199,   200,   180,    59,
      91,    92,    93,    75,   213,    89,   219,    59,    59,   172,
     174,   242,   200,   214,   218,   220,   221,   223,    36,   -17,
      94,    95,    96,    24,    97,    98,    25,   208,   182,   201,
     193,    80,    24,    90,   195,    25,    89,   243,   192,   177,
     107,   176,    30,   240,    89,    17,    21,   -48,   118,   247,
       2,   250,   252,     3,     4,     5,   256,   257,   221,   223,
      63,    72,    26,    27,     2,    71,    31,   163,   133,     2,
      40,     2,    41,    42,    43,   240,   247,   250,   252,   108,
     212,   134,    40,     2,    41,    42,    43,   205,   175,   198,
      44,   181,     2,    45,    24,     2,   109,    25,    69,    59,
     140,   227,    44,    77,    17,    45,    46,    47,    97,    98,
      59,    59,   231,   233,     3,     4,     5,   190,    46,    47,
      13,     2,   111,   149,     2,   112,   137,    78,   113,    67,
     114,    48,    68,   170,    59,   116,   255,     3,     4,     5,
     188,    59,   245,   227,   234,   204,    89,   108,    37,    27,
      40,     2,    41,    42,    43,    59,   189,   266,     3,     4,
       5,   101,   102,   103,   109,   196,    69,   110,     1,   197,
      44,   153,     2,    45,    40,     2,    41,    42,    43,     3,
       4,     5,   207,     3,     4,     5,    46,    47,   229,   235,
     111,   209,    27,   112,    44,   155,   113,    45,   114,    48,
     115,   108,   238,   116,    40,     2,    41,    42,    43,   249,
      46,    47,     3,     4,     5,    29,   246,    38,   109,   264,
      69,   183,    19,    48,    44,   178,   261,    45,    40,     2,
      41,    42,    43,   262,   141,   142,   143,   144,   150,   151,
      46,    47,   179,   147,   111,   228,    27,   112,    44,    64,
     113,    45,   114,    48,   115,   108,   184,   116,    40,     2,
      41,    42,    43,    79,    46,    47,    87,   138,    88,   191,
     259,   185,   109,   152,    69,   186,   160,    48,    44,    39,
     164,    45,    40,     2,    41,    42,    43,     0,   166,     0,
       0,     0,     0,     0,    46,    47,     0,     0,   111,     0,
       0,   112,    44,     0,   113,    45,   114,    48,     0,   108,
       0,   116,    40,     2,    41,    42,    43,     0,    46,    47,
       0,     0,     0,     0,     0,     0,   109,     0,    69,   210,
       0,    48,    44,     0,     0,    45,     0,     0,     0,     0,
     108,     0,     0,    40,     2,    41,    42,    43,    46,    47,
       0,     0,   111,     0,     0,   112,     0,   109,   113,    69,
     114,    48,     0,    44,    65,   116,    45,    40,     2,    41,
      42,    43,     0,     0,     0,     0,     0,     0,     0,    46,
      47,     0,     0,   111,     0,     0,   215,    44,     0,   216,
      45,   217,    48,     0,    81,     0,   116,    40,     2,    41,
      42,    43,    85,    46,    47,    40,     2,    41,    42,    43,
      -7,    13,     0,     0,     0,     2,    48,    44,     0,     0,
      45,     0,    -7,    -7,    -7,    44,     0,     0,    45,     0,
       0,     0,   153,    46,    47,    40,     2,    41,    42,    43,
       0,    46,    47,    80,     0,     0,    48,     0,   141,   142,
     143,   144,   145,   146,    48,    44,   159,   147,    45,    40,
       2,    41,    42,    43,    -2,     1,     0,     0,     0,     2,
       0,    46,    47,     0,     0,     0,     3,     4,     5,    44,
       0,     0,    45,   161,    48,     0,    40,     2,    41,    42,
      43,     0,     0,     0,   171,    46,    47,    40,     2,    41,
      42,    43,     0,     0,     0,     0,    44,     0,    48,    45,
       0,     0,     0,     0,     0,     0,     0,    44,     0,     0,
      45,   173,    46,    47,    40,     2,    41,    42,    43,     0,
       0,     0,     0,    46,    47,    48,   194,     0,     0,    40,
       2,    41,    42,    43,    44,   211,    48,    45,    40,     2,
      41,    42,    43,     0,     0,     0,     0,     0,     0,    44,
      46,    47,    45,     0,     0,     0,     0,     0,    44,     0,
       0,    45,     0,    48,     0,    46,    47,     0,     0,     0,
       0,     0,     0,     0,    46,    47,   225,     0,    48,    40,
       2,    41,    42,    43,     0,   230,     0,    48,    40,     2,
      41,    42,    43,     0,     0,     0,     0,     0,     0,    44,
     232,     0,    45,    40,     2,    41,    42,    43,    44,     0,
       0,    45,     0,     0,     0,    46,    47,     0,     0,     0,
       0,     0,     0,    44,    46,    47,    45,   254,    48,     0,
      40,     2,    41,    42,    43,     0,     0,    48,   258,    46,
      47,    40,     2,    41,    42,    43,     0,     0,     0,     0,
      44,     0,    48,    45,     0,     0,     0,     0,     0,     0,
       0,    44,     0,     0,    45,   265,    46,    47,    40,     2,
      41,    42,    43,     0,     0,     0,     0,    46,    47,    48,
     165,     0,     0,    40,     2,    41,    42,    43,    44,   167,
      48,    45,    40,     2,    41,    42,    43,     0,     0,     0,
       0,     0,     0,    44,    46,    47,    45,     0,     0,     0,
     169,     0,    44,     0,     0,    45,    80,    48,     0,    46,
      47,   141,   142,   143,   144,   145,   146,   206,    46,    47,
     147,     0,     0,    80,     0,     0,     0,     0,   141,   142,
     143,   144,   145,   146,     0,     0,     0,   147
};

static const yytype_int16 yycheck[] =
{
      25,    11,    25,    28,     0,    28,    44,     0,     1,    31,
     125,     7,    57,    48,     7,    24,    24,     0,    11,    24,
      46,     1,    24,    48,     4,     5,     6,     7,     8,    55,
      24,    26,    57,    18,    27,     1,   202,   203,    46,    32,
      25,    46,    51,    51,    24,    22,    51,    27,    45,    87,
      88,    20,    24,    75,    20,    90,    78,    51,    55,   104,
      40,    41,    51,   229,    89,    90,    55,    24,    18,   235,
     185,   237,   238,    69,    99,   100,    48,    49,   116,   104,
      15,    16,    17,    25,   199,    55,   201,   112,   113,   112,
     113,    48,    49,   199,   200,   201,   202,   203,    18,    19,
      35,    36,    37,    23,    39,    40,    26,    18,   118,    48,
     148,    24,    23,    56,   152,    26,    55,    48,   140,   115,
      23,   114,     1,   229,    55,   118,     1,    19,   124,   235,
       5,   237,   238,    12,    13,    14,   242,   243,   244,   245,
       1,   134,    18,    19,     5,     1,    25,     1,    22,     5,
       4,     5,     6,     7,     8,   261,   262,   263,   264,     1,
     198,    19,     4,     5,     6,     7,     8,   177,     1,    19,
      24,     1,     5,    27,    23,     5,    18,    26,    20,   204,
      25,   204,    24,     1,   177,    27,    40,    41,    39,    40,
     215,   216,   215,   216,    12,    13,    14,     1,    40,    41,
       1,     5,    44,    25,     5,    47,     1,    25,    50,     1,
      52,    53,     4,    18,   239,    57,   239,    12,    13,    14,
      18,   246,    51,   246,   217,    38,    55,     1,    18,    19,
       4,     5,     6,     7,     8,   260,    23,   260,    12,    13,
      14,    41,    42,    43,    18,    23,    20,    21,     1,    25,
      24,     1,     5,    27,     4,     5,     6,     7,     8,    12,
      13,    14,    18,    12,    13,    14,    40,    41,    49,    49,
      44,    18,    19,    47,    24,    25,    50,    27,    52,    53,
      54,     1,    51,    57,     4,     5,     6,     7,     8,     1,
      40,    41,    12,    13,    14,    22,    38,    24,    18,    51,
      20,    21,     7,    53,    24,     1,    49,    27,     4,     5,
       6,     7,     8,    49,    29,    30,    31,    32,    33,    34,
      40,    41,    18,    38,    44,    18,    19,    47,    24,    27,
      50,    27,    52,    53,    54,     1,   124,    57,     4,     5,
       6,     7,     8,    38,    40,    41,    22,    76,    24,   134,
     246,   124,    18,    84,    20,    21,    89,    53,    24,     1,
      99,    27,     4,     5,     6,     7,     8,    -1,   100,    -1,
      -1,    -1,    -1,    -1,    40,    41,    -1,    -1,    44,    -1,
      -1,    47,    24,    -1,    50,    27,    52,    53,    -1,     1,
      -1,    57,     4,     5,     6,     7,     8,    -1,    40,    41,
      -1,    -1,    -1,    -1,    -1,    -1,    18,    -1,    20,    21,
      -1,    53,    24,    -1,    -1,    27,    -1,    -1,    -1,    -1,
       1,    -1,    -1,     4,     5,     6,     7,     8,    40,    41,
      -1,    -1,    44,    -1,    -1,    47,    -1,    18,    50,    20,
      52,    53,    -1,    24,     1,    57,    27,     4,     5,     6,
       7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,
      41,    -1,    -1,    44,    -1,    -1,    47,    24,    -1,    50,
      27,    52,    53,    -1,     1,    -1,    57,     4,     5,     6,
       7,     8,     1,    40,    41,     4,     5,     6,     7,     8,
       0,     1,    -1,    -1,    -1,     5,    53,    24,    -1,    -1,
      27,    -1,    12,    13,    14,    24,    -1,    -1,    27,    -1,
      -1,    -1,     1,    40,    41,     4,     5,     6,     7,     8,
      -1,    40,    41,    24,    -1,    -1,    53,    -1,    29,    30,
      31,    32,    33,    34,    53,    24,     1,    38,    27,     4,
       5,     6,     7,     8,     0,     1,    -1,    -1,    -1,     5,
      -1,    40,    41,    -1,    -1,    -1,    12,    13,    14,    24,
      -1,    -1,    27,     1,    53,    -1,     4,     5,     6,     7,
       8,    -1,    -1,    -1,     1,    40,    41,     4,     5,     6,
       7,     8,    -1,    -1,    -1,    -1,    24,    -1,    53,    27,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,
      27,     1,    40,    41,     4,     5,     6,     7,     8,    -1,
      -1,    -1,    -1,    40,    41,    53,     1,    -1,    -1,     4,
       5,     6,     7,     8,    24,     1,    53,    27,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    24,
      40,    41,    27,    -1,    -1,    -1,    -1,    -1,    24,    -1,
      -1,    27,    -1,    53,    -1,    40,    41,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    40,    41,     1,    -1,    53,     4,
       5,     6,     7,     8,    -1,     1,    -1,    53,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    24,
       1,    -1,    27,     4,     5,     6,     7,     8,    24,    -1,
      -1,    27,    -1,    -1,    -1,    40,    41,    -1,    -1,    -1,
      -1,    -1,    -1,    24,    40,    41,    27,     1,    53,    -1,
       4,     5,     6,     7,     8,    -1,    -1,    53,     1,    40,
      41,     4,     5,     6,     7,     8,    -1,    -1,    -1,    -1,
      24,    -1,    53,    27,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    24,    -1,    -1,    27,     1,    40,    41,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    -1,    40,    41,    53,
       1,    -1,    -1,     4,     5,     6,     7,     8,    24,     1,
      53,    27,     4,     5,     6,     7,     8,    -1,    -1,    -1,
      -1,    -1,    -1,    24,    40,    41,    27,    -1,    -1,    -1,
      18,    -1,    24,    -1,    -1,    27,    24,    53,    -1,    40,
      41,    29,    30,    31,    32,    33,    34,    18,    40,    41,
      38,    -1,    -1,    24,    -1,    -1,    -1,    -1,    29,    30,
      31,    32,    33,    34,    -1,    -1,    -1,    38
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     5,    12,    13,    14,    61,    62,    63,    64,
      69,    70,    71,     1,    66,    67,    68,    69,     0,    63,
      24,     1,    66,    69,    23,    26,    18,    19,    26,    22,
       1,    25,    70,    72,    73,    74,    18,    18,    24,     1,
       4,     6,     7,     8,    24,    27,    40,    41,    53,    69,
      93,    94,    95,    96,    98,   100,   102,   103,   104,   105,
     106,   107,   110,     1,    67,     1,    93,     1,     4,    20,
      81,     1,    69,    75,    76,    25,    18,     1,    25,    72,
      24,     1,    91,    93,   105,     1,    95,    22,    24,    55,
      56,    15,    16,    17,    35,    36,    37,    39,    40,    97,
      99,    41,    42,    43,   101,     1,   102,    23,     1,    18,
      21,    44,    47,    50,    52,    54,    57,    65,    70,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      89,    90,    91,    22,    19,     1,    81,     1,    74,    81,
      25,    29,    30,    31,    32,    33,    34,    38,    92,    25,
      33,    34,    92,     1,    91,    25,    91,   108,   109,     1,
      94,     1,    95,     1,    98,     1,   100,     1,   102,    18,
      18,     1,    93,     1,    93,     1,    69,    70,     1,    18,
      91,     1,    66,    21,    65,    83,    21,    77,    18,    23,
       1,    76,    81,    91,     1,    91,    23,    25,    19,    48,
      49,    48,    51,    51,    38,    66,    18,    18,    18,    18,
      21,     1,    91,    77,    78,    47,    50,    52,    78,    77,
      78,    78,    79,    78,    79,     1,    88,    93,    18,    49,
       1,    93,     1,    93,    69,    49,    46,    51,    51,    45,
      78,    79,    48,    48,    51,    51,    38,    78,    79,     1,
      78,    79,    78,    79,     1,    93,    78,    78,     1,    88,
      46,    49,    49,    51,    51,     1,    93
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    60,    61,    62,    62,    63,    63,    63,    64,    64,
      64,    65,    65,    65,    66,    66,    66,    66,    67,    67,
      67,    67,    68,    68,    68,    68,    69,    70,    70,    70,
      71,    71,    71,    71,    71,    71,    71,    71,    72,    73,
      73,    73,    73,    74,    74,    75,    75,    75,    75,    76,
      76,    77,    77,    78,    78,    78,    78,    78,    78,    79,
      79,    80,    80,    80,    81,    81,    81,    81,    82,    82,
      83,    83,    84,    84,    84,    84,    85,    85,    85,    85,
      86,    86,    86,    86,    86,    86,    87,    87,    87,    87,
      88,    88,    88,    88,    88,    89,    89,    89,    90,    91,
      91,    91,    91,    91,    91,    91,    91,    92,    92,    92,
      92,    92,    93,    93,    93,    94,    94,    94,    95,    95,
      95,    96,    96,    96,    97,    97,    97,    97,    97,    97,
      98,    98,    98,    99,    99,   100,   100,   100,   101,   101,
     101,   102,   102,   102,   103,   103,   103,   104,   104,   105,
     105,   106,   106,   106,   106,   107,   107,   107,   108,   109,
     109,   109,   110,   110,   110,   110
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     3,     3,
       3,     4,     3,     3,     3,     1,     3,     1,     1,     3,
       3,     3,     1,     4,     3,     2,     1,     1,     1,     1,
       6,     5,     5,     4,     2,     4,     3,     5,     1,     3,
       1,     3,     1,     2,     2,     3,     1,     3,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     2,     4,     3,     3,     2,     2,     1,
       2,     1,     6,     2,     4,     6,     4,     6,     4,     6,
       4,     6,     4,     2,     6,     2,     4,     6,     4,     6,
       3,     5,     3,     3,     5,     2,     3,     3,     2,     3,
       2,     2,     1,     3,     3,     2,     2,     1,     1,     1,
       1,     1,     3,     1,     3,     3,     1,     3,     2,     1,
       2,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       3,     1,     3,     1,     1,     3,     1,     3,     1,     1,
       1,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       4,     3,     1,     1,     2,     4,     3,     2,     1,     3,
       1,     3,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
#line 122 "parser.y"
                                                                                                                                { fullTree = (yyvsp[0].treeNode); }
#line 1771 "parser.tab.c"
    break;

  case 3:
#line 125 "parser.y"
                                                                                                                        { (yyval.treeNode) = addSibling((yyvsp[-1].treeNode), (yyvsp[0].treeNode)); }
#line 1777 "parser.tab.c"
    break;

  case 4:
#line 126 "parser.y"
                                                                                                                                        { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1783 "parser.tab.c"
    break;

  case 5:
#line 129 "parser.y"
                                                                                                                                { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1789 "parser.tab.c"
    break;

  case 6:
#line 130 "parser.y"
                                                                                                                                        { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1795 "parser.tab.c"
    break;

  case 7:
#line 131 "parser.y"
                                                                                                                                        { (yyval.treeNode) = NULL; }
#line 1801 "parser.tab.c"
    break;

  case 8:
#line 134 "parser.y"
                                                                                                        { (yyval.treeNode) = (yyvsp[-1].treeNode);
																		  if ((yyval.treeNode) != NULL)
																		  {
																			(yyval.treeNode)->expType = setType((yyvsp[-2].tokenData));
																			setSibling((yyval.treeNode));
																		  }
																		  yyerrok; }
#line 1813 "parser.tab.c"
    break;

  case 9:
#line 141 "parser.y"
                                                                                                                { (yyval.treeNode) = NULL;
																		  yyerrok; }
#line 1820 "parser.tab.c"
    break;

  case 10:
#line 143 "parser.y"
                                                                                                                        { (yyval.treeNode) = NULL; yyerrok; yyerrok; }
#line 1826 "parser.tab.c"
    break;

  case 11:
#line 146 "parser.y"
                                                                                        { (yyval.treeNode) = (yyvsp[-1].treeNode);
																		  if ((yyval.treeNode) != NULL)
																		  {
																			(yyval.treeNode)->expType = setType((yyvsp[-2].tokenData));
																			(yyval.treeNode)->isStatic = true;
																			(yyval.treeNode)->memory = LocalStatic;
																			setSibling((yyval.treeNode));
																		  }
																		  yyerrok; }
#line 1840 "parser.tab.c"
    break;

  case 12:
#line 155 "parser.y"
                                                                                                                { (yyval.treeNode) = (yyvsp[-1].treeNode);
																		 if ((yyval.treeNode) != NULL)
																		  {
																			(yyval.treeNode)->expType = setType((yyvsp[-2].tokenData));
																			setSibling((yyval.treeNode));
																		  }
																		  yyerrok; }
#line 1852 "parser.tab.c"
    break;

  case 13:
#line 162 "parser.y"
                                                                                                                        { (yyval.treeNode) = NULL; yyerrok; yyerrok; }
#line 1858 "parser.tab.c"
    break;

  case 14:
#line 165 "parser.y"
                                                                                                        { if ((yyvsp[-2].treeNode) != NULL && (yyvsp[0].treeNode) != NULL)
																		  {
																		    (yyval.treeNode) = addSibling((yyvsp[-2].treeNode), (yyvsp[0].treeNode));
																		  }
																		  yyerrok; }
#line 1868 "parser.tab.c"
    break;

  case 15:
#line 170 "parser.y"
                                                                                                                                { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1874 "parser.tab.c"
    break;

  case 16:
#line 171 "parser.y"
                                                                                                                        { (yyval.treeNode) = NULL; }
#line 1880 "parser.tab.c"
    break;

  case 17:
#line 172 "parser.y"
                                                                                                                                        { (yyval.treeNode) = NULL; }
#line 1886 "parser.tab.c"
    break;

  case 18:
#line 175 "parser.y"
                                                                                                                                { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 1892 "parser.tab.c"
    break;

  case 19:
#line 176 "parser.y"
                                                                                                                        { (yyval.treeNode) = (yyvsp[-2].treeNode);
																		  if ((yyval.treeNode) != NULL && (yyvsp[0].treeNode) != NULL)
																		  {
																			(yyval.treeNode)->child[0] = (yyvsp[0].treeNode);
																		  }
																		}
#line 1903 "parser.tab.c"
    break;

  case 20:
#line 182 "parser.y"
                                                                                                                        { (yyval.treeNode) = NULL; }
#line 1909 "parser.tab.c"
    break;

  case 21:
#line 183 "parser.y"
                                                                                                                        { (yyval.treeNode) = NULL; yyerrok; }
#line 1915 "parser.tab.c"
    break;

  case 22:
#line 186 "parser.y"
                                                                                                                                { (yyval.treeNode) = (yyvsp[0].treeNode);
																		  (yyval.treeNode)->nodekind = DeclK;
																		  (yyval.treeNode)->subkind.decl = VarK;
																		  (yyval.treeNode)->size = 1; }
#line 1924 "parser.tab.c"
    break;

  case 23:
#line 190 "parser.y"
                                                                                                                { (yyval.treeNode) = (yyvsp[-3].treeNode);
																		  (yyval.treeNode)->nodekind = DeclK;
																		  (yyval.treeNode)->subkind.decl = VarK;
																		  (yyval.treeNode)->isArray = true;
																		  (yyval.treeNode)->size = (yyvsp[-1].tokenData)->nvalue + 1; }
#line 1934 "parser.tab.c"
    break;

  case 24:
#line 195 "parser.y"
                                                                                                                                { (yyval.treeNode) = NULL; }
#line 1940 "parser.tab.c"
    break;

  case 25:
#line 196 "parser.y"
                                                                                                                                { (yyval.treeNode) = NULL; yyerrok; }
#line 1946 "parser.tab.c"
    break;

  case 26:
#line 199 "parser.y"
                                                                                                                                        { (yyval.treeNode) = newExpNode(IdK, (yyvsp[0].tokenData));
																		  (yyval.treeNode)->attr.name = (yyvsp[0].tokenData)->id; }
#line 1953 "parser.tab.c"
    break;

  case 27:
#line 203 "parser.y"
                                                                                                                                { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 1959 "parser.tab.c"
    break;

  case 28:
#line 204 "parser.y"
                                                                                                                                        { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 1965 "parser.tab.c"
    break;

  case 29:
#line 205 "parser.y"
                                                                                                                                        { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 1971 "parser.tab.c"
    break;

  case 30:
#line 208 "parser.y"
                                                                                        { (yyval.treeNode) = (yyvsp[-4].treeNode);
																		  (yyval.treeNode)->nodekind = DeclK;
																		  (yyval.treeNode)->subkind.decl = FuncK;
																		  (yyval.treeNode)->expType = setType((yyvsp[-5].tokenData));
																		  (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
																		  (yyval.treeNode)->child[1] = (yyvsp[0].treeNode); }
#line 1982 "parser.tab.c"
    break;

  case 31:
#line 214 "parser.y"
                                                                                                        { (yyval.treeNode) = (yyvsp[-4].treeNode);
																		  (yyval.treeNode)->nodekind = DeclK;
																		  (yyval.treeNode)->subkind.decl = FuncK;
																		  (yyval.treeNode)->expType = Void;
																		  (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
																		  (yyval.treeNode)->child[1] = (yyvsp[0].treeNode); }
#line 1993 "parser.tab.c"
    break;

  case 32:
#line 220 "parser.y"
                                                                                                        { (yyval.treeNode) = (yyvsp[-3].treeNode);
																		  (yyval.treeNode)->nodekind = DeclK;
																		  (yyval.treeNode)->subkind.decl = FuncK;
																		  (yyval.treeNode)->expType = setType((yyvsp[-4].tokenData));
																		  (yyval.treeNode)->child[1] = (yyvsp[0].treeNode); }
#line 2003 "parser.tab.c"
    break;

  case 33:
#line 225 "parser.y"
                                                                                                                { (yyval.treeNode) = (yyvsp[-3].treeNode);
																		  (yyval.treeNode)->nodekind = DeclK;
																		  (yyval.treeNode)->subkind.decl = FuncK;
																		  (yyval.treeNode)->expType = Void;
																		  (yyval.treeNode)->child[1] = (yyvsp[0].treeNode); }
#line 2013 "parser.tab.c"
    break;

  case 34:
#line 230 "parser.y"
                                                                                                                                { (yyval.treeNode) = NULL; }
#line 2019 "parser.tab.c"
    break;

  case 35:
#line 231 "parser.y"
                                                                                                                        { (yyval.treeNode) = NULL; }
#line 2025 "parser.tab.c"
    break;

  case 36:
#line 232 "parser.y"
                                                                                                                                { (yyval.treeNode) = NULL; }
#line 2031 "parser.tab.c"
    break;

  case 37:
#line 233 "parser.y"
                                                                                                                { (yyval.treeNode) = NULL; }
#line 2037 "parser.tab.c"
    break;

  case 38:
#line 236 "parser.y"
                                                                                                                                { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2043 "parser.tab.c"
    break;

  case 39:
#line 239 "parser.y"
                                                                                                        { (yyval.treeNode) = addSibling((yyvsp[-2].treeNode), (yyvsp[0].treeNode)); }
#line 2049 "parser.tab.c"
    break;

  case 40:
#line 240 "parser.y"
                                                                                                                                { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2055 "parser.tab.c"
    break;

  case 41:
#line 241 "parser.y"
                                                                                                                        { (yyval.treeNode) = NULL; }
#line 2061 "parser.tab.c"
    break;

  case 42:
#line 242 "parser.y"
                                                                                                                                        { (yyval.treeNode) = NULL; }
#line 2067 "parser.tab.c"
    break;

  case 43:
#line 245 "parser.y"
                                                                                                        { (yyval.treeNode) = (yyvsp[0].treeNode);
																		  if ((yyval.treeNode) != NULL)
																		  {
																			(yyval.treeNode)->expType = setType((yyvsp[-1].tokenData));
																			setSibling((yyval.treeNode));
																		  }
																		}
#line 2079 "parser.tab.c"
    break;

  case 44:
#line 252 "parser.y"
                                                                                                                                { (yyval.treeNode) = NULL; }
#line 2085 "parser.tab.c"
    break;

  case 45:
#line 255 "parser.y"
                                                                                                                { (yyval.treeNode) = addSibling((yyvsp[-2].treeNode), (yyvsp[0].treeNode)); yyerrok; }
#line 2091 "parser.tab.c"
    break;

  case 46:
#line 256 "parser.y"
                                                                                                                                        { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2097 "parser.tab.c"
    break;

  case 47:
#line 257 "parser.y"
                                                                                                                        { (yyval.treeNode) = NULL; }
#line 2103 "parser.tab.c"
    break;

  case 48:
#line 258 "parser.y"
                                                                                                                                        { (yyval.treeNode) = NULL; }
#line 2109 "parser.tab.c"
    break;

  case 49:
#line 261 "parser.y"
                                                                                                                                { (yyval.treeNode) = (yyvsp[0].treeNode);
																		  (yyval.treeNode)->nodekind = DeclK;
																		  (yyval.treeNode)->subkind.decl = ParamK; }
#line 2117 "parser.tab.c"
    break;

  case 50:
#line 264 "parser.y"
                                                                                                                        { (yyval.treeNode) = (yyvsp[-2].treeNode);
																		  (yyval.treeNode)->nodekind = DeclK;
																		  (yyval.treeNode)->subkind.decl = ParamK;
																		  (yyval.treeNode)->isArray = true; }
#line 2126 "parser.tab.c"
    break;

  case 51:
#line 270 "parser.y"
                                                                                                                        { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2132 "parser.tab.c"
    break;

  case 52:
#line 271 "parser.y"
                                                                                                                                        { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2138 "parser.tab.c"
    break;

  case 53:
#line 274 "parser.y"
                                                                                                                                { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2144 "parser.tab.c"
    break;

  case 54:
#line 275 "parser.y"
                                                                                                                                { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2150 "parser.tab.c"
    break;

  case 55:
#line 276 "parser.y"
                                                                                                                                { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2156 "parser.tab.c"
    break;

  case 56:
#line 277 "parser.y"
                                                                                                                                { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2162 "parser.tab.c"
    break;

  case 57:
#line 278 "parser.y"
                                                                                                                                { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2168 "parser.tab.c"
    break;

  case 58:
#line 279 "parser.y"
                                                                                                                                        { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2174 "parser.tab.c"
    break;

  case 59:
#line 282 "parser.y"
                                                                                                                        { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2180 "parser.tab.c"
    break;

  case 60:
#line 283 "parser.y"
                                                                                                                                { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2186 "parser.tab.c"
    break;

  case 61:
#line 286 "parser.y"
                                                                                                                        { (yyval.treeNode) = (yyvsp[-1].treeNode); }
#line 2192 "parser.tab.c"
    break;

  case 62:
#line 287 "parser.y"
                                                                                                                                        { (yyval.treeNode) = newStmtNode(NullK, (yyvsp[0].tokenData)); }
#line 2198 "parser.tab.c"
    break;

  case 63:
#line 288 "parser.y"
                                                                                                                                { (yyval.treeNode) = NULL; yyerrok; }
#line 2204 "parser.tab.c"
    break;

  case 64:
#line 291 "parser.y"
                                                                                                { (yyval.treeNode) = newStmtNode(CompoundK, (yyvsp[-3].tokenData));
																		  (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
																		  (yyval.treeNode)->child[1] = (yyvsp[-1].treeNode);
																		  yyerrok; }
#line 2213 "parser.tab.c"
    break;

  case 65:
#line 295 "parser.y"
                                                                                                                        { (yyval.treeNode) = newStmtNode(CompoundK, (yyvsp[-2].tokenData));
																		  (yyval.treeNode)->child[1] = (yyvsp[-1].treeNode);
																		  yyerrok;}
#line 2221 "parser.tab.c"
    break;

  case 66:
#line 298 "parser.y"
                                                                                                                        { (yyval.treeNode) = newStmtNode(CompoundK, (yyvsp[-2].tokenData));
																		  (yyval.treeNode)->child[0] = (yyvsp[-1].treeNode);
																		  yyerrok;}
#line 2229 "parser.tab.c"
    break;

  case 67:
#line 301 "parser.y"
                                                                                                                                { (yyval.treeNode) = newStmtNode(CompoundK, (yyvsp[-1].tokenData));
																		  yyerrok; }
#line 2236 "parser.tab.c"
    break;

  case 68:
#line 305 "parser.y"
                                                                                                                { (yyval.treeNode) = addSibling((yyvsp[-1].treeNode), (yyvsp[0].treeNode)); }
#line 2242 "parser.tab.c"
    break;

  case 69:
#line 306 "parser.y"
                                                                                                                                { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2248 "parser.tab.c"
    break;

  case 70:
#line 309 "parser.y"
                                                                                                                        { (yyval.treeNode) = addSibling((yyvsp[-1].treeNode), (yyvsp[0].treeNode)); }
#line 2254 "parser.tab.c"
    break;

  case 71:
#line 310 "parser.y"
                                                                                                                                        { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2260 "parser.tab.c"
    break;

  case 72:
#line 313 "parser.y"
                                                                                { (yyval.treeNode) = newStmtNode(IfK, (yyvsp[-5].tokenData));
																		  (yyval.treeNode)->child[0] = (yyvsp[-4].treeNode);
																		  (yyval.treeNode)->child[1] = (yyvsp[-2].treeNode);
																		  (yyval.treeNode)->child[2] = (yyvsp[0].treeNode); }
#line 2269 "parser.tab.c"
    break;

  case 73:
#line 317 "parser.y"
                                                                                                                                        { (yyval.treeNode) = NULL; }
#line 2275 "parser.tab.c"
    break;

  case 74:
#line 318 "parser.y"
                                                                                                                        { (yyval.treeNode) = NULL; yyerrok; }
#line 2281 "parser.tab.c"
    break;

  case 75:
#line 319 "parser.y"
                                                                                                { (yyval.treeNode) = NULL; yyerrok; }
#line 2287 "parser.tab.c"
    break;

  case 76:
#line 322 "parser.y"
                                                                                                        { (yyval.treeNode) = newStmtNode(IfK, (yyvsp[-3].tokenData));
																		  (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
																		  (yyval.treeNode)->child[1] = (yyvsp[0].treeNode); }
#line 2295 "parser.tab.c"
    break;

  case 77:
#line 325 "parser.y"
                                                                                                { (yyval.treeNode) = newStmtNode(IfK, (yyvsp[-5].tokenData));
																		  (yyval.treeNode)->child[0] = (yyvsp[-4].treeNode); 
																		  (yyval.treeNode)->child[1] = (yyvsp[-2].treeNode);
																		  (yyval.treeNode)->child[2] = (yyvsp[0].treeNode); }
#line 2304 "parser.tab.c"
    break;

  case 78:
#line 329 "parser.y"
                                                                                                                        { (yyval.treeNode) = NULL; yyerrok; }
#line 2310 "parser.tab.c"
    break;

  case 79:
#line 330 "parser.y"
                                                                                                        { (yyval.treeNode) = NULL; yyerrok; }
#line 2316 "parser.tab.c"
    break;

  case 80:
#line 333 "parser.y"
                                                                                                { (yyval.treeNode) = newStmtNode(WhileK, (yyvsp[-3].tokenData));
																		  (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
																		  (yyval.treeNode)->child[1] = (yyvsp[0].treeNode); }
#line 2324 "parser.tab.c"
    break;

  case 81:
#line 336 "parser.y"
                                                                                                        { (yyval.treeNode) = newStmtNode(ForK, (yyvsp[-5].tokenData));
																		  (yyval.treeNode)->child[0] = (yyvsp[-4].treeNode);
																		  (yyval.treeNode)->child[0]->nodekind = DeclK;
																		  (yyval.treeNode)->child[0]->subkind.decl = VarK;
																		  (yyval.treeNode)->child[0]->expType = Integer;
																		  (yyval.treeNode)->child[0]->memory = Local;
																		  (yyval.treeNode)->child[0]->size = 1;
																		  (yyval.treeNode)->child[0]->isInitialized = true;
																		  (yyval.treeNode)->child[1] = (yyvsp[-2].treeNode);
																		  (yyval.treeNode)->child[2] = (yyvsp[0].treeNode); }
#line 2339 "parser.tab.c"
    break;

  case 82:
#line 346 "parser.y"
                                                                                                                { (yyval.treeNode) = NULL; yyerrok; }
#line 2345 "parser.tab.c"
    break;

  case 83:
#line 347 "parser.y"
                                                                                                                                { (yyval.treeNode) = NULL; }
#line 2351 "parser.tab.c"
    break;

  case 84:
#line 348 "parser.y"
                                                                                                                { (yyval.treeNode) = NULL; yyerrok; }
#line 2357 "parser.tab.c"
    break;

  case 85:
#line 349 "parser.y"
                                                                                                                                        { (yyval.treeNode) = NULL; }
#line 2363 "parser.tab.c"
    break;

  case 86:
#line 352 "parser.y"
                                                                                                { (yyval.treeNode) = newStmtNode(WhileK, (yyvsp[-3].tokenData));
																		  (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
																		  (yyval.treeNode)->child[1] = (yyvsp[0].treeNode); }
#line 2371 "parser.tab.c"
    break;

  case 87:
#line 355 "parser.y"
                                                                                                                { (yyval.treeNode) = newStmtNode(ForK, (yyvsp[-5].tokenData));
																		  (yyval.treeNode)->child[0] = (yyvsp[-4].treeNode);
																		  (yyval.treeNode)->child[0]->nodekind = DeclK;
																		  (yyval.treeNode)->child[0]->subkind.decl = VarK;
																		  (yyval.treeNode)->child[0]->expType = Integer;
																		  (yyval.treeNode)->child[0]->memory = Local;
																		  (yyval.treeNode)->child[0]->size = 1;
																		  (yyval.treeNode)->child[0]->isInitialized = true;
																		  (yyval.treeNode)->child[1] = (yyvsp[-2].treeNode);
																		  (yyval.treeNode)->child[2] = (yyvsp[0].treeNode);}
#line 2386 "parser.tab.c"
    break;

  case 88:
#line 365 "parser.y"
                                                                                                                        { (yyval.treeNode) = NULL; yyerrok; }
#line 2392 "parser.tab.c"
    break;

  case 89:
#line 366 "parser.y"
                                                                                                                { (yyval.treeNode) = NULL; yyerrok; }
#line 2398 "parser.tab.c"
    break;

  case 90:
#line 369 "parser.y"
                                                                                                                { (yyval.treeNode) = newStmtNode(RangeK, (yyvsp[-1].tokenData));
																		  (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
																		  (yyval.treeNode)->child[1] = (yyvsp[0].treeNode); }
#line 2406 "parser.tab.c"
    break;

  case 91:
#line 372 "parser.y"
                                                                                                        { (yyval.treeNode) = newStmtNode(RangeK, (yyvsp[-3].tokenData));
																		  (yyval.treeNode)->child[0] = (yyvsp[-4].treeNode);
																		  (yyval.treeNode)->child[1] = (yyvsp[-2].treeNode);
																		  (yyval.treeNode)->child[2] = (yyvsp[0].treeNode); }
#line 2415 "parser.tab.c"
    break;

  case 92:
#line 376 "parser.y"
                                                                                                                        { (yyval.treeNode) = NULL; }
#line 2421 "parser.tab.c"
    break;

  case 93:
#line 377 "parser.y"
                                                                                                                                { (yyval.treeNode) = NULL; yyerrok; }
#line 2427 "parser.tab.c"
    break;

  case 94:
#line 378 "parser.y"
                                                                                                                { (yyval.treeNode) = NULL; }
#line 2433 "parser.tab.c"
    break;

  case 95:
#line 381 "parser.y"
                                                                                                                        { (yyval.treeNode) = newStmtNode(ReturnK, (yyvsp[-1].tokenData)); }
#line 2439 "parser.tab.c"
    break;

  case 96:
#line 382 "parser.y"
                                                                                                                        { (yyval.treeNode) = newStmtNode(ReturnK, (yyvsp[-2].tokenData));
																		  (yyval.treeNode)->child[0] = (yyvsp[-1].treeNode); yyerrok; }
#line 2446 "parser.tab.c"
    break;

  case 97:
#line 384 "parser.y"
                                                                                                                        { (yyval.treeNode) = NULL; yyerrok; }
#line 2452 "parser.tab.c"
    break;

  case 98:
#line 387 "parser.y"
                                                                                                                        { (yyval.treeNode) = newStmtNode(BreakK, (yyvsp[-1].tokenData)); }
#line 2458 "parser.tab.c"
    break;

  case 99:
#line 390 "parser.y"
                                                                                                                        { (yyval.treeNode) = newExpNode(AssignK, (yyvsp[-1].tokenData));
																		  (yyval.treeNode)->attr.op = (yyvsp[-1].tokenData)->tokenclass;
																		  (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
																		  (yyval.treeNode)->child[1] = (yyvsp[0].treeNode); }
#line 2467 "parser.tab.c"
    break;

  case 100:
#line 394 "parser.y"
                                                                                                                                { (yyval.treeNode) = newExpNode(AssignK, (yyvsp[0].tokenData));
																		  (yyval.treeNode)->attr.op = (yyvsp[0].tokenData)->tokenclass;
																		  (yyval.treeNode)->child[0] = (yyvsp[-1].treeNode); }
#line 2475 "parser.tab.c"
    break;

  case 101:
#line 397 "parser.y"
                                                                                                                                { (yyval.treeNode) = newExpNode(AssignK, (yyvsp[0].tokenData));
																		  (yyval.treeNode)->attr.op = (yyvsp[0].tokenData)->tokenclass;
																		  (yyval.treeNode)->child[0] = (yyvsp[-1].treeNode); }
#line 2483 "parser.tab.c"
    break;

  case 102:
#line 400 "parser.y"
                                                                                                                                        { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2489 "parser.tab.c"
    break;

  case 103:
#line 401 "parser.y"
                                                                                                                        { (yyval.treeNode) = NULL; yyerrok; }
#line 2495 "parser.tab.c"
    break;

  case 104:
#line 402 "parser.y"
                                                                                                                        { (yyval.treeNode) = NULL; }
#line 2501 "parser.tab.c"
    break;

  case 105:
#line 403 "parser.y"
                                                                                                                                        { (yyval.treeNode) = NULL; yyerrok; }
#line 2507 "parser.tab.c"
    break;

  case 106:
#line 404 "parser.y"
                                                                                                                                        { (yyval.treeNode) = NULL; yyerrok; }
#line 2513 "parser.tab.c"
    break;

  case 107:
#line 407 "parser.y"
                                                                                                                                { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2519 "parser.tab.c"
    break;

  case 108:
#line 408 "parser.y"
                                                                                                                                        { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2525 "parser.tab.c"
    break;

  case 109:
#line 409 "parser.y"
                                                                                                                                        { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2531 "parser.tab.c"
    break;

  case 110:
#line 410 "parser.y"
                                                                                                                                        { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2537 "parser.tab.c"
    break;

  case 111:
#line 411 "parser.y"
                                                                                                                                        { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2543 "parser.tab.c"
    break;

  case 112:
#line 414 "parser.y"
                                                                                                                { (yyval.treeNode) = newExpNode(OpK, (yyvsp[-1].tokenData));
																		  (yyval.treeNode)->attr.op = (yyvsp[-1].tokenData)->tokenclass;
																		  (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
																		  (yyval.treeNode)->child[1] = (yyvsp[0].treeNode); }
#line 2552 "parser.tab.c"
    break;

  case 113:
#line 418 "parser.y"
                                                                                                                                        { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2558 "parser.tab.c"
    break;

  case 114:
#line 419 "parser.y"
                                                                                                                        { (yyval.treeNode) = NULL; }
#line 2564 "parser.tab.c"
    break;

  case 115:
#line 422 "parser.y"
                                                                                                                { (yyval.treeNode) = newExpNode(OpK, (yyvsp[-1].tokenData));
																		  (yyval.treeNode)->attr.op = (yyvsp[-1].tokenData)->tokenclass;
																		  (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
																		  (yyval.treeNode)->child[1] = (yyvsp[0].treeNode); }
#line 2573 "parser.tab.c"
    break;

  case 116:
#line 426 "parser.y"
                                                                                                                                { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2579 "parser.tab.c"
    break;

  case 117:
#line 427 "parser.y"
                                                                                                                                { (yyval.treeNode) = NULL; }
#line 2585 "parser.tab.c"
    break;

  case 118:
#line 430 "parser.y"
                                                                                                                        { (yyval.treeNode) = newExpNode(OpK, (yyvsp[-1].tokenData));
																		  (yyval.treeNode)->attr.op = (yyvsp[-1].tokenData)->tokenclass;
																		  (yyval.treeNode)->child[0] = (yyvsp[0].treeNode); }
#line 2593 "parser.tab.c"
    break;

  case 119:
#line 433 "parser.y"
                                                                                                                                        { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2599 "parser.tab.c"
    break;

  case 120:
#line 434 "parser.y"
                                                                                                                                        { (yyval.treeNode) = NULL; }
#line 2605 "parser.tab.c"
    break;

  case 121:
#line 437 "parser.y"
                                                                                                                { (yyval.treeNode) = newExpNode(OpK, (yyvsp[-1].tokenData));
																		  (yyval.treeNode)->attr.op = (yyvsp[-1].tokenData)->tokenclass;
																		  (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
																		  (yyval.treeNode)->child[1] = (yyvsp[0].treeNode); }
#line 2614 "parser.tab.c"
    break;

  case 122:
#line 441 "parser.y"
                                                                                                                                        { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2620 "parser.tab.c"
    break;

  case 123:
#line 442 "parser.y"
                                                                                                                        { (yyval.treeNode) = NULL; }
#line 2626 "parser.tab.c"
    break;

  case 124:
#line 445 "parser.y"
                                                                                                                                { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2632 "parser.tab.c"
    break;

  case 125:
#line 446 "parser.y"
                                                                                                                                        { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2638 "parser.tab.c"
    break;

  case 126:
#line 447 "parser.y"
                                                                                                                                        { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2644 "parser.tab.c"
    break;

  case 127:
#line 448 "parser.y"
                                                                                                                                        { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2650 "parser.tab.c"
    break;

  case 128:
#line 449 "parser.y"
                                                                                                                                        { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2656 "parser.tab.c"
    break;

  case 129:
#line 450 "parser.y"
                                                                                                                                        { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2662 "parser.tab.c"
    break;

  case 130:
#line 453 "parser.y"
                                                                                                                { (yyval.treeNode) = newExpNode(OpK, (yyvsp[-1].tokenData));
																		  (yyval.treeNode)->attr.op = (yyvsp[-1].tokenData)->tokenclass;
																		  (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode);
																		  (yyval.treeNode)->child[1] = (yyvsp[0].treeNode); }
#line 2671 "parser.tab.c"
    break;

  case 131:
#line 457 "parser.y"
                                                                                                                                        { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2677 "parser.tab.c"
    break;

  case 132:
#line 458 "parser.y"
                                                                                                                        { (yyval.treeNode) = NULL; }
#line 2683 "parser.tab.c"
    break;

  case 133:
#line 461 "parser.y"
                                                                                                                                { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2689 "parser.tab.c"
    break;

  case 134:
#line 462 "parser.y"
                                                                                                                                        { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2695 "parser.tab.c"
    break;

  case 135:
#line 465 "parser.y"
                                                                                                                { (yyval.treeNode) = newExpNode(OpK, (yyvsp[-1].tokenData));
																		  (yyval.treeNode)->attr.op = (yyvsp[-1].tokenData)->tokenclass;
																		  (yyval.treeNode)->child[0] = (yyvsp[-2].treeNode); 
																		  (yyval.treeNode)->child[1] = (yyvsp[0].treeNode); }
#line 2704 "parser.tab.c"
    break;

  case 136:
#line 469 "parser.y"
                                                                                                                                        { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2710 "parser.tab.c"
    break;

  case 137:
#line 470 "parser.y"
                                                                                                                        { (yyval.treeNode) = NULL; }
#line 2716 "parser.tab.c"
    break;

  case 138:
#line 473 "parser.y"
                                                                                                                                { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2722 "parser.tab.c"
    break;

  case 139:
#line 474 "parser.y"
                                                                                                                                        { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2728 "parser.tab.c"
    break;

  case 140:
#line 475 "parser.y"
                                                                                                                                        { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2734 "parser.tab.c"
    break;

  case 141:
#line 478 "parser.y"
                                                                                                                        { (yyval.treeNode) = newExpNode(OpK, (yyvsp[-1].tokenData));
																		  if ((yyvsp[-1].tokenData)->tokenclass == SUB)
																			(yyval.treeNode)->attr.op = CHSIGN;
																		  else if ((yyvsp[-1].tokenData)->tokenclass == MUL)
																			(yyval.treeNode)->attr.op = SIZEOF;
																		  else
					  														(yyval.treeNode)->attr.op = (yyvsp[-1].tokenData)->tokenclass;
																		  (yyval.treeNode)->child[0] = (yyvsp[0].treeNode); }
#line 2747 "parser.tab.c"
    break;

  case 142:
#line 486 "parser.y"
                                                                                                                                        { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2753 "parser.tab.c"
    break;

  case 143:
#line 487 "parser.y"
                                                                                                                                { (yyval.treeNode) = NULL; }
#line 2759 "parser.tab.c"
    break;

  case 144:
#line 490 "parser.y"
                                                                                                                                { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2765 "parser.tab.c"
    break;

  case 145:
#line 491 "parser.y"
                                                                                                                                        { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2771 "parser.tab.c"
    break;

  case 146:
#line 492 "parser.y"
                                                                                                                                        { (yyval.tokenData) = (yyvsp[0].tokenData); }
#line 2777 "parser.tab.c"
    break;

  case 147:
#line 495 "parser.y"
                                                                                                                                { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2783 "parser.tab.c"
    break;

  case 148:
#line 496 "parser.y"
                                                                                                                                        { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2789 "parser.tab.c"
    break;

  case 149:
#line 499 "parser.y"
                                                                                                                                { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2795 "parser.tab.c"
    break;

  case 150:
#line 500 "parser.y"
                                                                                                                        { (yyval.treeNode) = newExpNode(OpK, (yyvsp[-2].tokenData));
																		  (yyval.treeNode)->attr.op = (yyvsp[-2].tokenData)->tokenclass;
																		  (yyval.treeNode)->child[0] = (yyvsp[-3].treeNode);
																		  (yyval.treeNode)->child[1] = (yyvsp[-1].treeNode);
																		  (yyval.treeNode)->child[0]->isArray = true; }
#line 2805 "parser.tab.c"
    break;

  case 151:
#line 507 "parser.y"
                                                                                                                        { (yyval.treeNode) = (yyvsp[-1].treeNode);
																		  yyerrok; }
#line 2812 "parser.tab.c"
    break;

  case 152:
#line 509 "parser.y"
                                                                                                                                        { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2818 "parser.tab.c"
    break;

  case 153:
#line 510 "parser.y"
                                                                                                                                        { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2824 "parser.tab.c"
    break;

  case 154:
#line 511 "parser.y"
                                                                                                                                { (yyval.treeNode) = NULL; }
#line 2830 "parser.tab.c"
    break;

  case 155:
#line 514 "parser.y"
                                                                                                                { (yyval.treeNode) = (yyvsp[-3].treeNode);
																		  (yyval.treeNode)->nodekind = ExpK;
																		  (yyval.treeNode)->subkind.exp = CallK;
																		  (yyval.treeNode)->child[0] = (yyvsp[-1].treeNode); }
#line 2839 "parser.tab.c"
    break;

  case 156:
#line 518 "parser.y"
                                                                                                                                { (yyval.treeNode) = (yyvsp[-2].treeNode);
																		  (yyval.treeNode)->nodekind = ExpK;
																		  (yyval.treeNode)->subkind.exp = CallK; }
#line 2847 "parser.tab.c"
    break;

  case 157:
#line 521 "parser.y"
                                                                                                                                { (yyval.treeNode) = NULL; yyerrok; }
#line 2853 "parser.tab.c"
    break;

  case 158:
#line 524 "parser.y"
                                                                                                                                { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2859 "parser.tab.c"
    break;

  case 159:
#line 527 "parser.y"
                                                                                                                        { (yyval.treeNode) = addSibling((yyvsp[-2].treeNode), (yyvsp[0].treeNode));
																		  yyerrok; }
#line 2866 "parser.tab.c"
    break;

  case 160:
#line 529 "parser.y"
                                                                                                                                        { (yyval.treeNode) = (yyvsp[0].treeNode); }
#line 2872 "parser.tab.c"
    break;

  case 161:
#line 530 "parser.y"
                                                                                                                                { (yyval.treeNode) = NULL; }
#line 2878 "parser.tab.c"
    break;

  case 162:
#line 533 "parser.y"
                                                                                                                                { (yyval.treeNode) = newExpNode(ConstantK, (yyvsp[0].tokenData));
																		  (yyval.treeNode)->attr.value = (yyvsp[0].tokenData)->nvalue;
																		  (yyval.treeNode)->expType = Integer;}
#line 2886 "parser.tab.c"
    break;

  case 163:
#line 536 "parser.y"
                                                                                                                                        { (yyval.treeNode) = newExpNode(ConstantK, (yyvsp[0].tokenData));
																		  (yyval.treeNode)->attr.cvalue = (yyvsp[0].tokenData)->cvalue;
																		  (yyval.treeNode)->expType = Char; }
#line 2894 "parser.tab.c"
    break;

  case 164:
#line 539 "parser.y"
                                                                                                                                { (yyval.treeNode) = newExpNode(ConstantK, (yyvsp[0].tokenData));
																	      (yyval.treeNode)->attr.string = (yyvsp[0].tokenData)->svalue;
																		  (yyval.treeNode)->expType = Char;
																		  (yyval.treeNode)->isArray = true;
																		  (yyval.treeNode)->size = strlen((yyvsp[0].tokenData)->svalue) + 1; }
#line 2904 "parser.tab.c"
    break;

  case 165:
#line 544 "parser.y"
                                                                                                                                        { (yyval.treeNode) = newExpNode(ConstantK, (yyvsp[0].tokenData));
																		  (yyval.treeNode)->attr.value = (yyvsp[0].tokenData)->nvalue;
																		  (yyval.treeNode)->expType = Boolean; }
#line 2912 "parser.tab.c"
    break;


#line 2916 "parser.tab.c"

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
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
                  yystos[+*yyssp], yyvsp);
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
#line 549 "parser.y"

extern int yydebug;
int main(int argc, char *argv[])
{
	int c, optind;
	int pflg = 0, dflg = 0, Dflg = 0, Pflg = 0, hflg = 0, Mflg = 0;

	while (1)
	{
		// hunt for a string of options
        	while ((c = ourGetopt(argc, argv, (char *)"dDpPhM")) != EOF)
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
				case 'M':
					Mflg = 1;
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

	initErrorProcessing();

	if (hflg == 1)
	{
		printf("usage -c [options] [sourcefile]\noptions:\n-d - turn on parser debugging\n-D - turn on symbol table debugging\n-h - print this usage message\n-p - print the abstract syntax tree\n-P - print the abstract syntax tree plus type information\n");
		exit(1);
	}
	else if (argc > 1 && !(yyin = fopen(argv[argc - 1], "r"))) 
	{
		// failed to open file
		//printf("ERROR: failed to open \'%s\'\n", argv[1]);
		fileError(argv[argc - 1]);
	}
	else if (yyin)
	{
		//printf("====================================\n");
		//char* fileName = removeDirectory(argv[argc - 1]);
		//printf("FILE: %s\n", fileName);
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

		IORuntime(symbolTable); //insert I/O Runtime support
		semanticAnalysis(fullTree, symbolTable, -1); //perform semantic analysis (may find errors here)
		TreeNode *main = (TreeNode *)symbolTable->lookupGlobal("main");

		if (main != NULL && main->nodekind == DeclK && main->subkind.decl == FuncK)
		{
			if (main->child[0] != NULL)
			{
				mainError(strdup("A function named 'main' with no parameters must be defined."));
			}
		}
		else
		{
			mainError(strdup("A function named 'main' with no parameters must be defined."));
		}

		if (numErrors == 0)
		{
			if (Pflg == 1)
				printTree(fullTree, 0, true);
			if (Mflg == 1)
			{
				printMemTree(fullTree, 0, true);
				printf("Offset for end of global space: %d\n", goffset);
			}
		}
	}

	printf("Number of warnings: %d\n", numWarnings);        //WARNINGS
	printf("Number of errors: %d\n", numErrors);		// ERROR

	return 0;
}

char* removeDirectory(char* wholeName)
{
	char* fileName;
	int length = strlen(wholeName);
	int dirPos = -1;

	for (int i = 0; i < length; i++)
	{
		if (wholeName[i] == '/')
			dirPos = i + 1;
	}

	if (dirPos != -1)
	{
		int j = 0;
		fileName = new char[length - dirPos];
		for (int i = dirPos; i < length; i++)
		{
			fileName[j++] = wholeName[i];
		}
		fileName[j] = '\0';
	}
	else
	{
		return wholeName;
	}

	return fileName;
}

void IORuntime(SymbolTable* symbolTable)
{
	std::stringstream name;

	TreeNode* output = newDeclNode(FuncK, UndefinedType);
	output->attr.name = strdup("output");
	output->expType = Void;
		output->child[0] = newDeclNode(ParamK, UndefinedType);
		output->child[0]->expType = Integer;
	output->lineno = -1;
	name.str(output->attr.name);
	symbolTable->insertGlobal(name.str(), output);

	TreeNode* outputb = newDeclNode(FuncK, UndefinedType);
	outputb->attr.name = strdup("outputb");
	outputb->expType = Void;
		outputb->child[0] = newDeclNode(ParamK, UndefinedType);
		outputb->child[0]->expType = Boolean;
	outputb->lineno = -1;
	name.str(outputb->attr.name);
	symbolTable->insertGlobal(name.str(), outputb);

	TreeNode* outputc = newDeclNode(FuncK, UndefinedType);
	outputc->attr.name = strdup("outputc");
	outputc->expType = Void;
		outputc->child[0] = newDeclNode(ParamK, UndefinedType);
		outputc->child[0]->expType = Char;
	outputc->lineno = -1;
	name.str(outputc->attr.name);
	symbolTable->insertGlobal(name.str(), outputc);

	TreeNode* input = newDeclNode(FuncK, UndefinedType);
	input->attr.name = strdup("input");
	input->expType = Integer;
	input->lineno = -1;
	name.str(input->attr.name);
	symbolTable->insertGlobal(name.str(), input);

	TreeNode* inputb = newDeclNode(FuncK, UndefinedType);
	inputb->attr.name = strdup("inputb");
	inputb->expType = Boolean;
	inputb->lineno = -1;
	name.str(inputb->attr.name);
	symbolTable->insertGlobal(name.str(), inputb);

	TreeNode* inputc = newDeclNode(FuncK, UndefinedType);
	inputc->attr.name = strdup("inputc");
	inputc->expType = Char;
	inputc->lineno = -1;
	name.str(inputc->attr.name);
	symbolTable->insertGlobal(name.str(), inputc);

	TreeNode* outnl = newDeclNode(FuncK, UndefinedType);
	outnl->attr.name = strdup("outnl");
	outnl->expType = Void;
	outnl->lineno = -1;
	name.str(outnl->attr.name);
	symbolTable->insertGlobal(name.str(), outnl);
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

	t->ignore = false;
	t->ignoreWarn = false;
	t->isInitialized = false;
	t->isUsed = false;
	t->notScope = false;
	t->isStatic = false;
	t->isArray = false;
	t->isGlobal = false;

	t->expType = UndefinedType;

	t->memory = None;
	t->location = 0;
	t->size = 1;

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

	t->ignore = NULL;
	t->ignoreWarn = false;
	t->isInitialized = false;
	t->isUsed = false;
	t->notScope = false;
	t->isStatic = false;
	t->isArray = false;
	t->isGlobal = false;

	t->expType = UndefinedType;

	t->memory = None;
	t->location = 0;
	t->size = 1;

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
			if (token != NULL)
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

	t->ignore = NULL;
	t->ignoreWarn = false;
	t->isInitialized = false;
	t->isUsed = false;
	t->notScope = false;
	t->isStatic = false;
	t->isArray = false;
	t->isGlobal = false;

	t->expType = UndefinedType;

	t->memory = None;
	t->location = 0;
	t->size = 1;

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

char *returnToken(OpKind token)
{
	char* returnChar = strdup("Unkown op");

	switch (token)
	{
		case IF:
		case THEN:
		case ELSE:
		case WHILE:
		case TO:
		case BREAK:
		case FOR:
		case INC: returnChar = strdup("++"); break;
		case DEC: returnChar = strdup("--"); break;
		case ASGN: returnChar = strdup(":="); break;
		case LESSER: returnChar = strdup("<"); break;
		case GREATER: returnChar = strdup(">"); break;
		case EQ: returnChar = strdup("="); break;
		case GEQ: returnChar = strdup(">="); break;
		case LEQ: returnChar = strdup("<="); break;
		case NEQ: returnChar = strdup("><"); break;
		case LPAREN: returnChar = strdup("("); break;
		case RPAREN: returnChar = strdup(")"); break;
		case LBRACKET: returnChar = strdup("["); break;
		case RBRACKET: returnChar = strdup("]"); break;
		case LCURLY: returnChar = strdup("{"); break;
		case RCURLY: returnChar = strdup("}"); break;
		case SEMICOLON: returnChar = strdup(";"); break;
		case QUESTION: returnChar = strdup("?"); break;
		case ADD: returnChar = strdup("+"); break;
		case SUB: returnChar = strdup("-"); break;
		case MUL: returnChar = strdup("*"); break;
		case DIV: returnChar = strdup("/"); break;
		case MOD: returnChar = strdup("%"); break;
		case NOT: returnChar = strdup("not"); break;
		case AND: returnChar = strdup("and"); break;
		case OR: returnChar = strdup("or"); break;
		case ADDASS: returnChar = strdup("+="); break;
		case SUBASS: returnChar = strdup("-="); break;
		case MULASS: returnChar = strdup("*="); break;
		case DIVASS: returnChar = strdup("/="); break;
		case CHSIGN: returnChar = strdup("chsign"); break;
		case SIZEOF: returnChar = strdup("sizeof"); break;
		default: /* should never happen */
			fprintf(stdout, "Unknown token: %d", token);
	}

	return returnChar;
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

void printMemTree(TreeNode *tree, int childNum, bool types)
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

		char *memType;
		if (tree->memory == None)
			memType = strdup("None");
		else if (tree->memory == Local)
			memType = strdup("Local");
		else if (tree->memory == Global)
			memType = strdup("Global");
		else if (tree->memory == LocalStatic)
			memType = strdup("LocalStatic");
		else if (tree->memory == Parameter)
			memType = strdup("Parameter");

		char *arrayCheck;
		if (tree->isArray)
		{
			if (tree->isStatic)
				arrayCheck = strdup(" of static array");
			else
				arrayCheck = strdup(" of array");
		}
		else
		{
			if (tree->isStatic)
				arrayCheck = strdup(" of static");
			else
				arrayCheck = strdup("");
		}

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
					fprintf(stdout,"Op: %s", returnToken(tree->attr.op));
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
								fprintf(stdout,"\"%s\"", tree->attr.string);
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
                    fprintf(stdout,"Assign: %s", returnToken(tree->attr.op));
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
					fprintf(stdout,"Var: %s", tree->attr.name);
				break;
				case FuncK:
					fprintf(stdout,"Func: %s returns %stype %s", tree->attr.name, arrayCheck, expType);
				break;
				case ParamK:
					fprintf(stdout,"Parm: %s", tree->attr.name);
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

		fprintf(stdout, "%s", arrayCheck);

		if (types)
		{
			if (tree->nodekind != StmtK && !(tree->nodekind == DeclK && tree->subkind.decl == FuncK))
			{
				if (!(tree->isStatic && !tree->isArray))
					fprintf(stdout, " of");

				switch(tree->expType)
				{
					case Integer:
						fprintf(stdout, " type int");
					break;
					case Char:
						fprintf(stdout, " type char");
					break;
					case Boolean:
						fprintf(stdout, " type bool");
					break;
					case String:
						fprintf(stdout, " type string");
					break;
					case Void:
						fprintf(stdout, " type void");
					break;
					default:
						fprintf(stdout, " undefined type");
					break;
				}
			}
		}

		if ((tree->nodekind == ExpK && (tree->subkind.exp == IdK || (tree->subkind.exp == ConstantK && tree->expType == Char && tree->isArray))) ||
		(tree->nodekind == DeclK) ||
		(tree->nodekind == StmtK && (tree->subkind.stmt == CompoundK || tree->subkind.stmt == ForK)))
			fprintf(stdout," [mem: %s loc: %d size: %d]", memType, tree->location, tree->size);

		if ((tree->nodekind == StmtK && tree->subkind.stmt != NullK) || (tree->nodekind != StmtK))
			fprintf(stdout," [line: %d]\n", tree->lineno);
		
		for (i=0;i<MAXCHILDREN;i++)
		{
			printMemTree(tree->child[i], i, types);
		}
		
		
		if (tree != NULL && tree->nodekind == StmtK && tree->subkind.stmt == NullK)
		{
			//childNum = 1;
			tree = tree->sibling;
			continue;
		}
		else
		{
			tree = tree->sibling;
		}

		if (childNum <= -1)// && (tree->nodekind != StmtK || tree->subkind.stmt != NullK))
			childNum--;
		else
			childNum = -1;
	}
	UNINDENT;
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
					fprintf(stdout,"Op: %s", returnToken(tree->attr.op));
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
                    fprintf(stdout,"Assign: %s", returnToken(tree->attr.op));
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
		
		
		if (tree != NULL && tree->nodekind == StmtK && tree->subkind.stmt == NullK)
		{
			//childNum = 1;
			tree = tree->sibling;
			continue;
		}
		else
		{
			tree = tree->sibling;
		}

		if (childNum <= -1)// && (tree->nodekind != StmtK || tree->subkind.stmt != NullK))
			childNum--;
		else
			childNum = -1;
	}
	UNINDENT;
}
