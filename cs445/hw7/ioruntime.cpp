#include "ioruntime.h"

/*typeSpec id LPAREN parms RPAREN compoundStmt{ $$ = $2;
								  $$->nodekind = DeclK;
								  $$->subkind.decl = FuncK;
								  if ($1->tokenclass == INT)
									$$->expType = Integer;
								  else if ($1->tokenclass == BOOL)
									$$->expType = Boolean;
								  else if ($1->tokenclass == CHAR)
									$$->expType = Char;
								  $$->child[0] = $4;
								  $$->child[1] = $6; }*/

//void IORuntime(SymbolTable* symbolTable)

	//std::stringstream name;

	/*TreeNode* output = newDeclNode(FuncK, UndefinedType);
	output->attr.name = strdup("output");
	output->expType = Void;
		output->child[0] = newDeclNode(ParamK, UndefinedType);
		output->child[0]->expType = Integer;
	output->lineno = -1;
	name.str(output->attr.name);
	symbolTable->insertGlobal(name.str(), output);

	/*TreeNode* outputb = newDeclNode(FuncK, UndefinedType);
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
	inputb->expType = Integer;
	inputb->lineno = -1;
	name.str(inputb->attr.name);
	symbolTable->insertGlobal(name.str(), inputb);

	TreeNode* inputc = newDeclNode(FuncK, UndefinedType);
	inputc->attr.name = strdup("inputc");
	inputc->expType = Integer;
	inputc->lineno = -1;
	name.str(inputc->attr.name);
	symbolTable->insertGlobal(name.str(), inputc);

	TreeNode* outnl = newDeclNode(FuncK, UndefinedType);
	outnl->attr.name = strdup("outnl");
	outnl->expType = Void;
	outnl->lineno = -1;
	name.str(outnl->attr.name);
	symbolTable->insertGlobal(name.str(), outnl);*/
