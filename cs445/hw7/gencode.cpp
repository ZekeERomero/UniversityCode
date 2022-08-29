#include "gencode.h"

bool printExpression = true;
bool inParameter = false;
bool skipSibling = false;
stack<int> breakoffset;
int toff = -2;

/*int sizeOfDigits(int num)
{
	int digits = 1;

	if (num < 0) digits++;

	while (abs(num) >= 10)
	{
		num /= 10;
		digits += 1;
	}

	return digits;
}*/

void loadArrayAddress(TreeNode* tree, int reg, SymbolTable* symbolTable)
{
	if (tree->memory != Parameter)
		emitRM((char*)"LDA", reg, tree->location, !tree->isGlobal && !tree->isStatic, (char*)"Load address of base of array", tree->attr.name);
	else
		emitRM((char*)"LD", reg, tree->location, !tree->isGlobal && !tree->isStatic, (char*)"Load address of base of array", tree->attr.name);
}

void TOFF(TOFFtype type, int offset = 0)
{
	if (type == dec)
		offset = --toff;
	else if (type == inc)
		offset = ++toff;
	else
		toff = offset;
	
	if (type == set)
		emitComment((char*)"TOFF set:", offset);
	else if (type == dec)
		emitComment((char*)"TOFF dec:", offset);
	else
		emitComment((char*)"TOFF inc:", offset);
}

void genGlobals(TreeNode* tree, SymbolTable* symbolTable, bool arrays)
{
	while (tree != NULL)
	{
		if (tree->nodekind == DeclK)
		{
			if (tree->subkind.decl == VarK)
			{
				if (tree->isArray && tree->isGlobal && arrays)
				{
					emitRM((char*)"LDC", 3, tree->size - 1, 6, (char*)"load size of array", tree->attr.name);
					emitRM((char*)"ST", 3, tree->location + 1, !tree->isGlobal && !tree->isStatic, (char*)"save size of array", tree->attr.name);
				}
				if (tree->child[0] != NULL && tree->isGlobal && !arrays)
				{
					printExpression = false;
					genCode(tree->child[0], symbolTable);
					emitRM((char*)"ST", 3, tree->location, !tree->isGlobal && !tree->isStatic, (char*)"Store variable", tree->attr.name);
					printExpression = true;
				}
			}
		}

		tree = tree->sibling;
	}
}

void genStatics(TreeNode* tree, SymbolTable* symbolTable, bool arrays)
{
	while (tree != NULL)
	{
		if (tree->nodekind == DeclK)
		{
			if (tree->subkind.decl == VarK)
			{
				if (tree->isArray && tree->isStatic && arrays)
				{
					emitRM((char*)"LDC", 3, tree->size - 1, 6, (char*)"load size of array", tree->attr.name);
					emitRM((char*)"ST", 3, tree->location + 1, !tree->isGlobal && !tree->isStatic, (char*)"save size of array", tree->attr.name);
				}
				if (tree->child[0] != NULL && tree->isStatic && !arrays)
				{
					printExpression = false;
					genCode(tree->child[0], symbolTable);
					emitRM((char*)"ST", 3, tree->location, !tree->isGlobal && !tree->isStatic, (char*)"Store variable", tree->attr.name);
					printExpression = true;
				}
			}
		}

		for (int i = 0; i < 3; i++)
		{
			genStatics(tree->child[i], symbolTable, arrays);
		}

		tree = tree->sibling;
	}
}

int siblingCount(TreeNode* tree)
{
	int num = 0;

	while (tree != NULL)
	{
		tree = tree->sibling;
		num++;
	}

	return num;
}

