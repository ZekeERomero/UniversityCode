%{
#include "scanType.h"  // TokenData Type
#include "ioruntime.h"
#include "ourgetopt.h"
#include "symbolTable.h"
#include "semantic.h"
#include "yyerror.h"
#include "emitcode.h"
#include "gencode.h"
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
FILE *code;
FILE *mem = stdout;

TreeNode* ioTree;

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
void printMemTree(TreeNode* initialTree, TreeNode *tree, int childNum, bool types);
void setSibling(TreeNode *tree);
TreeNode* IORuntime(SymbolTable* symbolTable);
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

%}

/* this is included in the tab.h file */
%union {
	ExpType type;
	TokenData *tokenData;
	TreeNode *treeNode;
}

%token <tokenData> QUIT NUMCONST ID STRINGCONST CHARCONST BOOLCONST NONCHAR ILLEGALCHAR KEYWORD
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

program				: declList											{ fullTree = $1; }
					;

declList			: declList decl										{ $$ = addSibling($1, $2); }
					| decl												{ $$ = $1; }
					;

decl				: varDecl											{ $$ = $1; }
					| funDecl											{ $$ = $1; }
					| error												{ $$ = NULL; }
					;

varDecl				: typeSpec varDeclList SEMICOLON					{ $$ = $2;
																		  if ($$ != NULL)
																		  {
																			$$->expType = setType($1);
																			setSibling($$);
																		  }
																		  yyerrok; }
					| error varDeclList SEMICOLON						{ $$ = NULL;
																		  yyerrok; }
					| typeSpec error SEMICOLON							{ $$ = NULL; yyerrok; yyerrok; }
					;

scopedVarDecl		: STATIC typeSpec varDeclList SEMICOLON				{ $$ = $3;
																		  if ($$ != NULL)
																		  {
																			$$->expType = setType($2);
																			$$->isStatic = true;
																			$$->memory = LocalStatic;
																			setSibling($$);
																		  }
																		  yyerrok; }
					| typeSpec varDeclList SEMICOLON					{ $$ = $2;
																		 if ($$ != NULL)
																		  {
																			$$->expType = setType($1);
																			setSibling($$);
																		  }
																		  yyerrok; }
					| typeSpec error SEMICOLON							{ $$ = NULL; yyerrok; yyerrok; }
					;

varDeclList			: varDeclList COMMA varDeclInit						{ if ($1 != NULL && $3 != NULL)
																		  {
																		    $$ = addSibling($1, $3);
																		  }
																		  yyerrok; }
					| varDeclInit										{ $$ = $1; }
					| varDeclList COMMA error							{ $$ = NULL; }
					| error 											{ $$ = NULL; }
					;

varDeclInit			: varDeclId											{ $$ = $1; }
					| varDeclId COLON simpleExp							{ $$ = $1;
																		  if ($$ != NULL && $3 != NULL)
																		  {
																			$$->child[0] = $3;
																		  }
																		}
					| varDeclId COLON error								{ $$ = NULL; }
					| error COLON simpleExp								{ $$ = NULL; yyerrok; }
					;

varDeclId			: id												{ $$ = $1;
																		  $$->nodekind = DeclK;
																		  $$->subkind.decl = VarK;
																		  $$->size = 1; }
					| id LBRACKET NUMCONST RBRACKET						{ $$ = $1;
																		  $$->nodekind = DeclK;
																		  $$->subkind.decl = VarK;
																		  $$->isArray = true;
																		  $$->size = $3->nvalue + 1; }
					| id LBRACKET error									{ $$ = NULL; }
					| error RBRACKET									{ $$ = NULL; yyerrok; }
					;

id					: ID												{ $$ = newExpNode(IdK, $1);
																		  $$->attr.name = $1->id; }
					;

typeSpec			: BOOL												{ $$ = $1; }
					| CHAR												{ $$ = $1; }
					| INT												{ $$ = $1; }
					;

