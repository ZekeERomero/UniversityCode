%{
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

%}

/* this is included in the tab.h file */
%union {
	ExpType type;
	TokenData *tokenData;
	TreeNode *treeNode;
}

%token <tokenData> QUIT NUMCONST ID STRINGCONST CHARCONST BOOLCONST NONCHAR ILLEGALCHAR OPERATION KEYWORD
%token <tokenData> BOOL CHAR INT
%token <tokenData> EQ GREATER LESSER SEMICOLON
%token <tokenData> COMMA LCURLY RCURLY LBRACKET RBRACKET LPAREN RPAREN COLON QUESTION
%token <tokenData> MATHOP ADDASS SUBASS MULASS DIVASS INC DEC LEQ GEQ NEQ ASGN
%token <tokenData> ADD SUB MUL DIV MOD
%token <tokenData> BREAK TO BY IF THEN ELSE WHILE DO FOR NOT STATIC OR AND RETURN
%token <tokendata> CHSIGN SIZEOF

%type <tokenData> typeSpec sumop mulop relop unaryop assignop

%type <treeNode> program declList decl varDecl scopedVarDecl varDeclList varDeclInit
%type <treeNode> varDeclId  /*typeSpec*/ funDecl parms parmList parmTypeList parmIdList
%type <treeNode> parmId stmt matchedStmt openStmt expStmt compoundStmt localDecls
%type <treeNode> stmtList matchedSelectStmt openSelectStmt matchedIterStmt openIterStmt
%type <treeNode> iterRange returnStmt breakStmt exp /* assignop */ simpleExp andExp unaryRelExp
%type <treeNode> relExp /* relop */ sumExp /* sumop */ mulExp /* mulop */ unaryExp /* unaryop */ factor mutable
%type <treeNode> immutable call args argList constant id

%%

program		: declList	{ fullTree = $1; }
		;

declList	: declList decl	{ TreeNode *t = $1;
				  if (t != NULL)
				  {
					while (t->sibling != NULL)
						t = t->sibling;
					t->sibling = $2;
					$$ = $1;
				  }
				  else
				  {
					$$ = $2;
				  }
				}
		| decl		{ $$ = $1; }
		;

decl		: varDecl { $$ = $1; }
		| funDecl { $$ = $1; }
		;

varDecl		: typeSpec varDeclList SEMICOLON	{ $$ = $2;
							  if ($1->tokenclass == INT)
							  	$$->expType = Integer;
							  else if ($1->tokenclass == BOOL)
								$$->expType = Boolean;
							  else if ($1->tokenclass == CHAR)
								$$->expType = Char;
							  setSibling($$); }
		;

scopedVarDecl	: STATIC typeSpec varDeclList SEMICOLON	{ $$ = $3;
							  if ($2->tokenclass == INT)
								$$->expType = Integer;
							  else if ($2->tokenclass == BOOL)
								$$->expType = Boolean;
							  else if ($2->tokenclass == CHAR)
							  	$$->expType = Char;
							  $$->isStatic = true;
							  setSibling($$); }
		| varDecl				{ $$ = $1; }
		;

varDeclList	: varDeclList COMMA varDeclInit { TreeNode *t = $1;
						  if (t != NULL)
						  {
							while (t->sibling != NULL)
								t = t->sibling;
							t->sibling = $3;
							$$ = $1;
						  }
						  else
						  {
							$$ = $3;
						  } 
						}
		| varDeclInit			{ $$ = $1; }
		;

varDeclInit	: varDeclId			{ $$ = $1; }
		| varDeclId COLON simpleExp	{ $$ = $1;
						  $$->child[0] = $3; }
		;

varDeclId	: id					{ $$ = $1;
							  $$->nodekind = DeclK;
							  $$->subkind.decl = VarK; }
		| id LBRACKET NUMCONST RBRACKET		{ $$ = $1;
							  $$->nodekind = DeclK;
							  $$->subkind.decl = VarK;
							  $$->isArray = true; }
		;

id		: ID	{ $$ = newExpNode(IdK, $1);
			  $$->attr.name = $1->id; }

typeSpec	: BOOL	{ $$ = $1; }
		| CHAR	{ $$ = $1; }
		| INT	{ $$ = $1; }
		;

