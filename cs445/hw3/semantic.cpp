#include "semantic.h"

int compoundNum = 0;

extern int numErrors, numWarnings;

void error(const char *msg, int line)
{
	if (line == 0)
		printf("ERROR(LINKER): %s\n", msg);
	else
		printf("ERROR(%d): %s\n", line, msg);
	numErrors++;
}

void warning(const char* msg, int line)
{
	printf("WARNING(%d): %s\n", line, msg);
	numWarnings++;
}

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

char* returnExpType(ExpType type)
{
	char* expType;
	if (type == Integer)
		expType = strdup("type int");
	else if (type == Boolean)
		expType = strdup("type bool");
	else if (type == Char)
		expType = strdup("type char");
	else if (type == String)
		expType = strdup("type char");
	else if (type == Void)
		expType = strdup("type void");
	else
		expType = strdup("unknown type");

	return expType;
}

void isUsedCheck(TreeNode* tree, SymbolTable *symbolTable)
{
	while (tree != NULL)
	{
		if (tree->nodekind == ExpK && tree->subkind.exp == IdK)
		{
			std::stringstream name;
			name.str(tree->attr.name);

			//Looking for var
			TreeNode* returnVar = (TreeNode*)symbolTable->lookup(name.str());

			if (returnVar != NULL)
			{
				
				returnVar->isUsed = true;
			}
		}

		int i;
		for (i = 0; i < MAXCHILDREN; i++)
		{
			isUsedCheck(tree->child[i], symbolTable);
		}

		tree = tree->sibling;
	}
}

void checkUsed(std::string str, void* ptr)
{
	TreeNode* tree = (TreeNode*)ptr;

	if (tree->nodekind == DeclK && (tree->subkind.decl == VarK || tree->subkind.decl == ParamK))
	{
		std::stringstream name;
		name.str(tree->attr.name);

		if (!tree->isUsed)
		{
			std::ostringstream warningText;
			warningText << "The variable '" << name.str() << "' seems not to be used.";

			warning(warningText.str().c_str(), tree->lineno);
		}
	}
}

void setTypes(TreeNode* tree, SymbolTable *symbolTable)
{
	while (tree != NULL)
	{
		if (tree->nodekind == ExpK && tree->subkind.exp == IdK)
		{
			std::stringstream name;
			name.str(tree->attr.name);

			TreeNode* returnVar = (TreeNode*)symbolTable->lookup(name.str());

			if (returnVar != NULL)
			{
				tree->expType = returnVar->expType;
			}
		}

		for (int i = 0; i < MAXCHILDREN; i++)
		{
			setTypes(tree->child[0], symbolTable);
		}

		tree = tree->sibling;
	}
}