funDecl				: typeSpec id LPAREN parms RPAREN compoundStmt		{ $$ = $2;
																		  $$->nodekind = DeclK;
																		  $$->subkind.decl = FuncK;
																		  $$->expType = setType($1);
																		  $$->child[0] = $4;
																		  $$->child[1] = $6; }
					| id LPAREN parms RPAREN compoundStmt				{ $$ = $1;
																		  $$->nodekind = DeclK;
																		  $$->subkind.decl = FuncK;
																		  $$->expType = Void;
																		  $$->child[0] = $3;
																		  $$->child[1] = $5; }
					| typeSpec id LPAREN RPAREN compoundStmt			{ $$ = $2;
																		  $$->nodekind = DeclK;
																		  $$->subkind.decl = FuncK;
																		  $$->expType = setType($1);
																		  $$->child[1] = $5; }
				    | id LPAREN RPAREN compoundStmt						{ $$ = $1;
																		  $$->nodekind = DeclK;
																		  $$->subkind.decl = FuncK;
																		  $$->expType = Void;
																		  $$->child[1] = $4; }
					| typeSpec error									{ $$ = NULL; }
					| typeSpec id LPAREN error							{ $$ = NULL; }
					| id LPAREN error									{ $$ = NULL; }
					| id LPAREN parms RPAREN error						{ $$ = NULL; }
					;

parms				: parmList											{ $$ = $1; }
					;

parmList			: parmList SEMICOLON parmTypeList					{ $$ = addSibling($1, $3); }
					| parmTypeList										{ $$ = $1; }
					| parmList SEMICOLON error							{ $$ = NULL; }
					| error												{ $$ = NULL; }
					;

parmTypeList		: typeSpec parmIdList								{ $$ = $2;
																		  if ($$ != NULL)
																		  {
																			$$->expType = setType($1);
																			setSibling($$);
																		  }
																		}
					| typeSpec error									{ $$ = NULL; }
					;

parmIdList			: parmIdList COMMA parmId							{ $$ = addSibling($1, $3); yyerrok; }
					| parmId											{ $$ = $1; }
					| parmIdList COMMA error							{ $$ = NULL; }
					| error												{ $$ = NULL; }
					;

parmId				: id												{ $$ = $1;
																		  $$->nodekind = DeclK;
																		  $$->subkind.decl = ParamK; }
					| id LBRACKET RBRACKET								{ $$ = $1;
																		  $$->nodekind = DeclK;
																		  $$->subkind.decl = ParamK;
																		  $$->isArray = true; }
					;

stmt				: matchedStmt										{ $$ = $1; }
					| openStmt											{ $$ = $1; }
					;

matchedStmt			: expStmt											{ $$ = $1; }
					| compoundStmt										{ $$ = $1; }
					| matchedIterStmt									{ $$ = $1; }
					| matchedSelectStmt									{ $$ = $1; }
					| returnStmt										{ $$ = $1; }
					| breakStmt											{ $$ = $1; }
					;

openStmt			: openSelectStmt									{ $$ = $1; }
					| openIterStmt										{ $$ = $1; }
					;

expStmt				: exp SEMICOLON										{ $$ = $1; }
					| SEMICOLON											{ $$ = newStmtNode(NullK, $1); }
					| error SEMICOLON									{ $$ = NULL; yyerrok; }
					;

compoundStmt		: LCURLY localDecls stmtList RCURLY					{ $$ = newStmtNode(CompoundK, $1);
																		  $$->child[0] = $2;
																		  $$->child[1] = $3;
																		  yyerrok; }
					| LCURLY stmtList RCURLY							{ $$ = newStmtNode(CompoundK, $1);
																		  $$->child[1] = $2;
																		  yyerrok;}
					| LCURLY localDecls RCURLY							{ $$ = newStmtNode(CompoundK, $1);
																		  $$->child[0] = $2;
																		  yyerrok;}
					| LCURLY RCURLY										{ $$ = newStmtNode(CompoundK, $1);
																		  yyerrok; }
					;

localDecls			: localDecls scopedVarDecl							{ $$ = addSibling($1, $2); }
					| scopedVarDecl										{ $$ = $1; }
					;

stmtList			: stmtList stmt										{ $$ = addSibling($1, $2); }
					| stmt												{ $$ = $1; }
					;

