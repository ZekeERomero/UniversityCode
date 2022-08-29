#ifndef _SEMANTIC_H_
#define _SEMANTIC_H_

#include "scanType.h"
#include "symbolTable.h"
#include "parser.tab.h"
#include "string.h"
#include <stdlib.h>
#include <stdio.h>
#include <sstream>

using namespace std;

char* returnToken(OpKind token);
char* returnExpType(ExpType type);
bool isArray(TreeNode *temp, SymbolTable *symbolTable);
void semanticAnalysis(TreeNode *tree, SymbolTable *symbolTable);

#endif