funDecl		: typeSpec id LPAREN parms RPAREN compoundStmt	{ $$ = $2;
								  $$->nodekind = DeclK;
								  $$->subkind.decl = FuncK;
								  if ($1->tokenclass == INT)
									$$->expType = Integer;
								  else if ($1->tokenclass == BOOL)
									$$->expType = Boolean;
								  else if ($1->tokenclass == CHAR)
									$$->expType = Char;
								  $$->child[0] = $4; 
								  $$->child[1] = $6; }
		| id LPAREN parms RPAREN compoundStmt		{ $$ = $1;
								  $$->nodekind = DeclK;
								  $$->subkind.decl = FuncK;
								  $$->expType = Void;
								  $$->child[0] = $3;
								  $$->child[1] = $5; }
		| typeSpec id LPAREN RPAREN compoundStmt	{ $$ = $2;
								  $$->nodekind = DeclK;
								  $$->subkind.decl = FuncK;
								  if ($1->tokenclass == INT)
									$$->expType = Integer;
								  else if ($1->tokenclass == BOOL)
									$$->expType = Boolean;
								  else if ($1->tokenclass == CHAR)
									$$->expType = Char;
								  $$->child[1] = $5; }
                | id LPAREN RPAREN compoundStmt			{ $$ = $1;
								  $$->nodekind = DeclK;
								  $$->subkind.decl = FuncK;
								  $$->expType = Void;
								  $$->child[1] = $4; }
		;

parms		: parmList	{ $$ = $1; }
		;

parmList	: parmList SEMICOLON parmTypeList	{ TreeNode *t = $1;
							  if (t != NULL)
							  {
								while (t->sibling != NULL)
									t = t->sibling;
								t->sibling = $3;
								$$ = $1;
							  }
							  else
							  {
								$$ = $3;
							  } 
							}
		| parmTypeList				{ $$ = $1; }
		;

parmTypeList	: typeSpec parmIdList	{ $$ = $2;
					  if ($1->tokenclass == INT)
						$$->expType = Integer;
					  else if ($1->tokenclass == BOOL)
						$$->expType = Boolean;
					  else if ($1->tokenclass == CHAR)
						$$->expType = Char;
					  setSibling($$); }
		;

parmIdList	: parmIdList COMMA parmId	{ TreeNode *t = $1;
						  if (t != NULL)
						  {
							while (t->sibling != NULL)
								t = t->sibling;
							t->sibling = $3;
							$$ = $1;
						  }
						  else
						  {
							$$ = $3;
						  }
						}
		| parmId			{ $$ = $1; }
		;

parmId		: id			{ $$ = $1;
					  $$->nodekind = DeclK;
					  $$->subkind.decl = ParamK; }
		| id LBRACKET RBRACKET	{ $$ = $1;
					  $$->nodekind = DeclK;
					  $$->subkind.decl = ParamK;
					  $$->isArray = true; }
		;

stmt		: matchedStmt	{ $$ = $1; }
		| openStmt	{ $$ = $1; }
		;

matchedStmt	: expStmt		{ $$ = $1; }
		| compoundStmt		{ $$ = $1; }
		| matchedIterStmt	{ $$ = $1; }
		| matchedSelectStmt	{ $$ = $1; }
		| returnStmt		{ $$ = $1; }
		| breakStmt		{ $$ = $1; }
		;

openStmt	: openSelectStmt	{ $$ = $1; }
		| openIterStmt		{ $$ = $1; }
		;

expStmt		: exp SEMICOLON	{ $$ = $1; }
		| SEMICOLON	{ $$ = newStmtNode(NullK, $1); }
		;

compoundStmt	: LCURLY localDecls stmtList RCURLY	{ $$ = newStmtNode(CompoundK, $1);
							  $$->child[0] = $2;
							  $$->child[1] = $3; }
		| LCURLY stmtList RCURLY		{ $$ = newStmtNode(CompoundK, $1);
							  $$->child[1] = $2; }
		| LCURLY localDecls RCURLY		{ $$ = newStmtNode(CompoundK, $1);
							  $$->child[0] = $2; }
                | LCURLY RCURLY				{ $$ = newStmtNode(CompoundK, $1); }
		;

localDecls	: localDecls scopedVarDecl	{ TreeNode *t = $1;
						  if (t != NULL)
						  {
							while (t->sibling != NULL)
								t = t->sibling;
							t->sibling = $2;
							$$ = $1;
						  }
						  else
						  {
							$$ = $2;
						  } }
		| scopedVarDecl			{ $$ = $1; }
		;

