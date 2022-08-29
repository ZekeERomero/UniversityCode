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
bool hasReturn(TreeNode* temp, SymbolTable* symbolTable);
void isUsed(TreeNode* tree, SymbolTable* symbolTable);
void checkUsed(std::string str, void* ptr);
bool isArray(TreeNode *temp, SymbolTable *symbolTable);
void semanticAnalysis(TreeNode *tree, SymbolTable *symbolTable, int childNum);
TreeNode* newExpNode(ExpKind kind, TokenData* token, TreeNode* c0 = NULL, TreeNode* c1 = NULL, TreeNode* c2 = NULL);
TreeNode* newStmtNode(StmtKind kind, TokenData* token, TreeNode* c0 = NULL, TreeNode* c1 = NULL, TreeNode* c2 = NULL);
TreeNode* newDeclNode(DeclKind kind, ExpType type, TokenData* token = NULL, TreeNode* c0 = NULL, TreeNode* c1 = NULL, TreeNode* c2 = NULL);

#endif