ExpType checkType(TreeNode* temp, SymbolTable* symbolTable)
{
	if (temp->expType == UndefinedType)
	{
		if (temp->nodekind == ExpK && temp->subkind.exp == IdK)
		{
			std::stringstream name;
			name.str(temp->attr.name);

			//Looking for var
			TreeNode* returnVar = (TreeNode*)symbolTable->lookup(name.str());

			if (returnVar != NULL)
			{
				temp->expType = returnVar->expType;
				returnVar->isUsed = true;
			}
			else
			{
				temp->expType = UndeclaredType;
			}
		}
		if (temp->nodekind == ExpK && temp->subkind.exp == CallK)
		{
			std::stringstream name;
			name.str(temp->attr.name);

			//Looking for var
			TreeNode* returnVar = (TreeNode*)symbolTable->lookupGlobal(name.str());

			if (returnVar != NULL)
				temp->expType = returnVar->expType;
		}

		if (temp->nodekind == ExpK && temp->subkind.exp == AssignK)
		{
			if (temp->attr.op == ASGN)
			{
				temp->expType = checkType(temp->child[0], symbolTable);
			}
			else if (temp->attr.op == INC || temp->attr.op == DEC)
			{
				if (checkType(temp->child[0], symbolTable) == Integer)
					temp->expType = Integer;
				
				if (checkType(temp->child[0], symbolTable) == UndeclaredType)
					temp->expType = UndeclaredType;
			}
			else
			{
				if (checkType(temp->child[0], symbolTable) == checkType(temp->child[1], symbolTable))
					temp->expType = checkType(temp->child[0], symbolTable);

				if (checkType(temp->child[0], symbolTable) == UndeclaredType || checkType(temp->child[1], symbolTable) == UndeclaredType)
					temp->expType = UndeclaredType;
			}
		}

		if (temp->nodekind == ExpK && temp->subkind.exp == OpK)
		{
			if (temp->attr.op == LBRACKET)
			{
				if (temp->child[0] != NULL)
				{
					std::stringstream name;
					name.str(temp->child[0]->attr.name);

					//Looking for var
					TreeNode* returnVar = (TreeNode*)symbolTable->lookup(name.str());

					if (returnVar != NULL)
						temp->expType = returnVar->expType;
					else
						temp->expType = UndeclaredType;
				}
			}
			else if (temp->attr.op == LESSER || temp->attr.op == GREATER || temp->attr.op == LEQ || temp->attr.op == GEQ || temp->attr.op == EQ || temp->attr.op == NEQ)
			{
				if (checkType(temp->child[0], symbolTable) == checkType(temp->child[1], symbolTable))
				{
					temp->expType = Boolean;
				}

				if (checkType(temp->child[0], symbolTable) == UndeclaredType || checkType(temp->child[1], symbolTable) == UndeclaredType)
					temp->expType = UndeclaredType;
			}
			else if (temp->attr.op == NOT || temp->attr.op == CHSIGN || temp->attr.op == QUESTION || temp->attr.op == SIZEOF)
			{
				if (temp->attr.op == NOT && checkType(temp->child[0], symbolTable) == Boolean)
				{
					temp->expType = Boolean;
				}
				else if (temp->attr.op == CHSIGN && checkType(temp->child[0], symbolTable) == Integer)
				{
					temp->expType = Integer;
				}
				else if (temp->attr.op == QUESTION && checkType(temp->child[0], symbolTable) == Integer)
				{
					temp->expType = Integer;
				}
				else if (temp->attr.op == SIZEOF && isArray(temp->child[0], symbolTable))
				{
					temp->expType = Integer;
				}

				if (checkType(temp->child[0], symbolTable) == UndeclaredType)
					temp->expType = UndeclaredType;
			}
			else if (temp->attr.op == ADD || temp->attr.op == SUB || temp->attr.op == MUL || temp->attr.op == DIV || temp->attr.op == MOD)
			{
				if (checkType(temp->child[0], symbolTable) == checkType(temp->child[1], symbolTable))
				{
					temp->expType = checkType(temp->child[0], symbolTable);
				}

				if (checkType(temp->child[0], symbolTable) == UndeclaredType || checkType(temp->child[1], symbolTable) == UndeclaredType)
					temp->expType = UndeclaredType;
			}
			else if (temp->attr.op == AND || temp->attr.op == OR)
			{
				if (checkType(temp->child[0], symbolTable) == checkType(temp->child[1], symbolTable))
				{
					temp->expType = Boolean;
				}

				if (checkType(temp->child[0], symbolTable) == UndeclaredType || checkType(temp->child[1], symbolTable) == UndeclaredType)
					temp->expType = UndeclaredType;
			}
		}
	}

	return temp->expType;
}

