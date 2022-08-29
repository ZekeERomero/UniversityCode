#ifndef GENCODE_H
#define GENCODE_H

#include "emitcode.h"
#include "scanType.h"
#include "symbolTable.h"
#include "parser.tab.h"
#include "string.h"
#include <stdlib.h>
#include <stdio.h>
#include <stack>

using namespace std;

void genCodeIO(TreeNode* tree, SymbolTable *symbolTable);
void genGlobals(TreeNode* tree, SymbolTable* symbolTable, bool arrays);
void genCode(TreeNode* tree, SymbolTable *symbolTable);
void genStatics(TreeNode* tree, SymbolTable* symbolTable, bool arrays);
void commentFunction(char* name);
void endFunction(char* name);

enum TOFFtype
{
	set,
	dec,
	inc
};

enum inType
{
	none,
	function,
	forloop,
	whileloop,
	ifstmt
};

#endif