matchedSelectStmt	: IF simpleExp THEN matchedStmt ELSE matchedStmt	{ $$ = newStmtNode(IfK, $1);
																		  $$->child[0] = $2;
																		  $$->child[1] = $4;
																		  $$->child[2] = $6; }
					| IF error											{ $$ = NULL; }
					| IF error ELSE matchedStmt							{ $$ = NULL; yyerrok; }
					| IF error THEN matchedStmt ELSE matchedStmt		{ $$ = NULL; yyerrok; }
					;

openSelectStmt		: IF simpleExp THEN stmt							{ $$ = newStmtNode(IfK, $1);
																		  $$->child[0] = $2;
																		  $$->child[1] = $4; }
					| IF simpleExp THEN matchedStmt ELSE openStmt		{ $$ = newStmtNode(IfK, $1);
																		  $$->child[0] = $2; 
																		  $$->child[1] = $4;
																		  $$->child[2] = $6; }
					| IF error THEN stmt								{ $$ = NULL; yyerrok; }
					| IF error THEN matchedStmt ELSE openStmt			{ $$ = NULL; yyerrok; }
					;

matchedIterStmt		: WHILE simpleExp DO matchedStmt					{ $$ = newStmtNode(WhileK, $1);
																		  $$->child[0] = $2;
																		  $$->child[1] = $4; }
					| FOR id ASGN iterRange DO matchedStmt				{ $$ = newStmtNode(ForK, $1);
																		  $$->child[0] = $2;
																		  $$->child[0]->nodekind = DeclK;
																		  $$->child[0]->subkind.decl = VarK;
																		  $$->child[0]->expType = Integer;
																		  $$->child[0]->memory = Local;
																		  $$->child[0]->size = 1;
																		  $$->child[0]->isInitialized = true;
																		  $$->child[1] = $4;
																		  $$->child[2] = $6; }
					| WHILE error DO matchedStmt						{ $$ = NULL; yyerrok; }
					| WHILE error										{ $$ = NULL; }
					| FOR id ASGN error DO matchedStmt					{ $$ = NULL; yyerrok; }
					| FOR error											{ $$ = NULL; }
					;

openIterStmt		: WHILE simpleExp DO openStmt						{ $$ = newStmtNode(WhileK, $1);
																		  $$->child[0] = $2;
																		  $$->child[1] = $4; }
					| FOR id ASGN iterRange DO openStmt					{ $$ = newStmtNode(ForK, $1);
																		  $$->child[0] = $2;
																		  $$->child[0]->nodekind = DeclK;
																		  $$->child[0]->subkind.decl = VarK;
																		  $$->child[0]->expType = Integer;
																		  $$->child[0]->memory = Local;
																		  $$->child[0]->size = 1;
																		  $$->child[0]->isInitialized = true;
																		  $$->child[1] = $4;
																		  $$->child[2] = $6;}
					| WHILE error DO openStmt							{ $$ = NULL; yyerrok; }
					| FOR id ASGN error DO openStmt						{ $$ = NULL; yyerrok; }
					;

iterRange			: simpleExp TO simpleExp							{ $$ = newStmtNode(RangeK, $2);
																		  $$->child[0] = $1;
																		  $$->child[1] = $3; }
					| simpleExp TO simpleExp BY simpleExp				{ $$ = newStmtNode(RangeK, $2);
																		  $$->child[0] = $1;
																		  $$->child[1] = $3;
																		  $$->child[2] = $5; }
					| simpleExp TO error								{ $$ = NULL; }
					| error BY error									{ $$ = NULL; yyerrok; }
					| simpleExp TO simpleExp BY error					{ $$ = NULL; }
					;

returnStmt			: RETURN SEMICOLON									{ $$ = newStmtNode(ReturnK, $1); }
					| RETURN exp SEMICOLON								{ $$ = newStmtNode(ReturnK, $1);
																		  $$->child[0] = $2; yyerrok; }
					| RETURN error SEMICOLON							{ $$ = NULL; yyerrok; }
					;

breakStmt			: BREAK SEMICOLON									{ $$ = newStmtNode(BreakK, $1); }
					;