bool isArray(TreeNode* temp, SymbolTable *symbolTable)
{
	bool checkArray = false;

		if (temp->nodekind == ExpK && temp->subkind.exp == IdK)
		{
			std::stringstream name;
			name.str(temp->attr.name);

			//Looking for var
			TreeNode* returnVar = (TreeNode*)symbolTable->lookup(name.str());

			if (returnVar != NULL)
				checkArray = returnVar->isArray;
		}

		if (temp->nodekind == ExpK && temp->subkind.exp == ConstantK)
		{
			checkArray = temp->isArray;
		}

		/*if (temp->nodekind == ExpK && temp->subkind.exp == AssignK)
		{
			if (temp->attr.op == ASGN)
			{
				temp->isArray = isArray(temp->child[0], symbolTable);
			}
			else if (temp->attr.op == INC || temp->attr.op == DEC)
			{
				temp->isArray = isArray(temp->child[0], symbolTable);
			}
			else
			{
				if (isArray(temp->child[0], symbolTable) == isArray(temp->child[1], symbolTable))
					temp->isArray = isArray(temp->child[0], symbolTable);
			}
		}*/

		if (temp->nodekind == ExpK && temp->subkind.exp == OpK)
		{
			if (temp->attr.op == LBRACKET)
			{
				checkArray = false;
			}
			/*else if (temp->attr.op == LESSER || temp->attr.op == GREATER || temp->attr.op == LEQ || temp->attr.op == GEQ || temp->attr.op == EQ || temp->attr.op == NEQ)
			{
				if (isArray(temp->child[0], symbolTable) == isArray(temp->child[1], symbolTable))
				{
					temp->isArray = isArray(temp->child[0], symbolTable);
				}
			}
			else if (temp->attr.op == ADD || temp->attr.op == SUB || temp->attr.op == MUL || temp->attr.op == DIV || temp->attr.op == MOD)
			{
				if (isArray(temp->child[0], symbolTable) == isArray(temp->child[1], symbolTable))
				{
					temp->isArray = isArray(temp->child[0], symbolTable);
				}
			}
			else if (temp->attr.op == AND || temp->attr.op == OR)
			{
				if (isArray(temp->child[0], symbolTable) == isArray(temp->child[1], symbolTable))
				{
					temp->isArray = isArray(temp->child[0], symbolTable);
				}
			}*/
		}

	return checkArray;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void semanticAnalysis(TreeNode *tree, SymbolTable *symbolTable)
{
	while (tree != NULL)
	{
		switch (tree->nodekind)
		{
			case StmtK:
				if (tree->subkind.stmt == CompoundK)
				{
					if (!tree->notScope)
					{
						std::ostringstream oss;
						oss << "New Compound #" << compoundNum;
						std::string str = oss.str();
//						printf("Made a new scope \"%s\" \n", str.c_str());
						symbolTable->enter(str);
						compoundNum++;
					}
				}
				if (tree->subkind.stmt == ForK)
				{
					std::ostringstream oss;
					oss << "New Compound #" << compoundNum;
					std::string str = oss.str();
//					printf("Made a new scope \"%s\" \n", str.c_str());
					symbolTable->enter(str);
					compoundNum++;

					//Do something to its compound child
					if (tree->child[2]->nodekind == StmtK)
					{
						if (tree->child[2]->subkind.stmt == CompoundK)
						{
							tree->child[2]->notScope = true;
						}
					}

					//Set the for var as declared and initialized
					if (tree->child[1]->child[0] != NULL)
					{
						tree->child[0]->value = tree->child[1]->child[0];
					}
				}
				if (tree->subkind.stmt == ReturnK)
				{
					//Has return expression
					if (tree->child[0] != NULL)
					{
						bool checkArray = isArray(tree->child[0], symbolTable);

						if (checkArray)
						{
							std::string str = "Cannot return an array.";

							error(str.c_str(), tree->lineno);
						}
					}
				}
			break;
			case ExpK:
				if (tree->subkind.exp == AssignK)
				{
					if (tree->attr.op != DEC && tree->attr.op != INC)
					{
						//Left Hand Side;
						std::stringstream name;
						if (tree->child[0]->subkind.exp == OpK)
						{
							name.str(tree->child[0]->child[0]->attr.name);
							tree->child[0]->child[0]->ignore = true;
						}
						else
						{
							name.str(tree->child[0]->attr.name);
							tree->child[0]->ignore = true;
						}
					}
				/*	bool notArray = false;
					bool notArray1 = false;

					if (tree->attr.op != DEC && tree->attr.op != INC)
					{
						//Left Hand Side;
						std::stringstream name;
						if (tree->child[0]->subkind.exp == OpK)
						{
							name.str(tree->child[0]->child[0]->attr.name);
							tree->child[0]->child[0]->ignore = true;
							notArray = true;
						}
						else
						{
							name.str(tree->child[0]->attr.name);
							tree->child[0]->ignore = true;
						}

						TreeNode* returnVar = (TreeNode*)symbolTable->lookup(name.str());

						if (returnVar != NULL)
						{
							TreeNode* temp = tree->child[1];
							
							ExpType leftHand = returnVar->expType;
							ExpType rightHand = checkType(temp, symbolTable);

							TreeNode* returnTemp = returnVar;
							TreeNode* returnTemp1 = NULL;

							if (temp->nodekind == ExpK && temp->subkind.exp == IdK)
							{
								std::stringstream name;
								name.str(temp->attr.name);

								//Looking for var
								returnTemp1 = (TreeNode*)symbolTable->lookup(name.str());
							}
							else if (temp->nodekind == ExpK && temp->subkind.exp == OpK && temp->attr.op == LBRACKET) /////////////////////NEWWWWW
							{
								std::stringstream name;
								name.str(temp->child[0]->attr.name);

								//Looking for var
								returnTemp1 = (TreeNode*)symbolTable->lookup(name.str());

								notArray1 = true;
							}

							if (tree->attr.op == ASGN)
							{
								if (leftHand != rightHand)
								{
									std::ostringstream oss;
									oss << "'" << returnToken(tree->attr.op) << "' requires operands of the same type but lhs is " << returnExpType(leftHand) << " and rhs is " << returnExpType(rightHand) << ".";
									std::string str = oss.str();

									error(str.c_str(), tree->lineno);
								}
							}
							else
							{
								if (leftHand != rightHand)
								{
									std::ostringstream oss;
									oss << "'" << returnToken(tree->attr.op) << "' requires operands of type int but lhs is of " << returnExpType(leftHand) << ".";
									std::string str = oss.str();

									error(str.c_str(), tree->lineno);
								}
							}
							
							if (returnTemp != NULL && returnTemp1 != NULL)
							{
								if (returnTemp->isArray && !notArray && !returnTemp1->isArray && notArray1)
								{
									std::ostringstream oss;
									oss << "'" << returnToken(tree->attr.op) << "' requires both operands be arrays or not but lhs is an array and rhs is not an array.";
									std::string str = oss.str();

									error(str.c_str(), tree->lineno);
								}
								else if (!returnTemp->isArray && notArray && returnTemp1->isArray && !notArray1)
								{
									std::ostringstream oss;
									oss << "'" << returnToken(tree->attr.op) << "' requires both operands be arrays or not but lhs is not an array and rhs is an array.";
									std::string str = oss.str();

									error(str.c_str(), tree->lineno);
								}
							}
							else if (returnTemp != NULL && returnTemp->isArray && !notArray && rightHand != String)
							{
								std::ostringstream oss;
								oss << "'" << returnToken(tree->attr.op) << "' requires both operands be arrays or not but lhs is an array and rhs is not an array.";
								std::string str = oss.str();

								error(str.c_str(), tree->lineno);
							}
						}
					}
					else
					{
						bool notArray = false;

						std::stringstream name;
						if (tree->child[0]->subkind.exp == OpK)
						{
							name.str(tree->child[0]->child[0]->attr.name);
							notArray = true;
						}
						else
						{
							name.str(tree->child[0]->attr.name);
						}

						TreeNode* returnVar = (TreeNode*)symbolTable->lookup(name.str());

						if (returnVar != NULL)
						{
							ExpType leftHand = returnVar->expType;
							ExpType rightHand = Integer;

							if (leftHand != rightHand)
							{
								std::ostringstream oss;
								oss << "Unary '" << returnToken(tree->attr.op) << "' requires an operand of " << returnExpType(rightHand) << " but was given " << returnExpType(leftHand) << ".";
								std::string str = oss.str();

								error(str.c_str(), tree->lineno);
							}

							if (returnVar->isArray && !notArray)
							{
								std::ostringstream oss;
								oss << "The operation '" << returnToken(tree->attr.op) << "' does not work with arrays.";
								std::string str = oss.str();

								error(str.c_str(), tree->lineno);
							}
						}
					}*/
				}
				else if (tree->subkind.exp == OpK)
				{
					if (tree->attr.op == LESSER || tree->attr.op == GREATER || tree->attr.op == LEQ || tree->attr.op == GEQ || tree->attr.op == EQ || tree->attr.op == NEQ)
					{
						TreeNode* temp = tree->child[0];
						TreeNode* temp1 = tree->child[1];
						
						ExpType leftHand = checkType(temp, symbolTable);
						ExpType rightHand = checkType(temp1, symbolTable);

						if (leftHand == rightHand)
						{ 
							tree->expType = Boolean;
						}

						bool arrayCheck = isArray(temp, symbolTable);
						bool arrayCheck1 = isArray(temp1, symbolTable);

						if (leftHand != UndeclaredType && rightHand != UndeclaredType) /////////////////////UndeclaredType
						{
							if (leftHand != rightHand)
							{
								std::ostringstream oss;
								oss << "'" << returnToken(tree->attr.op) << "' requires operands of the same type but lhs is " << returnExpType(leftHand) << " and rhs is " << returnExpType(rightHand) << ".";
								std::string str = oss.str();

								error(str.c_str(), tree->lineno);
							}

							if (arrayCheck && !arrayCheck1)
							{
								std::ostringstream oss;
								oss << "'" << returnToken(tree->attr.op) << "' requires both operands be arrays or not but lhs is an array and rhs is not an array.";
								std::string str = oss.str();

								error(str.c_str(), tree->lineno);
							}
							else if (!arrayCheck && arrayCheck1)
							{
								std::ostringstream oss;
								oss << "'" << returnToken(tree->attr.op) << "' requires both operands be arrays or not but lhs is not an array and rhs is an array.";
								std::string str = oss.str();

								error(str.c_str(), tree->lineno);
							}
						}
					}
					if (tree->attr.op == NOT || tree->attr.op == CHSIGN || tree->attr.op == QUESTION || tree->attr.op == SIZEOF)
					{
						TreeNode* temp = tree->child[0];

						ExpType leftHand;

						if (tree->attr.op == NOT)
						{
							leftHand = Boolean;
						}
						else if (tree->attr.op == CHSIGN)
						{
							leftHand = Integer;
						}
						else if (tree->attr.op == QUESTION)
						{
							leftHand = Integer;
						}
						else if (tree->attr.op == SIZEOF)
						{
							leftHand = Integer;
						}
						
						ExpType rightHand = checkType(temp, symbolTable);

						bool arrayCheck = isArray(temp, symbolTable);

						if (tree->attr.op == NOT && rightHand == leftHand && !arrayCheck)
						{
							tree->expType = Boolean;
						}
						else if (tree->attr.op == CHSIGN && rightHand == leftHand && !arrayCheck)
						{
							tree->expType = Integer;
						}
						else if (tree->attr.op == QUESTION && rightHand == leftHand && !arrayCheck)
						{
							tree->expType = Integer;
						}
						else if (tree->attr.op == SIZEOF && rightHand)
						{
							tree->expType = Integer;
						}

						if (leftHand != UndeclaredType && rightHand != UndeclaredType) /////////////////////UndeclaredType
						{
							if (leftHand != rightHand && tree->attr.op != SIZEOF)
							{
								std::ostringstream oss;
								oss << "Unary '" << returnToken(tree->attr.op) << "' requires an operand of " << returnExpType(leftHand) << " but was given " << returnExpType(rightHand) << ".";
								std::string str = oss.str();

								error(str.c_str(), tree->lineno);
							}
							else if (tree->attr.op == SIZEOF)
							{
								if (!arrayCheck)
								{
									std::string str = "The operation 'sizeof' only works with arrays.";

									error(str.c_str(), tree->lineno);

									//returnTempVar->ignoreWarn = true;
								}
							}

							if (tree->attr.op == QUESTION || tree->attr.op == NOT || tree->attr.op == CHSIGN)
							{
								if (arrayCheck)
								{
									std::ostringstream oss;
									oss << "The operation '" << returnToken(tree->attr.op) << "' does not work with arrays.";
									std::string str = oss.str();

									error(str.c_str(), tree->lineno);
								}
							}
						}
					}
					else if (tree->attr.op == ADD || tree->attr.op == SUB || tree->attr.op == MUL || tree->attr.op == DIV || tree->attr.op == MOD)
					{
						TreeNode* temp = tree->child[0];
						TreeNode* temp1 = tree->child[1];

						ExpType leftHand = checkType(temp, symbolTable);
						ExpType rightHand = checkType(temp1, symbolTable);

						if (leftHand == rightHand)
						{
							tree->expType = leftHand;
						}

						bool arrayCheck = isArray(temp, symbolTable);
						bool arrayCheck1 = isArray(temp1, symbolTable);
						
						if (leftHand != UndeclaredType && rightHand != UndeclaredType) /////////////////////UndeclaredType
						{
							if (leftHand != Integer)
							{
								std::ostringstream oss;
								oss << "'" << returnToken(tree->attr.op) << "' requires operands of type int but lhs is of " << returnExpType(leftHand) << ".";
								std::string str = oss.str();

								error(str.c_str(), tree->lineno);
							}
							if (rightHand != Integer)
							{
								std::ostringstream oss;
								oss << "'" << returnToken(tree->attr.op) << "' requires operands of type int but rhs is of " << returnExpType(rightHand) << ".";
								std::string str = oss.str();

								error(str.c_str(), tree->lineno);
							}

							if (arrayCheck || arrayCheck1)
							{
								std::ostringstream oss;
								oss << "The operation '" << returnToken(tree->attr.op) << "' does not work with arrays.";
								std::string str = oss.str();

								error(str.c_str(), tree->lineno);
							}
						}
					}
					else if (tree->attr.op == AND || tree->attr.op == OR)
					{
						TreeNode* temp = tree->child[0];
						TreeNode* temp1 = tree->child[1];

						ExpType leftHand = checkType(temp, symbolTable);
						ExpType rightHand = checkType(temp1, symbolTable);

						if (leftHand == rightHand)
						{
							tree->expType = leftHand;
						}

						bool checkArray = isArray(temp, symbolTable);
						bool checkArray1 = isArray(temp1, symbolTable);

						if (leftHand != UndeclaredType && rightHand != UndeclaredType) /////////////////////UndeclaredType
						{
							if (leftHand != Boolean)
							{
								std::ostringstream oss;
								oss << "'" << returnToken(tree->attr.op) << "' requires operands of type bool but lhs is of " << returnExpType(leftHand) << ".";
								std::string str = oss.str();

								error(str.c_str(), tree->lineno);
							}
							if (rightHand != Boolean)
							{
								std::ostringstream oss;
								oss << "'" << returnToken(tree->attr.op) << "' requires operands of type bool but rhs is of " << returnExpType(rightHand) << ".";
								std::string str = oss.str();

								error(str.c_str(), tree->lineno);
							}

							if (checkArray || checkArray1)
							{
								std::ostringstream oss;
								oss << "The operation '" << returnToken(tree->attr.op) << "' does not work with arrays.";
								std::string str = oss.str();

								error(str.c_str(), tree->lineno);
							}
						}
					}
					else if (tree->attr.op == LBRACKET)
					{
						if (tree->child[0] != NULL && tree->child[1] != NULL)
						{
							TreeNode* temp = tree->child[0];
							TreeNode* temp1 = tree->child[1];

							ExpType returnType = checkType(temp1, symbolTable);

							tree->expType = temp->expType;

							bool checkArray = isArray(temp1, symbolTable);

							if (returnType != UndeclaredType) /////////////////////UndeclaredType
							{
								if (returnType != Integer)
								{
									std::ostringstream oss;
									oss << "Array '" << tree->child[0]->attr.name << "' should be indexed by type int but got " << returnExpType(returnType) << ".";
									std::string str = oss.str();

									error(str.c_str(), tree->lineno);
								}

								if (checkArray)
								{
									std::ostringstream oss;
									oss << "Array index is the unindexed array '" << tree->child[1]->attr.name << "'.";
									std::string str = oss.str();

									error(str.c_str(), tree->lineno);
								}
							}

							if (temp1->nodekind == ExpK && temp1->subkind.exp == OpK && temp1->attr.op == SIZEOF)
							{
								temp1->child[0]->ignore = true;
							}
							else
							{
								temp1->ignore = true;
							}
						}
					}
				}
				else if (tree->subkind.exp == IdK)
				{
					//Left Hand Side;
					std::stringstream name;
					name.str(tree->attr.name);

					checkType(tree, symbolTable); //isUsed

					TreeNode* returnVar = (TreeNode*)symbolTable->lookup(name.str());

					if (returnVar != NULL)
					{
						//returnVar->isUsed = true;
					}

					if (returnVar == NULL)
					{
						std::ostringstream errorText;
						errorText << "Symbol '" << name.str() << "' is not declared.";

						error(errorText.str().c_str(), tree->lineno);
					}
					else if (returnVar->nodekind == DeclK && returnVar->subkind.decl == FuncK)
					{
						std::ostringstream errorText;
						errorText << "Cannot use function '" << name.str() << "' as a variable.";

						error(errorText.str().c_str(), tree->lineno);
					}
					else if (returnVar->value == NULL && !returnVar->ignoreWarn && !tree->ignore)
					{
						std::ostringstream warningText;
						warningText << "Variable '" << name.str() << "' may be uninitialized when used here.";

						warning(warningText.str().c_str(), tree->lineno);

						returnVar->ignoreWarn = true;
					}
					else
					{
//						printf("Found var %s ", name.str().c_str());
					}
				}
				else if (tree->subkind.exp == CallK)
				{
					//Left Hand Side;
					std::stringstream name;
					name.str(tree->attr.name);

					TreeNode* returnGlobalVar = (TreeNode*)symbolTable->lookupGlobal(name.str());
					TreeNode* returnVar = (TreeNode*)symbolTable->lookup(name.str());

					if (tree->child[0] != NULL)
					{
						isUsedCheck(tree->child[0], symbolTable);
					}

					if (returnGlobalVar == NULL && returnVar == NULL)
					{
						std::ostringstream errorText;
						errorText << "Symbol '" << name.str() << "' is not declared.";

						error(errorText.str().c_str(), tree->lineno);
					}
					else if (returnGlobalVar != NULL && returnGlobalVar->nodekind == DeclK && returnGlobalVar->subkind.decl == FuncK)
					{
						tree->expType = returnGlobalVar->expType;
					}
					else if (returnVar != NULL)
					{
						std::ostringstream errorText;
						errorText << "'" << name.str() << "' is a simple variable and cannot be called.";

						error(errorText.str().c_str(), tree->lineno);
					}
					else
					{
						std::ostringstream errorText;
						errorText << "'" << name.str() << "' is a simple variable and cannot be called.";

						error(errorText.str().c_str(), tree->lineno);
					}
				}
			break;
			case DeclK:
				if (tree->subkind.decl == VarK)
				{
					std::stringstream name;
					name.str(tree->attr.name);

					void *var = tree;

					if (compoundNum > 0)
					{
						if(!symbolTable->insert(name.str(), var))
						{
							TreeNode *returnVar = (TreeNode *)symbolTable->lookup(name.str());

							std::ostringstream errorText;
							errorText << "Symbol '" << name.str() << "' is already declared at line " << returnVar->lineno << ".";

							error(errorText.str().c_str(), tree->lineno);
						}
						else
						{
							if (tree->child[0] != NULL)
							{
								tree->value = tree->child[0];
							}

							TreeNode* returnVar = (TreeNode*)symbolTable->lookup(name.str());

							if (returnVar->isStatic)
							{
								returnVar->ignoreWarn = true;
							}
//							printf("Declared %s as a new variable of %s ", tree->attr.name, expType);
						}
					}
					else
					{
						if(!symbolTable->insertGlobal(name.str(), var))
						{
							TreeNode* returnVar = (TreeNode*)symbolTable->lookup(name.str());

							std::ostringstream errorText;
							errorText << "Symbol '" << name.str() << "' is already declared at line " << returnVar->lineno << ".";

							error(errorText.str().c_str(), tree->lineno);
						}
						else
						{
							if (tree->child[0] != NULL)
							{
								tree->value = tree->child[0];
							}

							TreeNode* returnVar = (TreeNode*)symbolTable->lookup(name.str());

							returnVar->ignoreWarn = true;

//							printf("Declared %s as a new GLOBAL variable of %s ", tree->attr.name, expType);
						}
					}
				}
				if (tree->subkind.decl == FuncK)
				{
					std::stringstream name;
					name.str(tree->attr.name);

					void* var = tree;

					if (!symbolTable->insertGlobal(name.str(), var))
					{
						TreeNode* returnVar = (TreeNode*)symbolTable->lookupGlobal(name.str());

						if (returnVar != NULL)
						{
							std::ostringstream errorText;
							errorText << "Symbol '" << name.str() << "' is already declared at line " << returnVar->lineno << ".";

							error(errorText.str().c_str(), tree->lineno);
						}
					}

					std::ostringstream oss;
					oss << "New Compound #" << compoundNum;
					std::string str = oss.str();
//					printf("Made a new scope \"%s\" ", str.c_str());
					symbolTable->enter(str);

					compoundNum++;

					//Do something to its compound child
					tree->child[1]->notScope = true;
				}
				if (tree->subkind.decl == ParamK)
				{
					std::stringstream name;
					name.str(tree->attr.name);

					void* var = tree;

					if(!symbolTable->insert(name.str(), var))
					{
						TreeNode *returnVar = (TreeNode *)symbolTable->lookup(name.str());

						std::ostringstream errorText;
						errorText << "Symbol '" << name.str() << "' is already declared at line " << returnVar->lineno << ".";

						error(errorText.str().c_str(), tree->lineno);
					}
					else
					{
						TreeNode* returnVar = (TreeNode*)symbolTable->lookup(name.str());

						returnVar->ignoreWarn = true;

						//tree->value = (TreeNode*)malloc(sizeof(TreeNode));
//						printf("Declared %s as a new variable of %s ", tree->attr.name, expType);
					}
				}
			break;
		}
		

		//printf("[line: %d]\n", tree->lineno);

		int i;
		for (i = 0; i < MAXCHILDREN; i++)
		{
			semanticAnalysis(tree->child[i], symbolTable);
		}
		
		if (tree->nodekind == ExpK)
		{
			if (tree->subkind.exp == AssignK)
			{
				bool notArray = false;
				bool notArray1 = false;
				bool stringArray = false;

				if (tree->attr.op != DEC && tree->attr.op != INC)
				{
					/*if (returnVar->expType == Char && returnVar->isArray)
					{
						leftHand = String;
					}
					else
					{
						leftHand = returnVar->expType;
					}*/

					ExpType leftHand = checkType(tree->child[0], symbolTable);
					ExpType rightHand = checkType(tree->child[1], symbolTable);

					tree->expType = leftHand;

					bool arrayCheck = isArray(tree->child[0], symbolTable);
					bool arrayCheck1 = isArray(tree->child[1], symbolTable);

					/*if (returnTemp1 == NULL)
						returnTemp1 = ifID(temp, symbolTable);

					if (returnTemp1 == NULL)
						returnTemp1 = ifArray(temp, symbolTable, &notArray1);

					if (returnTemp1 == NULL)
						returnTemp1 = ifSizeOf(temp, symbolTable, &notArray1);*/

					std::stringstream name;
					if (tree->child[0]->subkind.exp == OpK)
					{
						name.str(tree->child[0]->child[0]->attr.name);
					}
					else
					{
						name.str(tree->child[0]->attr.name);
					}

					TreeNode* returnVar = (TreeNode*)symbolTable->lookup(name.str());

					if (leftHand != UndeclaredType && rightHand != UndeclaredType) /////////////////////UndeclaredType
					{
						if (returnVar != NULL)
						{
							if (tree->attr.op == ASGN)
							{
								if (leftHand != rightHand)
								{
									std::ostringstream oss;
									oss << "'" << returnToken(tree->attr.op) << "' requires operands of the same type but lhs is " << returnExpType(leftHand) << " and rhs is " << returnExpType(rightHand) << ".";
									std::string str = oss.str();

									error(str.c_str(), tree->lineno);
								}
							}
							else
							{
								if (leftHand != rightHand)
								{
									std::ostringstream oss;
									oss << "'" << returnToken(tree->attr.op) << "' requires operands of type int but lhs is of " << returnExpType(leftHand) << ".";
									std::string str = oss.str();

									error(str.c_str(), tree->lineno);
								}
							}

							if (arrayCheck && !arrayCheck1)
							{
								std::ostringstream oss;
								oss << "'" << returnToken(tree->attr.op) << "' requires both operands be arrays or not but lhs is an array and rhs is not an array.";
								std::string str = oss.str();

								error(str.c_str(), tree->lineno);
							}
							else if (!arrayCheck && arrayCheck1)
							{
								std::ostringstream oss;
								oss << "'" << returnToken(tree->attr.op) << "' requires both operands be arrays or not but lhs is not an array and rhs is an array.";
								std::string str = oss.str();

								error(str.c_str(), tree->lineno);
							}
						}
					}
				}
				else
				{
					bool notArray = false;

					std::stringstream name;
					if (tree->child[0]->subkind.exp == OpK)
					{
						name.str(tree->child[0]->child[0]->attr.name);
						notArray = true;
					}
					else
					{
						name.str(tree->child[0]->attr.name);
					}

					TreeNode* returnVar = (TreeNode*)symbolTable->lookup(name.str());

					if (returnVar != NULL)
					{
						isUsedCheck(returnVar, symbolTable);

						ExpType leftHand = returnVar->expType;
						ExpType rightHand = Integer;

						if (leftHand != rightHand)
						{
							std::ostringstream oss;
							oss << "Unary '" << returnToken(tree->attr.op) << "' requires an operand of " << returnExpType(rightHand) << " but was given " << returnExpType(leftHand) << ".";
							std::string str = oss.str();

							error(str.c_str(), tree->lineno);
						}

						if (returnVar->isArray && !notArray)
						{
							std::ostringstream oss;
							oss << "The operation '" << returnToken(tree->attr.op) << "' does not work with arrays.";
							std::string str = oss.str();

							error(str.c_str(), tree->lineno);
						}
					}
				}

				//Left Hand Side;
				std::stringstream name;
				if (tree->child[0]->subkind.exp == OpK)
				{
					name.str(tree->child[0]->child[0]->attr.name);
				}
				else
				{
					name.str(tree->child[0]->attr.name);
				}

				TreeNode* returnVar = (TreeNode*)symbolTable->lookup(name.str());

				if (returnVar != NULL)
					if (tree->child[1] != NULL)
						returnVar->value = tree->child[1];
			}
			if (tree->subkind.exp == OpK)
			{
				if (tree->attr.op == LBRACKET)
				{
					if (tree->child[0] != NULL)
					{
						std::stringstream name;
						name.str(tree->child[0]->attr.name);

						ExpType returnType = checkType(tree->child[0], symbolTable);
						bool arrayCheck = isArray(tree->child[0], symbolTable);

						TreeNode* returnVar = (TreeNode*)symbolTable->lookup(name.str());

						if (returnVar != NULL)
						{
							tree->expType = returnVar->expType;
						}

					//	if (returnVar != NULL)
						//if (returnType != UndeclaredType) /////////////////////UndeclaredType
						{
							if (!arrayCheck)
							{
								std::ostringstream oss;
								oss << "Cannot index nonarray '" << tree->child[0]->attr.name << "'.";
								std::string str = oss.str();

								error(str.c_str(), tree->lineno);
							}
						}

						/*if (returnVar != NULL && returnVar->isArray && !notArray)
						{
							std::ostringstream oss;
							oss << "Array index is the unindexed array '" << tree->child[0]->attr.name << "'.";
							std::string str = oss.str();

							error(str.c_str(), tree->lineno);
						}*/
					}
				}
			}
		}

		//Leave Compound Scope
		if (tree->nodekind == StmtK)
		{
			if ((tree->subkind.stmt == CompoundK && !tree->notScope) || tree->subkind.stmt == ForK)
			{
				if (compoundNum > 0)
				{
//					printf("Removing previous scope. \n");
					
					symbolTable->applyToAll(checkUsed);

					symbolTable->leave();
					compoundNum--;
				}
			}
		}
		if (tree->nodekind == DeclK)
		{
			if (tree->subkind.decl == FuncK)
			{
				if (compoundNum > 0)
				{
//					printf("Removing previous scope. \n");
					
					symbolTable->applyToAll(checkUsed);

					symbolTable->leave();
					compoundNum--;
				}
			}
		}

		tree = tree->sibling; 
	}
}