stmtList	: stmtList stmt	{ TreeNode *t = $1;
				  if (t != NULL)
				  {
					while (t->sibling != NULL)
						t = t->sibling;
					t->sibling = $2;
					$$ = $1;
				  }
				  else
				  {
					$$ = $2;
				  } }
		| stmt		{ $$ = $1; }

matchedSelectStmt
		: IF simpleExp THEN matchedStmt ELSE matchedStmt	{ $$ = newStmtNode(IfK, $1);
									  $$->child[0] = $2;
									  $$->child[1] = $4;
									  $$->child[2] = $6; }
		;

openSelectStmt	: IF simpleExp THEN stmt			{ $$ = newStmtNode(IfK, $1);
								  $$->child[0] = $2;
								  $$->child[1] = $4; }
		| IF simpleExp THEN matchedStmt ELSE openStmt	{ $$ = newStmtNode(IfK, $1);
								  $$->child[0] = $2; 
								  $$->child[1] = $4;
								  $$->child[2] = $6; }

matchedIterStmt	: WHILE simpleExp DO matchedStmt	{ $$ = newStmtNode(WhileK, $1);
							  $$->child[0] = $2;
							  $$->child[1] = $4; }
		| FOR id ASGN iterRange DO matchedStmt	{ $$ = newStmtNode(ForK, $1);
							  $$->child[0] = $2;
							  $$->child[0]->nodekind = DeclK;
							  $$->child[0]->subkind.decl = VarK;
							  $$->child[0]->expType = Integer;
							  $$->child[1] = $4;
							  $$->child[2] = $6; }
		;

openIterStmt	: WHILE simpleExp DO openStmt		{ $$ = newStmtNode(WhileK, $1);
							  $$->child[0] = $2;
							  $$->child[1] = $4; }
		| FOR id ASGN iterRange DO openStmt	{ $$ = newStmtNode(ForK, $1);
							  $$->child[0] = $2;
							  $$->child[0]->nodekind = DeclK;
							  $$->child[0]->subkind.decl = VarK;
							  $$->child[0]->expType = Integer;
							  $$->child[1] = $4;
							  $$->child[2] = $6; }
		;

iterRange	: simpleExp TO simpleExp		{ $$ = newStmtNode(RangeK, $2);
							  $$->child[0] = $1;
							  $$->child[1] = $3; }
		| simpleExp TO simpleExp BY simpleExp	{ $$ = newStmtNode(RangeK, $2);
							  $$->child[0] = $1;
							  $$->child[1] = $3;
							  $$->child[2] = $5; }
		;

returnStmt	: RETURN SEMICOLON	{ $$ = newStmtNode(ReturnK, $1); }
		| RETURN exp SEMICOLON	{ $$ = newStmtNode(ReturnK, $1);
					  $$->child[0] = $2; }
		;

breakStmt	: BREAK SEMICOLON	{ $$ = newStmtNode(BreakK, $1); }
		;

exp		: mutable assignop exp	{ $$ = newExpNode(AssignK, $2);
					  $$->attr.op = $2->tokenclass;
					  $$->child[0] = $1;
					  $$->child[1] = $3; }
		| mutable INC		{ $$ = newExpNode(AssignK, $2);
					  $$->attr.op = $2->tokenclass;
					  $$->child[0] = $1; }
		| mutable DEC		{ $$ = newExpNode(AssignK, $2);
					  $$->attr.op = $2->tokenclass;
					  $$->child[0] = $1; }
		| simpleExp { $$ = $1; }
		;

assignop	: ASGN		{ $$ = $1; }
		| ADDASS	{ $$ = $1; }
		| SUBASS	{ $$ = $1; }
		| MULASS	{ $$ = $1; }
		| DIVASS	{ $$ = $1; }
		;

simpleExp	: simpleExp OR andExp	{ $$ = newExpNode(OpK, $2);
					  $$->attr.op = $2->tokenclass;
					  $$->child[0] = $1;
					  $$->child[1] = $3; }
		| andExp		{ $$ = $1; }
		;