exp					: mutable assignop exp								{ $$ = newExpNode(AssignK, $2);
																		  $$->attr.op = $2->tokenclass;
																		  $$->child[0] = $1;
																		  $$->child[1] = $3; }
					| mutable INC										{ $$ = newExpNode(AssignK, $2);
																		  $$->attr.op = $2->tokenclass;
																		  $$->child[0] = $1; }
					| mutable DEC										{ $$ = newExpNode(AssignK, $2);
																		  $$->attr.op = $2->tokenclass;
																		  $$->child[0] = $1; }
					| simpleExp											{ $$ = $1; }
					| error assignop exp								{ $$ = NULL; yyerrok; }
					| mutable assignop error							{ $$ = NULL; }
					| error INC											{ $$ = NULL; yyerrok; }
					| error DEC											{ $$ = NULL; yyerrok; }
					;

assignop			: ASGN												{ $$ = $1; }
					| ADDASS											{ $$ = $1; }
					| SUBASS											{ $$ = $1; }
					| MULASS											{ $$ = $1; }
					| DIVASS											{ $$ = $1; }
					;

simpleExp			: simpleExp OR andExp								{ $$ = newExpNode(OpK, $2);
																		  $$->attr.op = $2->tokenclass;
																		  $$->child[0] = $1;
																		  $$->child[1] = $3; }
					| andExp											{ $$ = $1; }
					| simpleExp OR error								{ $$ = NULL; }
					;

andExp				: andExp AND unaryRelExp							{ $$ = newExpNode(OpK, $2);
																		  $$->attr.op = $2->tokenclass;
																		  $$->child[0] = $1;
																		  $$->child[1] = $3; }
					| unaryRelExp										{ $$ = $1; }
					| andExp AND error									{ $$ = NULL; }
					;

unaryRelExp			: NOT unaryRelExp									{ $$ = newExpNode(OpK, $1);
																		  $$->attr.op = $1->tokenclass;
																		  $$->child[0] = $2; }
					| relExp											{ $$ = $1; }
					| NOT error											{ $$ = NULL; }
					;

relExp				: sumExp relop sumExp								{ $$ = newExpNode(OpK, $2);
																		  $$->attr.op = $2->tokenclass;
																		  $$->child[0] = $1;
																		  $$->child[1] = $3; }
					| sumExp											{ $$ = $1; }
					| sumExp relop error								{ $$ = NULL; }
					;

relop				: LESSER											{ $$ = $1; }
					| LEQ												{ $$ = $1; }
					| GREATER											{ $$ = $1; }
					| GEQ												{ $$ = $1; }
					| EQ												{ $$ = $1; }
					| NEQ												{ $$ = $1; }
					;

sumExp				: sumExp sumop mulExp								{ $$ = newExpNode(OpK, $2);
																		  $$->attr.op = $2->tokenclass;
																		  $$->child[0] = $1;
																		  $$->child[1] = $3; }
					| mulExp											{ $$ = $1; }
					| sumExp sumop error								{ $$ = NULL; }
					;

sumop				: ADD												{ $$ = $1; }
					| SUB												{ $$ = $1; }
					;

mulExp				: mulExp mulop unaryExp								{ $$ = newExpNode(OpK, $2);
																		  $$->attr.op = $2->tokenclass;
																		  $$->child[0] = $1; 
																		  $$->child[1] = $3; }
					| unaryExp											{ $$ = $1; }
					| mulExp mulop error								{ $$ = NULL; }
					;

mulop				: MUL												{ $$ = $1; }
					| DIV												{ $$ = $1; }
					| MOD												{ $$ = $1; }
					;

unaryExp			: unaryop unaryExp									{ $$ = newExpNode(OpK, $1);
																		  if ($1->tokenclass == SUB)
																			$$->attr.op = CHSIGN;
																		  else if ($1->tokenclass == MUL)
																			$$->attr.op = SIZEOF;
																		  else
					  														$$->attr.op = $1->tokenclass;
																		  $$->child[0] = $2; }
					| factor											{ $$ = $1; }
					| unaryop error										{ $$ = NULL; }
					;

unaryop				: SUB												{ $$ = $1; }
					| MUL												{ $$ = $1; }
					| QUESTION											{ $$ = $1; }
					;

factor				: mutable											{ $$ = $1; }
					| immutable											{ $$ = $1; }
					;