void genCode(TreeNode* tree, SymbolTable *symbolTable)
{
	while (tree != NULL)
	{
		if (tree->nodekind == DeclK)
		{
			if (tree->subkind.decl == FuncK)
			{
				string str(tree->attr.name);

				TreeNode* temp = (TreeNode*)symbolTable->lookup(str);

				if (temp != NULL)
					temp->addr = emitSkip(0);

				commentFunction(tree->attr.name);
				TOFF(set, tree->size);
				emitRM((char*)"ST", 3, -1, 1, (char*)"Store return address");
				genCode(tree->child[1], symbolTable);
				emitComment((char*) "Add standard closing in case there is no return statement");
				emitRM((char*)"LDC", 2, 0, 6, (char*)"Set return value to 0");
				emitRM((char*)"LD", 3, -1, 1, (char*)"Load return address");
				emitRM((char*)"LD", 1, 0, 1, (char*)"Adjust fp");
				emitRM((char*)"JMP", 7, 0, 3, (char*)"Return");
				endFunction(tree->attr.name);

				if(strcmp(tree->attr.name, "main")) //FIX LATER
					emitComment((char*)NO_COMMENT);
			}
			if (tree->subkind.decl == VarK)
			{
				if (tree->isArray && !tree->isGlobal && !tree->isStatic)
				{
					emitRM((char*)"LDC", 3, tree->size - 1, 6, (char*)"load size of array", tree->attr.name);
					emitRM((char*)"ST", 3, tree->location + 1, !tree->isGlobal && !tree->isStatic, (char*)"save size of array", tree->attr.name);
				}
				if (tree->child[0] != NULL && !tree->isGlobal && !tree->isStatic)
				{
					printExpression = false;
					genCode(tree->child[0], symbolTable);
					if (!(tree->child[0]->expType == Char && tree->child[0]->isArray))
					{
						emitRM((char*)"ST", 3, tree->location, !tree->isGlobal && !tree->isStatic, (char*)"Store variable", tree->attr.name);
					}
					else
					{
						emitRM((char*)"LDA", 4, tree->location, 1, (char*)"address of lhs");
						emitRM((char*)"LD", 5, 1, 3, (char*)"size of rhs");
						emitRM((char*)"LD", 6, 1, 4, (char*)"size of lhs");
						emitRO((char*)"SWP", 5, 6, 6, (char*)"pick smallest size");
						emitRO((char*)"MOV", 4, 3, 5, (char*)"array op =");
					}
					printExpression = true;
				}
			}
		}
		if (tree->nodekind == ExpK)
		{
			if (tree->subkind.exp == OpK)
			{
				//if (printExpression)
					//emitComment((char*)"EXPRESSION");

				int op = tree->attr.op;

				if (op == LBRACKET)
				{
					loadArrayAddress(tree->child[0], 3, symbolTable);
					//if (!inParameter)
						//emitRM((char*)"LDA", 3, tree->child[0]->location, !tree->child[0]->isGlobal && !tree->child[0]->isStatic, (char*)"Load address of base of array", tree->child[0]->attr.name);
					//else
					//	emitRM((char*)"LD", 3, tree->child[0]->location, !tree->child[0]->isGlobal && !tree->child[0]->isStatic, (char*)"Load address of base of array", tree->child[0]->attr.name);
					emitRM((char*)"ST", 3, toff, 1, (char*)"Push left side");
					TOFF(dec);
					genCode(tree->child[1], symbolTable);
					TOFF(inc);
					emitRM((char*)"LD", 4, toff, 1, (char*)"Pop left into ac1");
					emitRO((char*)"SUB", 3, 4, 3, (char*)"compute location from index");
					emitRM((char*)"LD", 3, 0, 3, (char*)"Load array element");
				}
				if (op == ADD || op == SUB || op == DIV || op == MUL || op == MOD)
				{
					genCode(tree->child[0], symbolTable);
					//if (tree->child[0]->child[0] != NULL) emitComment((char*)"Is array");
					emitRM((char*)"ST", 3, toff, 1, (char*)"Push left side");
					TOFF(dec);
					printExpression = false;
					genCode(tree->child[1], symbolTable);
					printExpression = true;
					TOFF(inc);
					emitRM((char*)"LD", 4, toff, 1, (char*)"Pop left into ac1");
					if (op == ADD)
						emitRO((char*)"ADD", 3, 4, 3, (char*)"Op +");
					else if (op == SUB)
						emitRO((char*)"SUB", 3, 4, 3, (char*)"Op -");
					else if (op == DIV)
						emitRO((char*)"DIV", 3, 4, 3, (char*)"Op /");
					else if (op == MUL)
						emitRO((char*)"MUL", 3, 4, 3, (char*)"Op *");
					else if (op == MOD)
						emitRO((char*)"MOD", 3, 4, 3, (char*)"Op %");
				}
				if (op == CHSIGN || op == QUESTION)
				{
					genCode(tree->child[0], symbolTable);
					if (op == CHSIGN)
						emitRO((char*)"NEG", 3, 3, 3, (char*)"Op unary -");
					else if (op == QUESTION)
						emitRO((char*)"RND", 3, 3, 6, (char*)"Op ?");
				}
				if (op == SIZEOF)
				{
					//if (printExpression)
					//	emitComment((char*)"EXPRESSION");

					loadArrayAddress(tree->child[0], 3, symbolTable);
					//emitRM((char*)"LDA", 3, -1, !tree->child[0]->isGlobal && !tree->child[0]->isStatic, (char*)"Load address of base of array", tree->child[0]->attr.name);
					emitRM((char*)"LD", 3, 1, 3, (char*)"Load array size");
				}
				if (op == NOT)
				{
					genCode(tree->child[0], symbolTable);
					emitRM((char*)"LDC", 4, 1, 6, (char*)"Load 1");
					emitRO((char*)"XOR", 3, 3, 4, (char*)"Op XOR to get logical not");
				}
				if (op == EQ || op == AND || op == OR || op == GREATER || op == LESSER || op == NEQ || op == GEQ || op == LEQ)
				{
					genCode(tree->child[0], symbolTable);
					emitRM((char*)"ST", 3, toff, 1, (char*)"Push left side");
					TOFF(dec);
					printExpression = false;
					genCode(tree->child[1], symbolTable);
					printExpression = true;
					TOFF(inc);
					emitRM((char*)"LD", 4, toff, 1, (char*)"Pop left into ac1");
					if (tree->child[0]->isArray)
					{
						emitRM((char*)"LD", 5, 1, 3, (char*)"AC2 <- |RHS|");
						emitRM((char*)"LD", 6, 1, 4, (char*)"AC3 <- |LHS|");
						emitRM((char*)"LDA", 2, 0, 5, (char*)"R2 <- |RHS|");
						emitRO((char*)"SWP", 5, 6, 6, (char*)"pick smallest size");
						emitRM((char*)"LD", 6, 1, 4, (char*)"AC3 <- |LHS|");
						emitRO((char*)"CO", 4, 3, 5, (char*)"setup array compare  LHS vs RHS");
						emitRO((char*)"TNE", 5, 4, 3, (char*)"if not equal then test (AC1, AC)");
						emitRO((char*)"JNZ", 5, 2, 7, (char*)"jump not equal");
						emitRM((char*)"LDA", 3, 0, 2, (char*)"AC1 <- |RHS|");
						emitRM((char*)"LDA", 4, 0, 6, (char*)"AC <- |LHS|");
					}
					if (op == EQ)
						emitRO((char*)"TEQ", 3, 4, 3, (char*)"Op =");
					else if (op == AND)
						emitRO((char*)"AND", 3, 4, 3, (char*)"Op AND");
					else if (op == OR)
						emitRO((char*)"OR", 3, 4, 3, (char*)"Op OR");
					else if (op == GREATER)
						emitRO((char*)"TGT", 3, 4, 3, (char*)"Op >");
					else if (op == LESSER)
						emitRO((char*)"TLT", 3, 4, 3, (char*)"Op <");
					else if (op == NEQ)
						emitRO((char*)"TNE", 3, 4, 3, (char*)"Op ><");
					else if (op == GREATER)
						emitRO((char*)"TGT", 3, 4, 3, (char*)"Op >");
					else if (op == LESSER)
						emitRO((char*)"TLT", 3, 4, 3, (char*)"Op <");
					else if (op == GEQ)
						emitRO((char*)"TGE", 3, 4, 3, (char*)"Op >=");
					else if (op == LEQ)
						emitRO((char*)"TLE", 3, 4, 3, (char*)"Op <=");
					else if (op == NEQ)
						emitRO((char*)"TNE", 3, 4, 3, (char*)"Op ><");
				}
			}
			if (tree->subkind.exp == IdK)
			{
				if (printExpression)
					emitComment((char*)"EXPRESSION");

				if (tree->isArray)
				{
					loadArrayAddress(tree, 3, symbolTable);//emitRM((char*)"LDA", 3, tree->location, !tree->isGlobal && !tree->isStatic, (char*)"Load address of base of array", tree->attr.name);

					
				}
				else
				{
					emitRM((char*)"LD", 3, tree->location, !tree->isGlobal && !tree->isStatic, (char*)"Load variable", tree->attr.name);
				}
			}
			if (tree->subkind.exp == AssignK)
			{
				if (tree->attr.op == ASGN || tree->attr.op == ADDASS || tree->attr.op == SUBASS || tree->attr.op == DIVASS || tree->attr.op == MULASS)
				{
					if (tree->child[0]->child[0] == NULL)
					{
						if (!tree->child[1]->isArray)
						{
							genCode(tree->child[1], symbolTable);
						}
						else
						{
							//if (tree->expType == Char)
							{
								emitComment((char*)"EXPRESSION");
								loadArrayAddress(tree->child[1], 3, symbolTable);
								emitRM((char*)"LDA", 4, tree->child[0]->location, 1, (char*)"address of lhs");
								emitRM((char*)"LD", 5, 1, 3, (char*)"size of rhs");
								emitRM((char*)"LD", 6, 1, 4, (char*)"size of lhs");
								emitRO((char*)"SWP", 5, 6, 6, (char*)"pick smallest size");
								emitRO((char*)"MOV", 4, 3, 5, (char*)"array op =");
							}
						}

						if (tree->attr.op != ASGN)
						{
							int op = tree->attr.op;

							emitRM((char*)"LD", 4, tree->child[0]->location, !tree->child[0]->isGlobal && !tree->child[0]->isStatic, (char*)"load lhs variable", tree->child[0]->attr.name);
							if (op == ADDASS)
								emitRO((char*)"ADD", 3, 4, 3, (char*)"op +=");
							else if (op == SUBASS)
								emitRO((char*)"SUB", 3, 4, 3, (char*)"op -=");
							else if (op == DIVASS)
								emitRO((char*)"DIV", 3, 4, 3, (char*)"op /=");
							else if (op == MULASS)
								emitRO((char*)"MUL", 3, 4, 3, (char*)"op *=");
						}

						if(!tree->child[0]->isArray)
							emitRM((char*)"ST", 3, tree->child[0]->location, !tree->child[0]->isGlobal && !tree->child[0]->isStatic, (char*)"Store variable", tree->child[0]->attr.name);
					}
					//Array
					else
					{
						genCode(tree->child[0]->child[1], symbolTable);
						emitRM((char*)"ST", 3, toff, 1, (char*)"Push index"); //DO MATH HERE TO FIND INDEX

						printExpression = false;

						TOFF(dec);

						if (!tree->child[1]->isArray)
						{
							genCode(tree->child[1], symbolTable);
						}
						else
						{
							//if (tree->expType == Char)
							{
								emitComment((char*)"EXPRESSION");
								loadArrayAddress(tree->child[1], 3, symbolTable);
								emitRM((char*)"LDA", 4, tree->child[0]->location, 1, (char*)"address of lhs");
								emitRM((char*)"LD", 5, 1, 3, (char*)"size of rhs");
								emitRM((char*)"LD", 6, 1, 4, (char*)"size of lhs");
								emitRO((char*)"SWP", 5, 6, 6, (char*)"pick smallest size");
								emitRO((char*)"MOV", 4, 3, 5, (char*)"array op =");
							}
						}

						TOFF(inc);

						emitRM((char*)"LD", 4, toff, 1, (char*)"Pop index"); //DO MATH HERE TO FIND INDEX
						loadArrayAddress(tree->child[0]->child[0], 5, symbolTable);
						//emitRM((char*)"LDA", 5, tree->child[0]->child[0]->location, !tree->child[0]->child[0]->isGlobal && !tree->child[0]->child[0]->isStatic, (char*)"Load address of base of array", tree->child[0]->child[0]->attr.name);//genCode(tree->child[0], symbolTable);
						emitRO((char*)"SUB", 5, 5, 4, (char*)"Compute offset of value");

						if (tree->attr.op != ASGN)
						{
							int op = tree->attr.op;

							emitRM((char*)"LD", 4, 0/*tree->child[0]->child[0]->location*/, 5/*!tree->child[0]->child[0]->isGlobal && !tree->child[0]->isStatic*/, (char*)"load lhs variable", tree->child[0]->child[0]->attr.name);
							if (op == ADDASS)
								emitRO((char*)"ADD", 3, 4, 3, (char*)"op +=");
							else if (op == SUBASS)
								emitRO((char*)"SUB", 3, 4, 3, (char*)"op -=");
							else if (op == DIVASS)
								emitRO((char*)"DIV", 3, 4, 3, (char*)"op /=");
							else if (op == MULASS)
								emitRO((char*)"MUL", 3, 4, 3, (char*)"op *=");
						}

						emitRM((char*)"ST", 3, 0/*tree->child[0]->child[0]->location*/, 5/*!tree->child[0]->child[0]->isGlobal*/, (char*)"Store variable", tree->child[0]->child[0]->attr.name);


						printExpression = true;
					}
				}
				else if (tree->attr.op == INC || tree->attr.op == DEC)
				{
					//Not array
					if (tree->child[0]->child[0] == NULL)
					{
						if (printExpression)
							emitComment((char*)"EXPRESSION");

						emitRM((char*)"LD", 3, tree->child[0]->location, !tree->child[0]->isGlobal && !tree->child[0]->isStatic, (char*)"load lhs variable", tree->child[0]->attr.name);
						if (tree->attr.op == INC)
							emitRM((char*)"LDA", 3, 1, 3, (char*)"increment value of", tree->child[0]->attr.name);
						if (tree->attr.op == DEC)
							emitRM((char*)"LDA", 3, -1, 3, (char*)"decrement value of", tree->child[0]->attr.name);
						emitRM((char*)"ST", 3, tree->child[0]->location, !tree->child[0]->isGlobal && !tree->child[0]->isStatic, (char*)"Store variable", tree->child[0]->attr.name);
					}
					else
					{
						genCode(tree->child[0]->child[1], symbolTable);

						loadArrayAddress(tree->child[0]->child[0], 5, symbolTable);
						//if (!inParameter)
						//	emitRM((char*)"LDA", 5, tree->child[0]->child[0]->location, !tree->child[0]->child[0]->isGlobal && !tree->child[0]->child[0]->isStatic, (char*)"Load address of base of array", tree->child[0]->child[0]->attr.name);
						//else
						//	emitRM((char*)"LD", 5, tree->child[0]->child[0]->location, !tree->child[0]->child[0]->isGlobal && !tree->child[0]->child[0]->isStatic, (char*)"Load address of base of array", tree->child[0]->child[0]->attr.name);
						emitRO((char*)"SUB", 5, 5, 3, (char*)"Compute offset of value");

						emitRM((char*)"LD", 3, 0/*tree->child[0]->child[0]->location*/, 5, (char*)"load lhs variable", tree->child[0]->child[0]->attr.name);
						if (tree->attr.op == INC)
							emitRM((char*)"LDA", 3, 1, 3, (char*)"increment value of", tree->child[0]->child[0]->attr.name);
						if (tree->attr.op == DEC)
							emitRM((char*)"LDA", 3, -1, 3, (char*)"decrement value of", tree->child[0]->child[0]->attr.name);
						emitRM((char*)"ST", 3, tree->child[0]->location, 5, (char*)"Store variable", tree->child[0]->child[0]->attr.name);
					}
				}

			}
			if (tree->subkind.exp == ConstantK)
			{
				if (printExpression)
					emitComment((char*)"EXPRESSION");

				switch(tree->expType)
				{
					case Integer:
						emitRM((char*)"LDC", 3, tree->attr.value, 6, (char*)"Load integer constant");
						break;
					case Boolean:
						emitRM((char*)"LDC", 3, tree->attr.value, 6, (char*)"Load Boolean constant");
						break;
					case Char:
						if (!tree->isArray)
						{
							emitRM((char*)"LDC", 3, (int)tree->attr.cvalue, 6, (char*)"Load char constant");
						}
						else
						{
							emitStrLit(tree->location, tree->attr.string);
							emitRM((char*)"LDA", 3, tree->location, 0, (char*)"Load address of char array");
							/*emitRM((char*)"LD", 5, 1, 3, (char*)"size of rhs");
							emitRM((char*)"LD", 6, 1, 4, (char*)"size of lhs");
							emitRO((char*)"SWP", 5, 6, 6, (char*)"pick smallest size");
							emitRO((char*)"MOV", 4, 3, 5, (char*)"array op =");*/
						}
						break;
				}
			}
			if (tree->subkind.exp == CallK)
			{
				if (printExpression)
					emitComment((char*)"EXPRESSION");

				emitComment((char*)"CALL", tree->attr.name);
				emitRM((char*)"ST", 1, toff, 1, (char*)"Store fp in ghost frame for", tree->attr.name);
				
				int tempTOFF = toff;
				TOFF(dec);

				if (tree->child[0] != NULL)
				{
					int paramNum = 1;
					TreeNode* temp = tree->child[0];

					inParameter = true;
					while (temp != NULL)
					{
						TOFF(dec);
						emitComment((char*)"Param", paramNum++);
						printExpression = false;
						temp->skip = true;
						genCode(temp, symbolTable);
						temp->skip = false;
						printExpression = true;
						emitRM((char*)"ST", 3, toff, 1, (char*)"Push parameter");
						temp = temp->sibling;
					}
					inParameter = false;
				}
				TOFF(dec);
				emitComment((char*)"Param end", tree->attr.name);

				emitRM((char*)"LDA", 1, tempTOFF, 1, (char*)"Ghost frame becomes new active frame");
				emitRM((char*)"LDA", 3, 1, 7, (char*)"Return address in ac");
				string str(tree->attr.name);
				TreeNode* temp = (TreeNode*)symbolTable->lookup(str);
				if (temp != NULL)
					emitRM((char*)"JMP", 7, temp->addr - emitSkip(0) - 1, 7, (char*)"CALL", tree->attr.name);
				emitRM((char*)"LDA", 3, 0, 2, (char*)"Save the result in ac");

				emitComment((char*)"Call end", tree->attr.name);
				TOFF(set, tempTOFF);
			}
		}
		if (tree->nodekind == StmtK)
		{
			if (tree->subkind.stmt == ReturnK)
			{
				emitComment((char*)"RETURN");
				if (tree->child[0] != NULL)
				{
					printExpression = false;
					genCode(tree->child[0], symbolTable);
					emitRM((char*)"LDA", 2, 0, 3, (char*)"Copy result to return register");
					printExpression = true;
				}
				emitRM((char*)"LD", 3, -1, 1, (char*)"Load return address");
				emitRM((char*)"LD", 1, 0, 1, (char*)"Adjust fp");
				emitRM((char*)"JMP", 7, 0, 3, (char*)"Return");
			}
			if (tree->subkind.stmt == CompoundK)
			{
				int oldTOFF = toff;
				emitComment((char*)"COMPOUND");
				TOFF(set, tree->size);
				genCode(tree->child[0], symbolTable);
				emitComment((char*)"Compound Body");
				genCode(tree->child[1], symbolTable);
				TOFF(set, oldTOFF);
				emitComment((char*)"END COMPOUND");
			}
			if (tree->subkind.stmt == IfK)
			{
				//IF ALONE
				if (tree->child[2] == NULL)
				{
					int rememberif;
					emitComment((char*)"IF");
					printExpression = false;
					genCode(tree->child[0], symbolTable);
					printExpression = true;
					rememberif = emitSkip(1);
					emitComment((char*)"THEN");
					genCode(tree->child[1], symbolTable);
					backPatchAJumpToHere((char*)"JZR", 3, rememberif, (char*)"Jump around the THEN if false [backpatch]");
					emitComment((char*)"END IF");
				}
				//IF ELSE
				else
				{
					int l1patch, l2patch;
					emitComment((char*)"IF");
					printExpression = false;
					genCode(tree->child[0], symbolTable);
					printExpression = true;
					l1patch = emitSkip(1);
					emitComment((char*)"THEN");
					genCode(tree->child[1], symbolTable);
					l2patch = emitSkip(1);
					backPatchAJumpToHere((char*)"JZR", 3, l1patch, (char*)"Jump around the THEN if false [backpatch]");
					//emitRM((char*)"JZR", 3, emitSkip(0) - rememberif - 1, 7, (char*)"Jump around the THEN if false[backpatch]");
					emitComment((char*)"ELSE");
					genCode(tree->child[2], symbolTable);
					backPatchAJumpToHere((char*)"JMP", 7, l2patch, (char*)"Jump around the ELSE [backpatch]");
					emitComment((char*)"END IF");
				}
			}
			if (tree->subkind.stmt == WhileK)
			{
				int rememberL1, rememberbp;
				emitComment((char*)"WHILE");
				rememberL1 = emitSkip(0);
				printExpression = false;
				genCode(tree->child[0], symbolTable);
				printExpression = true;
				emitRM((char*)"JNZ", 3, 1, 7, (char*)"Jump to while part");
				rememberbp = emitSkip(1);
				breakoffset.push(rememberbp);
				emitComment((char*)"DO");
				genCode(tree->child[1], symbolTable);
				emitRM((char*)"JMP", 7, rememberL1 - emitSkip(0) - 1, 7, (char*)"go to beginning of loop");
				backPatchAJumpToHere((char*)"JMP", 7, rememberbp, (char*)"Jump past loop [backpatch]");
				breakoffset.pop();
				emitComment((char*)"END WHILE");
			}
			if (tree->subkind.stmt == ForK)
			{
				TOFF(set, tree->size);
				int rememberL1, rememberbp;
				emitComment((char*)"FOR");
				rememberL1 = emitSkip(0);
				printExpression = false;
				genCode(tree->child[0], symbolTable);
				genCode(tree->child[1], symbolTable);
				printExpression = true;
				emitRM((char*)"JNZ", 3, 1, 7, (char*)"Jump to loop body");
				rememberbp = emitSkip(1);
				breakoffset.push(rememberbp);
				//emitComment((char*)"DO");
				genCode(tree->child[2], symbolTable);

				emitComment((char*)"Bottom of loop increment and jump");

				emitRM((char*)"LD", 3, toff + 3, 1, (char*)"Load index");
				emitRM((char*)"LD", 5, toff + 1, 1, (char*)"Load step");
				emitRO((char*)"ADD", 3, 3, 5, (char*)"increment");
				emitRM((char*)"ST", 3, toff + 3, 1, (char*)"store back to index");

				emitRM((char*)"JMP", 7, rememberbp - emitSkip(0) - 6, 7, (char*)"go to beginning of loop");
				backPatchAJumpToHere((char*)"JMP", 7, rememberbp, (char*)"Jump past loop [backpatch]");
				breakoffset.pop();
				emitComment((char*)"END LOOP");
			}
			if (tree->subkind.stmt == RangeK)
			{
				genCode(tree->child[0], symbolTable);
				emitRM((char*)"ST", 3, toff + 3, 1, (char*)"save starting value in index variable");
				printExpression = false;
				genCode(tree->child[1], symbolTable);
				printExpression = true;
				emitRM((char*)"ST", 3, toff + 2, 1, (char*)"save stop value");
				if (tree->child[2] != NULL)
				{
					printExpression = false;
					genCode(tree->child[2], symbolTable);
					emitRM((char*)"ST", 3, toff + 1, 1, (char*)"save step value");
					printExpression = true;
				}
				else
				{
					emitRM((char*)"LDC", 3, 1, 6, (char*)"default increment by 1");
					emitRM((char*)"ST", 3, toff + 1, 1, (char*)"save step value");
				}
				emitRM((char*)"LD", 4, toff + 3, 1, (char*)"loop index");
				emitRM((char*)"LD", 5, toff + 2, 1, (char*)"stop value");
				emitRM((char*)"LD", 3, toff + 1, 1, (char*)"step value");
				emitRO((char*)"SLT", 3, 4, 5, (char*)"Op <");
			}
			if (tree->subkind.stmt == BreakK)
			{
				emitComment((char*)"BREAK");
				emitRM((char*)"JMP", 7, breakoffset.top() - emitSkip(0) - 1, 7, (char*)"break");
			}
		}

		if (tree->skip) break;

		tree = tree->sibling;
	}
}