andExp		: andExp AND unaryRelExp	{ $$ = newExpNode(OpK, $2);
						  $$->attr.op = $2->tokenclass;
						  $$->child[0] = $1;
						  $$->child[1] = $3; }
		| unaryRelExp 			{ $$ = $1; }
		;

unaryRelExp	: NOT unaryRelExp	{ $$ = newExpNode(OpK, $1);
					  $$->attr.op = $1->tokenclass;
					  $$->child[0] = $2; }
		| relExp 		{ $$ = $1; }
		;

relExp		: sumExp relop sumExp	{ $$ = newExpNode(OpK, $2);
                                          $$->attr.op = $2->tokenclass;
					  $$->child[0] = $1;
                                          $$->child[1] = $3; }
		| sumExp		{ $$ = $1; }
		;

relop		: LESSER	{ $$ = $1; }
		| LEQ		{ $$ = $1; }
		| GREATER	{ $$ = $1; }
		| GEQ		{ $$ = $1; }
		| EQ		{ $$ = $1; }
		| NEQ		{ $$ = $1; }
		;

sumExp		: sumExp sumop mulExp	{ $$ = newExpNode(OpK, $2);
					  $$->attr.op = $2->tokenclass;
					  $$->child[0] = $1;
					  $$->child[1] = $3; }
		| mulExp		{ $$ = $1; }
		;

sumop		: ADD	{ $$ = $1; }
		| SUB	{ $$ = $1; }
		;

mulExp		: mulExp mulop unaryExp	{ $$ = newExpNode(OpK, $2);
					  $$->attr.op = $2->tokenclass;
					  $$->child[0] = $1; 
					  $$->child[1] = $3; }
		| unaryExp		{ $$ = $1; }
		;

mulop		: MUL	{ $$ = $1; }
		| DIV	{ $$ = $1; }
		| MOD	{ $$ = $1; }
		;

unaryExp	: unaryop unaryExp	{ $$ = newExpNode(OpK, $1);
					  if ($1->tokenclass == SUB)
						$$->attr.op = CHSIGN;
					  else if ($1->tokenclass == MUL)
						$$->attr.op = SIZEOF;
					  else
					  	$$->attr.op = $1->tokenclass;
					  $$->child[0] = $2; }
		| factor		{ $$ = $1; }
		;

unaryop		: SUB		{ $$ = $1; }
		| MUL		{ $$ = $1; }
		| QUESTION	{ $$ = $1; }
		;

factor		: mutable	{ $$ = $1; }
		| immutable	{ $$ = $1; }
		;

mutable		: id				{ $$ = $1; }
		| id LBRACKET exp RBRACKET	{ $$ = newExpNode(OpK, $2);
						  $$->attr.op = $2->tokenclass;
						  $$->child[0] = $1;
						  $$->child[1] = $3;
						  $$->child[0]->isArray = true; }
		;

immutable	: LPAREN exp RPAREN	{ $$ = $2; }
		| call			{ $$ = $1; }
		| constant		{ $$ = $1; }
		;

call		: id LPAREN args RPAREN	{ $$ = $1;
					  $$->nodekind = ExpK;
					  $$->subkind.exp = CallK;
					  $$->child[0] = $3; }
		| id LPAREN RPAREN	{ $$ = $1;
					  $$->nodekind = ExpK;
					  $$->subkind.exp = CallK; }
		;

args		: argList	{ $$ = $1; }
		;

argList		: argList COMMA exp	{ TreeNode *t = $1;
					  if (t != NULL)
					  {
						while (t->sibling != NULL)
							t = t->sibling;
						t->sibling = $3;
						$$ = $1;
					  }
					  else
					  {
						$$ = $3;
					  } }
		| exp			{ $$ = $1; }
		;

constant	: NUMCONST 	{ $$ = newExpNode(ConstantK, $1);
				  $$->attr.value = $1->nvalue;
				  $$->expType = Integer;}
		| CHARCONST	{ $$ = newExpNode(ConstantK, $1);
                                  $$->attr.cvalue = $1->cvalue;
				  $$->expType = Char; }
		| STRINGCONST	{ $$ = newExpNode(ConstantK, $1);
                                  $$->attr.string = $1->svalue;
				  $$->expType = Char;
					$$->isArray = true; }
		| BOOLCONST	{ $$ = newExpNode(ConstantK, $1);
                                  $$->attr.value = $1->nvalue;
				  $$->expType = Boolean; }
		;

%%
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