mutable				: id												{ $$ = $1; }
					| id LBRACKET exp RBRACKET							{ $$ = newExpNode(OpK, $2);
																		  $$->attr.op = $2->tokenclass;
																		  $$->child[0] = $1;
																		  $$->child[1] = $3;
																		  $$->child[0]->isArray = true; }
					;

immutable			: LPAREN exp RPAREN									{ $$ = $2;
																		  yyerrok; }
					| call												{ $$ = $1; }
					| constant											{ $$ = $1; }
					| LPAREN error										{ $$ = NULL; }
					;

call				: id LPAREN args RPAREN								{ $$ = $1;
																		  $$->nodekind = ExpK;
																		  $$->subkind.exp = CallK;
																		  $$->child[0] = $3; }
					| id LPAREN RPAREN									{ $$ = $1;
																		  $$->nodekind = ExpK;
																		  $$->subkind.exp = CallK; }
					| error LPAREN										{ $$ = NULL; yyerrok; }
					;

args				: argList											{ $$ = $1; }
					;

argList				: argList COMMA exp									{ $$ = addSibling($1, $3);
																		  yyerrok; }
					| exp												{ $$ = $1; }
					| argList COMMA error									{ $$ = NULL; }
					;

constant			: NUMCONST 											{ $$ = newExpNode(ConstantK, $1);
																		  $$->attr.value = $1->nvalue;
																		  $$->expType = Integer;}
					| CHARCONST											{ $$ = newExpNode(ConstantK, $1);
																		  $$->attr.cvalue = $1->cvalue;
																		  $$->expType = Char; }
					| STRINGCONST										{ $$ = newExpNode(ConstantK, $1);
																	      $$->attr.string = $1->svalue;
																		  $$->expType = Char;
																		  $$->isArray = true;
																		  $$->size = strlen($1->svalue) + 1 + $1->nullNum; }
					| BOOLCONST											{ $$ = newExpNode(ConstantK, $1);
																		  $$->attr.value = $1->nvalue;
																		  $$->expType = Boolean; }
					;

%%
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

	mem = stdout;

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

		ioTree = IORuntime(symbolTable); //insert I/O Runtime support
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
			{
				printTree(ioTree, 0, true);
				printTree(fullTree, -7, true);
			}

			if (Mflg == 1)
			{
				printMemTree(ioTree, ioTree, 0, true);
				printMemTree(fullTree, fullTree, -7, true);
				fprintf(mem, "Offset for end of global space: %d\n", goffset);
			}

			//code = stdout;
			char* fileName = argv[argc - 1];
			int size = strlen(fileName);
			fileName[size - 2] = 't';
			fileName[size - 1] = 'm';
			code = fopen(fileName , "w");
			if (code == NULL)
			{
				printf("ERROR: failed to open test.tm\n");
			}
			else
			{
				emitComment((char *) "C- compiler version C-F21");
				emitComment((char *) "Built: Dec 12, 2021 (toffset telemetry)");
				emitComment((char *) "Author: Ezequiel E. Romero");
				emitComment((char *) "File compiled: ", removeDirectory(argv[argc - 1]));
				emitComment((char *) NO_COMMENT);

				int start = emitSkip(1);
				genCodeIO(ioTree, symbolTable);
				genCode(fullTree, symbolTable);

				backPatchAJumpToHere(start, (char*)"Jump to init [backpatch]");
				emitComment((char *) "INIT");
				emitRM((char*)"LDA", 1, goffset, 0, (char*)"set first frame at end of globals");
				emitRM((char*)"ST", 1, 0, 1, (char*)"store old fp (point to self)");
				emitComment((char *) "INIT GLOBALS AND STATICS");
				genGlobals(fullTree, symbolTable, false);
				genGlobals(fullTree, symbolTable, true);
				genStatics(fullTree, symbolTable, false);
				genStatics(fullTree, symbolTable, true);
				
				emitComment((char *) "END INIT GLOBALS AND STATICS");
				emitRM((char*)"LDA", 3, 1, 7, (char*)"Return address in ac");
				int mainAddr = ((TreeNode*)symbolTable->lookup("main"))->addr;
				emitRM((char*)"JMP", 7, mainAddr - emitSkip(0) - 1, 7, (char*)"Jump to main");
				emitRO((char*)"HALT", 0, 0, 0, (char*)"DONE!");
				emitComment((char *) "END INIT");
			}
		}
	}

	fprintf(stdout, "Number of warnings: %d\n", numWarnings);        //WARNINGS
	fprintf(stdout, "Number of errors: %d\n", numErrors);		// ERROR

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