void commentFunction(char *name)
{
	emitComment((char*)"** ** ** ** ** ** ** ** ** ** ** **");
	emitComment((char*)"FUNCTION", name);
}

void endFunction(char* name)
{
	emitComment((char*)"END FUNCTION", name);
}

//In charge of generating code for I/O
//	input, inputc, inputb, output, outputb, outputc, outnl
void genCodeIO(TreeNode* tree, SymbolTable *symbolTable)
{
	for (int i = 0; i <= 6; i++)
	{
		string str(tree->attr.name);

		TreeNode* temp = (TreeNode*)symbolTable->lookup(str);

		if (temp != NULL)
			temp->addr = emitSkip(0);

		commentFunction(tree->attr.name);

		emitRM((char*)"ST", 3, -1, 1, (char*)"Store return address");
		if (i % 2 != 0) emitRM((char*)"LD", 3, -2, 1, (char*)"Load parameter");
		if (i == 0) emitRO((char*)"IN", 2, 2, 2, (char*)"Grab int input");
		else if (i == 1) emitRO((char*)"OUT", 3, 3, 3, (char*)"Output integer");
		else if (i == 2) emitRO((char*)"INB", 2, 2, 2, (char*)"Grab bool input");
		else if (i == 3) emitRO((char*)"OUTB", 3, 3, 3, (char*)"Output bool");
		else if (i == 4) emitRO((char*)"INC", 2, 2, 2, (char*)"Grab char input");
		else if (i == 5) emitRO((char*)"OUTC", 3, 3, 3, (char*)"Output char");
		else if (i == 6) emitRO((char*)"OUTNL", 3, 3, 3, (char*)"Output a newline");
		emitRM((char*)"LD", 3, -1, 1, (char*)"Load return address");
		emitRM((char*)"LD", 1, 0, 1, (char*)"Adjust fp");
		emitRM((char*)"JMP", 7, 0, 3, (char*)"Return");

		endFunction(tree->attr.name);
		emitComment(NO_COMMENT);

		tree = tree->sibling;
	}
}
