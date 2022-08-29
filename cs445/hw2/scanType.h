#ifndef SCANTYPE_H
#define SCANTYPE_H

#define MAXCHILDREN 3

struct TokenData {
	int tokenclass; // token class
	int linenum; // line where found
	char *tokenstr; // what string was actually read
	char *id; // any id variable name
	char cvalue; // any character value
	int nvalue; // any numeric value or Boolean value
	char *svalue; // any string value e.g. an id
};

// Kinds of Operators
// these are the token numbers for the operators same as in flex
typedef int OpKind;
// Kinds of Statements
//typedef enum {DeclK, StmtK, ExpK} NodeKind;
enum NodeKind {DeclK, StmtK, ExpK};
// Subkinds of Declarations
enum DeclKind {VarK, FuncK, ParamK};
// Subkinds of Statements
enum StmtKind {NullK, IfK, WhileK, ForK, CompoundK, ReturnK, BreakK, RangeK};
// Subkinds of Expressions
enum ExpKind {OpK, ConstantK, IdK, AssignK, InitK, CallK};
// ExpType is used for type checking (Void means no type or value, UndefinedType means undefined)
enum ExpType {Void, Integer, Boolean, Char, CharInt, String, Equal, UndefinedType};
// What kind of scoping is used? (decided during typing)
enum VarKind {None, Local, Global, Parameter, LocalStatic};


typedef struct treeNode
{
	// connectivity in the tree
	struct treeNode *child[MAXCHILDREN]; // children of the node
	struct treeNode *sibling; // siblings for the node
	
	// what kind of node
	int lineno; // linenum relevant to this node
	NodeKind nodekind; // type of this node
	union // subtype of type
	{
		DeclKind decl; // used when DeclK
		StmtKind stmt; // used when StmtK
		ExpKind exp; // used when ExpK
	} subkind;

	// extra properties about the node depending on type of the node
	union // relevant data to type -> attr
	{
		OpKind op; // type of token (same as in bison)
		int value; // used when an integer constant or boolean
		unsigned char cvalue; // used when a character
		char *string; // used when a string constant
		char *name; // used when IdK
	} attr;
	
	ExpType expType; // used when ExpK for type checking
	bool isArray; // is this an array
	bool isStatic; // is staticly allocated?
	
	// even more semantic stuff will go here in later assignments.
} TreeNode;

#endif