TreeNode* IORuntime(SymbolTable* symbolTable)
{
	std::stringstream name;

	TreeNode* outnl = newDeclNode(FuncK, UndefinedType);
	outnl->attr.name = strdup("outnl");
	outnl->expType = Void;
	outnl->lineno = -1;
	name.str(outnl->attr.name);
	outnl->memory = Global;
	outnl->size = -2;
	outnl->location = 0;
	symbolTable->insertGlobal(name.str(), outnl);
	outnl->sibling = NULL;

	TreeNode* outputc = newDeclNode(FuncK, UndefinedType);
	outputc->attr.name = strdup("outputc");
	outputc->expType = Void;
		outputc->child[0] = newDeclNode(ParamK, UndefinedType);
		outputc->child[0]->expType = Char;
		outputc->child[0]->attr.name = (char *)"*dummy*";
		outputc->child[0]->memory = Parameter;
		outputc->child[0]->size = 1;
		outputc->child[0]->location = -2;
		outputc->child[0]->lineno = -1;
	outputc->lineno = -1;
	name.str(outputc->attr.name);
	outputc->memory = Global;
	outputc->size = -3;
	outputc->location = 0;
	symbolTable->insertGlobal(name.str(), outputc);
	outputc->sibling = outnl;

	TreeNode* inputc = newDeclNode(FuncK, UndefinedType);
	inputc->attr.name = strdup("inputc");
	inputc->expType = Char;
	inputc->lineno = -1;
	name.str(inputc->attr.name);
	inputc->memory = Global;
	inputc->size = -2;
	inputc->location = 0;
	symbolTable->insertGlobal(name.str(), inputc);
	inputc->sibling = outputc;

	TreeNode* outputb = newDeclNode(FuncK, UndefinedType);
	outputb->attr.name = strdup("outputb");
	outputb->expType = Void;
		outputb->child[0] = newDeclNode(ParamK, UndefinedType);
		outputb->child[0]->expType = Boolean;
		outputb->child[0]->attr.name = (char *)"*dummy*";
		outputb->child[0]->memory = Parameter;
		outputb->child[0]->size = 1;
		outputb->child[0]->location = -2;
		outputb->child[0]->lineno = -1;
	outputb->lineno = -1;
	name.str(outputb->attr.name);
	outputb->memory = Global;
	outputb->size = -3;
	outputb->location = 0;
	symbolTable->insertGlobal(name.str(), outputb);
	outputb->sibling = inputc;

	TreeNode* inputb = newDeclNode(FuncK, UndefinedType);
	inputb->attr.name = strdup("inputb");
	inputb->expType = Boolean;
	inputb->lineno = -1;
	name.str(inputb->attr.name);
	inputb->memory = Global;
	inputb->size = -2;
	inputb->location = 0;
	symbolTable->insertGlobal(name.str(), inputb);
	inputb->sibling = outputb;

	TreeNode* output = newDeclNode(FuncK, UndefinedType);
	output->attr.name = strdup("output");
	output->expType = Void;
		output->child[0] = newDeclNode(ParamK, UndefinedType);
		output->child[0]->expType = Integer;
		output->child[0]->attr.name = (char *)"*dummy*";
		output->child[0]->memory = Parameter;
		output->child[0]->size = 1;
		output->child[0]->location = -2;
		output->child[0]->lineno = -1;
	output->lineno = -1;
	name.str(output->attr.name);
	output->memory = Global;
	output->size = -3;
	output->location = 0;
	symbolTable->insertGlobal(name.str(), output);
	output->sibling = inputb;

	TreeNode* input = newDeclNode(FuncK, UndefinedType);
	input->attr.name = strdup("input");
	input->expType = Integer;
	input->lineno = -1;
	name.str(input->attr.name);
	input->memory = Global;
	input->size = -2;
	input->location = 0;
	symbolTable->insertGlobal(name.str(), input);
	input->sibling = output;

	return input;
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
	t->skip = false;

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
	t->skip = false;

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
	t->skip = false;

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
			fprintf(mem, "Unknown token: %d", token);
	}

	return returnChar;
}

static void printSpaces(void)
{
	int i;
	for (i = 0; i < indentno; i++)
	{
		if (i % 3 == 0)
			fprintf(mem,".");
		fprintf(mem," ");
	}
}

void printMemTree(TreeNode *initialTree, TreeNode *tree, int childNum, bool types)
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
	
		if (childNum >= 0 && tree != initialTree && ((tree->nodekind == StmtK && tree->subkind.stmt != NullK) || (tree->nodekind != StmtK)))
		{
			fprintf(mem,"Child: %d  ", childNum);
		}
		else if ((tree != initialTree || tree == fullTree) && ((tree->nodekind == StmtK && tree->subkind.stmt != NullK) || (tree->nodekind != StmtK)))
		{
			fprintf(mem,"Sibling: %d  ", abs(childNum));
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
					fprintf(mem,"If");
				break;
				case WhileK:
					fprintf(mem,"While");
				break;
				case ForK:
					fprintf(mem,"For");
				break;
				case CompoundK:
					fprintf(mem,"Compound");
				break;
				case ReturnK:
					fprintf(mem,"Return");
				break;
				case BreakK:
                                        fprintf(mem,"Break");
                                break;
				case RangeK:
                                        fprintf(mem,"Range");
                                break;
				case NullK:
					//do nothing
				break;
				default:
					fprintf(mem,"Unknown ExpNode kind");
				break;
			}
		}
		else if (tree->nodekind == ExpK)
		{
			switch (tree->subkind.exp)
			{
				case OpK:
					fprintf(mem,"Op: %s", returnToken(tree->attr.op));
				break;
				case ConstantK:
					fprintf(mem,"Const ");
					switch(tree->expType)
					{
						case Integer:
							fprintf(mem,"%d", tree->attr.value);
						break;
						case Boolean:
							if (tree->attr.value == 0)
								fprintf(mem,"false");
							else
								fprintf(mem,"true");
						break;
						case Char:
							if (!tree->isArray)
								fprintf(mem,"'%c'", tree->attr.cvalue);
							else
								fprintf(mem,"\"%s\"", tree->attr.string);
						break;
						case String:
							fprintf(mem,"\"%s\"", tree->attr.string);
						break;
					}
				break;
				case IdK:
					fprintf(mem,"Id: %s", tree->attr.name);
				break;
				case AssignK:
                    fprintf(mem,"Assign: %s", returnToken(tree->attr.op));
                break;
				case CallK:
					fprintf(mem,"Call: %s", tree->attr.name);
                break;
				default:
					fprintf(mem,"Unknown ExpNode kind");
				break;
			}
		}
		else if (tree->nodekind == DeclK)
		{
			switch(tree->subkind.decl)
			{
				case VarK:
					fprintf(mem,"Var: %s", tree->attr.name);
				break;
				case FuncK:
					fprintf(mem,"Func: %s returns %stype %s", tree->attr.name, arrayCheck, expType);
				break;
				case ParamK:
					fprintf(mem,"Parm: %s", tree->attr.name);
				break;
				default:
					fprintf(mem,"Unknown ExpNode kind");
				break;
			}
		}
		else
		{
			fprintf(mem,"Unknown node kind");
		}

		fprintf(mem, "%s", arrayCheck);

		if (types)
		{
			if (tree->nodekind != StmtK && !(tree->nodekind == DeclK && tree->subkind.decl == FuncK))
			{
				if (!(tree->isStatic && !tree->isArray))
					fprintf(mem, " of");

				switch(tree->expType)
				{
					case Integer:
						fprintf(mem, " type int");
					break;
					case Char:
						fprintf(mem, " type char");
					break;
					case Boolean:
						fprintf(mem, " type bool");
					break;
					case String:
						fprintf(mem, " type string");
					break;
					case Void:
						fprintf(mem, " type void");
					break;
					default:
						fprintf(mem, " undefined type");
					break;
				}
			}
		}

		if ((tree->nodekind == ExpK && (tree->subkind.exp == IdK || (tree->subkind.exp == ConstantK && tree->expType == Char && tree->isArray))) ||
		(tree->nodekind == DeclK) ||
		(tree->nodekind == StmtK && (tree->subkind.stmt == CompoundK || tree->subkind.stmt == ForK)))
			fprintf(mem," [mem: %s loc: %d size: %d]", memType, tree->location, tree->size);

		if ((tree->nodekind == StmtK && tree->subkind.stmt != NullK) || (tree->nodekind != StmtK))
			fprintf(mem," [line: %d]\n", tree->lineno);
		
		for (i=0;i<MAXCHILDREN;i++)
		{
			printMemTree(initialTree, tree->child[i], i, types);
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
			fprintf(mem,"Child: %d  ", childNum);
		}
		else if (tree != fullTree && ((tree->nodekind == StmtK && tree->subkind.stmt != NullK) || (tree->nodekind != StmtK)))
		{
			fprintf(mem,"Sibling: %d  ", abs(childNum));
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
					fprintf(mem,"If");
				break;
				case WhileK:
					fprintf(mem,"While");
				break;
				case ForK:
					fprintf(mem,"For");
				break;
				case CompoundK:
					fprintf(mem,"Compound");
				break;
				case ReturnK:
					fprintf(mem,"Return");
				break;
				case BreakK:
                                        fprintf(mem,"Break");
                                break;
				case RangeK:
                                        fprintf(mem,"Range");
                                break;
				case NullK:
					//do nothing
				break;
				default:
					fprintf(mem,"Unknown ExpNode kind");
				break;
			}
		}
		else if (tree->nodekind == ExpK)
		{
			switch (tree->subkind.exp)
			{
				case OpK:
					fprintf(mem,"Op: %s", returnToken(tree->attr.op));
				break;
				case ConstantK:
					fprintf(mem,"Const ");
					switch(tree->expType)
					{
						case Integer:
							fprintf(mem,"%d", tree->attr.value);
						break;
						case Boolean:
							if (tree->attr.value == 0)
								fprintf(mem,"false");
							else
								fprintf(mem,"true");
						break;
						case Char:
							if (!tree->isArray)
								fprintf(mem,"'%c'", tree->attr.cvalue);
							else
								fprintf(mem,"is array \"%s\"", tree->attr.string);
						break;
						case String:
							fprintf(mem,"\"%s\"", tree->attr.string);
						break;
					}
				break;
				case IdK:
					fprintf(mem,"Id: %s", tree->attr.name);
				break;
				case AssignK:
                    fprintf(mem,"Assign: %s", returnToken(tree->attr.op));
                break;
				case CallK:
					fprintf(mem,"Call: %s", tree->attr.name);
                break;
				default:
					fprintf(mem,"Unknown ExpNode kind");
				break;
			}
		}
		else if (tree->nodekind == DeclK)
		{
			switch(tree->subkind.decl)
			{
				case VarK:
					fprintf(mem,"Var: %s %sof %stype %s", tree->attr.name, arrayCheck, staticCheck, expType);
				break;
				case FuncK:
					fprintf(mem,"Func: %s returns %stype %s", tree->attr.name, arrayCheck, expType);
				break;
				case ParamK:
					fprintf(mem,"Parm: %s %sof type %s", tree->attr.name, arrayCheck, expType);
				break;
				default:
					fprintf(mem,"Unknown ExpNode kind");
				break;
			}
		}
		else
		{
			fprintf(mem,"Unknown node kind");
		}

		if (tree->nodekind != DeclK && tree->nodekind != StmtK)
		{
			switch(tree->expType)
			{
				case Integer:
					fprintf(mem, " of type int");
				break;
				case Char:
					fprintf(mem, " of type char");
				break;
				case Boolean:
					fprintf(mem, " of type bool");
				break;
				case String:
					fprintf(mem, " of type string");
				break;
				case Void:
					fprintf(mem, " of type void");
				break;
				default:
					fprintf(mem, " of undefined type");
				break;
			}
		}

		if ((tree->nodekind == StmtK && tree->subkind.stmt != NullK) || (tree->nodekind != StmtK))
			fprintf(mem," [line: %d]\n", tree->lineno);
		
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
