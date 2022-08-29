#include "semantic.h"

int compoundNum = 0;
TreeNode* inFunction = NULL;
int loopNum = 0;

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

int countSiblings(TreeNode* tree)
{
	int count = 0;

	while (tree != NULL)
	{
		count++;
		tree = tree->sibling;
	}

	return count;
}

void isUsed(TreeNode* tree, SymbolTable *symbolTable)
{
	while (tree != NULL)
	{
		if (tree->nodekind == ExpK && tree->subkind.exp == IdK)
		{
			std::stringstream name;
			name.str(tree->attr.name);

			//Looking for var
			TreeNode* returnVar = (TreeNode*)symbolTable->lookup(name.str());

			if (returnVar != NULL && returnVar->nodekind == DeclK && returnVar->subkind.decl == VarK)
			{
				returnVar->isUsed = true;
			}
		}
		if (tree->nodekind == ExpK && tree->subkind.exp == CallK)
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
			isUsed(tree->child[i], symbolTable);
		}

		tree = tree->sibling;
	}
}

void checkVariablesUsed(std::string str, void* ptr)
{
	TreeNode* tree = (TreeNode*)ptr;

	if (tree->nodekind == DeclK && tree->subkind.decl == VarK)
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

void checkParametersUsed(std::string str, void* ptr)
{
	TreeNode* tree = (TreeNode*)ptr;

	if (tree->nodekind == DeclK && tree->subkind.decl == ParamK)
	{
		std::stringstream name;
		name.str(tree->attr.name);

		if (!tree->isUsed)
		{
			std::ostringstream warningText;
			warningText << "The parameter '" << name.str() << "' seems not to be used.";

			warning(warningText.str().c_str(), tree->lineno);
		}
	}
}

void checkFunctionsUsed(std::string str, void* ptr)
{
	TreeNode* tree = (TreeNode*)ptr;

	if (tree->nodekind == DeclK && tree->subkind.decl == FuncK)
	{
		std::stringstream name;
		name.str(tree->attr.name);

		if (!tree->isUsed && name.str() != "main" && name.str() != "output"
			&& name.str() != "outputb" && name.str() != "outputc" && name.str() != "input"
			&& name.str() != "inputb" && name.str() != "inputc" && name.str() != "outnl")
		{
			std::ostringstream warningText;
			warningText << "The function '" << name.str() << "' seems not to be used.";

			warning(warningText.str().c_str(), tree->lineno);
		}
	}
}

void ignoreAll(TreeNode* tree, SymbolTable *symbolTable)
{
	while (tree != NULL)
	{
		if (tree->nodekind == ExpK && tree->subkind.exp == IdK)
		{
			tree->ignore = true;
		}
		if (tree->nodekind == ExpK && tree->subkind.exp == CallK)
		{
			tree->ignore = true;
		}

		int i;
		for (i = 0; i < MAXCHILDREN; i++)
		{
			ignoreAll(tree->child[i], symbolTable);
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

			if (returnVar != NULL && (returnVar->nodekind != DeclK || returnVar->subkind.decl != FuncK))
			{
				temp->expType = returnVar->expType;
				returnVar->isUsed = true;
			}
			else if (returnVar != NULL && returnVar->nodekind == DeclK && returnVar->subkind.decl == FuncK)
			{
				returnVar->isUsed = true;
				//temp->expType = UndeclaredType;
			}
		}
		if (temp->nodekind == ExpK && temp->subkind.exp == CallK)
		{
			std::stringstream name;
			name.str(temp->attr.name);

			//Looking for var
			TreeNode* returnVar = (TreeNode*)symbolTable->lookupGlobal(name.str());

			if (returnVar != NULL)
			{
				temp->expType = returnVar->expType;
				returnVar->isUsed = true;
			}
			else
			{
				TreeNode* returnTempVar = (TreeNode*)symbolTable->lookup(name.str());

				if (returnTempVar != NULL)
				{
					returnTempVar->isUsed = true;
				}
				//temp->expType = UndeclaredType;
			}
		}

		if (temp->nodekind == ExpK && temp->subkind.exp == AssignK)
		{
			if (temp->attr.op == ASGN)
			{
				//if (checkType(temp->child[0], symbolTable) == checkType(temp->child[1], symbolTable))
				temp->expType = checkType(temp->child[0], symbolTable);
			}
			else if (temp->attr.op == INC || temp->attr.op == DEC)
			{
				//if (checkType(temp->child[0], symbolTable) == Integer)
				temp->expType = Integer;

				//if (checkType(temp->child[0], symbolTable) == UndeclaredType)
					//temp->expType = UndeclaredType;
			}
			else
			{
				//if (checkType(temp->child[0], symbolTable) == Integer && checkType(temp->child[1], symbolTable) == Integer)
				temp->expType = Integer;

				//if (checkType(temp->child[0], symbolTable) == UndeclaredType || checkType(temp->child[1], symbolTable) == UndeclaredType)
					//temp->expType = UndeclaredType;
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
					{
						temp->expType = returnVar->expType;
					}
					else
					{
						//temp->expType = UndeclaredType;
					}
				}
			}
			else if (temp->attr.op == LESSER || temp->attr.op == GREATER || temp->attr.op == LEQ || temp->attr.op == GEQ || temp->attr.op == EQ || temp->attr.op == NEQ)
			{
				//if (checkType(temp->child[0], symbolTable) == checkType(temp->child[1], symbolTable))
				{
					temp->expType = Boolean;
				}

				//if (checkType(temp->child[0], symbolTable) == UndeclaredType || checkType(temp->child[1], symbolTable) == UndeclaredType)
					//temp->expType = UndeclaredType;
			}
			else if (temp->attr.op == NOT || temp->attr.op == CHSIGN || temp->attr.op == QUESTION || temp->attr.op == SIZEOF)
			{
				if (temp->attr.op == NOT)// && checkType(temp->child[0], symbolTable) == Boolean)
				{
					temp->expType = Boolean;
				}
				else if (temp->attr.op == CHSIGN)// && checkType(temp->child[0], symbolTable) == Integer)
				{
					temp->expType = Integer;
				}
				else if (temp->attr.op == QUESTION)// && checkType(temp->child[0], symbolTable) == Integer)
				{
					temp->expType = Integer;
				}
				else if (temp->attr.op == SIZEOF)// && isArray(temp->child[0], symbolTable))
				{
					temp->expType = Integer;
				}

				//if (checkType(temp->child[0], symbolTable) == UndeclaredType)
					//temp->expType = UndeclaredType;
			}
			else if (temp->attr.op == ADD || temp->attr.op == SUB || temp->attr.op == MUL || temp->attr.op == DIV || temp->attr.op == MOD)
			{
				//if (checkType(temp->child[0], symbolTable) == Integer && checkType(temp->child[1], symbolTable) == Integer)
				{
					temp->expType = Integer;
				}

				//if (checkType(temp->child[0], symbolTable) == UndeclaredType || checkType(temp->child[1], symbolTable) == UndeclaredType)
					//temp->expType = UndeclaredType;
			}
			else if (temp->attr.op == AND || temp->attr.op == OR)
			{
				//if (checkType(temp->child[0], symbolTable) == Boolean && checkType(temp->child[1], symbolTable) == Boolean)
				{
					temp->expType = Boolean;
				}

				//if (checkType(temp->child[0], symbolTable) == UndeclaredType || checkType(temp->child[1], symbolTable) == UndeclaredType)
					//temp->expType = UndeclaredType;
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

	if (temp->nodekind == ExpK && temp->subkind.exp == AssignK)
	{
		if (temp->attr.op == ASGN)
		{
			checkArray = isArray(temp->child[0], symbolTable);
		}
		else if (temp->attr.op == INC || temp->attr.op == DEC)
		{
			checkArray = isArray(temp->child[0], symbolTable);
		}
		else
		{
			if (isArray(temp->child[0], symbolTable) == isArray(temp->child[1], symbolTable))
				checkArray = isArray(temp->child[0], symbolTable);
		}
	}

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
				checkArray = isArray(temp->child[0], symbolTable);
			}
		}
		else if (temp->attr.op == ADD || temp->attr.op == SUB || temp->attr.op == MUL || temp->attr.op == DIV || temp->attr.op == MOD)
		{
			if (isArray(temp->child[0], symbolTable) == isArray(temp->child[1], symbolTable))
			{
				checkArray = isArray(temp->child[0], symbolTable);
			}
		}
		else if (temp->attr.op == AND || temp->attr.op == OR)
		{
			if (isArray(temp->child[0], symbolTable) == isArray(temp->child[1], symbolTable))
			{
				checkArray = isArray(temp->child[0], symbolTable);
			}
		}*/
	}

	return checkArray;
}

bool isConstant(TreeNode* temp, SymbolTable *symbolTable)
{
	bool constant = false;

	if (temp->nodekind == ExpK && temp->subkind.exp == ConstantK)
	{
		constant = true;
	}

	if (temp->nodekind == ExpK && temp->subkind.exp == OpK)
	{
		if (temp->attr.op == LESSER || temp->attr.op == GREATER || temp->attr.op == LEQ || temp->attr.op == GEQ || temp->attr.op == EQ || temp->attr.op == NEQ)
		{
			constant = (isConstant(temp->child[0], symbolTable) && isConstant(temp->child[1], symbolTable));
		}
		else if (temp->attr.op == NOT || temp->attr.op == CHSIGN || temp->attr.op == SIZEOF)
		{
			constant = isConstant(temp->child[0], symbolTable);
		}
		else if (temp->attr.op == ADD || temp->attr.op == SUB || temp->attr.op == MUL || temp->attr.op == DIV || temp->attr.op == MOD)
		{
			constant = (isConstant(temp->child[0], symbolTable) && isConstant(temp->child[1], symbolTable));
		}
		else if (temp->attr.op == AND || temp->attr.op == OR)
		{
			constant = (isConstant(temp->child[0], symbolTable) && isConstant(temp->child[1], symbolTable));
		}
	}

	return constant;
}

bool hasReturn(TreeNode* temp, SymbolTable* symbolTable)
{
	bool returns = false;

	while (temp != NULL)
	{
		if (temp->nodekind == StmtK && temp->subkind.stmt == ReturnK)
		{
			return true;
		}

		for (int i = 0; i < MAXCHILDREN; i++)
		{
			returns = hasReturn(temp->child[i], symbolTable);

			if (returns)
				return true;
		}

		temp = temp->sibling;
	}

	return returns;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void semanticAnalysis(TreeNode *tree, SymbolTable *symbolTable, int childNum)
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
					loopNum++;

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
						tree->child[0]->isInitialized = true;
					}
				}
				if (tree->subkind.stmt == RangeK)
				{
					int rangeNum = 0;

					TreeNode* temp;

					for (int i = 0; i < 3; i++) //For multiple positions!!
					{
						temp = tree->child[i];

						if (temp != NULL)
						{
							rangeNum++;

							ExpType returnType = checkType(temp, symbolTable);
							bool returnArray = isArray(temp, symbolTable);

							/////////////////////UndeclaredType

							if (returnType != Integer && returnType != UndefinedType) //"ERROR(%d): Expecting %s(type int) in parameter %i of call to '%s' declared on line %d but got %s.\n" 
							{
								std::ostringstream errorText;
								errorText << "Expecting " << returnExpType(Integer) << " in position " << rangeNum << " in range of for statement but got " << returnExpType(returnType) << ".";

								error(errorText.str().c_str(), tree->lineno);
							}
							if (returnArray) //"ERROR(%d): Not expecting array in parameter %i of call to '%s' declared on line %d.\n"
							{
								std::ostringstream errorText;
								errorText << "Cannot use array in position " << rangeNum << " in range of for statement.";

								error(errorText.str().c_str(), tree->lineno);
							}
						}
					}
				}
				if (tree->subkind.stmt == IfK) //"ERROR(%d): Expecting Boolean test condition in %s statement but got %s.\n"
				{
					TreeNode* temp = tree->child[0];

					ExpType returnType = checkType(temp, symbolTable);
					bool checkArray = isArray(temp, symbolTable);

					if (returnType != UndefinedType) /////////////////////UndeclaredType
					{
						if (returnType != Boolean && returnType != UndefinedType)
						{
							std::ostringstream oss;
							oss << "Expecting Boolean test condition in if statement but got " << returnExpType(returnType) << ".";
							std::string str = oss.str();

							error(str.c_str(), tree->lineno);
						}
						if (checkArray)
						{
							std::ostringstream oss;
							oss << "Cannot use array as test condition in if statement.";
							std::string str = oss.str();

							error(str.c_str(), tree->lineno);
						}
					}
				}
				if (tree->subkind.stmt == WhileK) //"ERROR(%d): Expecting Boolean test condition in %s statement but got %s.\n"
				{
					TreeNode* temp = tree->child[0];

					ExpType returnType = checkType(temp, symbolTable);
					bool checkArray = isArray(temp, symbolTable);
					loopNum++;

					if (returnType != UndefinedType) /////////////////////UndeclaredType
					{
						if (returnType != Boolean && returnType != UndefinedType)
						{
							std::ostringstream oss;
							oss << "Expecting Boolean test condition in while statement but got " << returnExpType(returnType) << ".";
							std::string str = oss.str();

							error(str.c_str(), tree->lineno);
						}
						if (checkArray)
						{
							std::ostringstream oss;
							oss << "Cannot use array as test condition in while statement.";
							std::string str = oss.str();

							error(str.c_str(), tree->lineno);
						}
					}
				}
				if (tree->subkind.stmt == BreakK) //"ERROR(%d): Expecting Boolean test condition in %s statement but got %s.\n"
				{
					if (loopNum == 0) /////////////////////UndeclaredType
					{
						std::ostringstream oss;
						oss << "Cannot have a break statement outside of loop.";
						std::string str = oss.str();

						error(str.c_str(), tree->lineno);
					}
				}
				if (tree->subkind.stmt == ReturnK)
				{
					//Has return expression
					if (tree->child[0] != NULL)
					{
						ExpType returnType = checkType(tree->child[0], symbolTable);
						bool checkArray = isArray(tree->child[0], symbolTable);

						std::stringstream name;
						name.str(inFunction->attr.name);

						if (returnType != UndefinedType)
						{
							if (returnType != inFunction->expType && (inFunction->expType != Void || returnType != UndeclaredType))
							{
								std::ostringstream errorText;

								if (inFunction->expType == Void)
								{
									errorText << "Function '" << name.str() << "' at line " << inFunction->lineno << " is expecting no return value, but return has a value.";
									error(errorText.str().c_str(), tree->lineno);
								}
								else
								{
									errorText << "Function '" << name.str() << "' at line " << inFunction->lineno << " is expecting to return " << returnExpType(inFunction->expType) << " but returns " << returnExpType(returnType) << ".";
									error(errorText.str().c_str(), tree->lineno);
								}
							}
							if (checkArray)
							{
								std::string str = "Cannot return an array.";

								error(str.c_str(), tree->lineno);
							}
						}
					}
					else
					{
						std::ostringstream errorText;

						std::stringstream name;
						name.str(inFunction->attr.name);

						if (inFunction->expType != Void)
						{
							errorText << "Function '" << name.str() << "' at line " << inFunction->lineno << " is expecting to return " << returnExpType(inFunction->expType) << " but return has no value.";
							error(errorText.str().c_str(), tree->lineno);
						}
					}
				}
			break;
			case ExpK:
				if (tree->subkind.exp == AssignK)
				{
					std::stringstream name;

					if (tree->attr.op != DEC && tree->attr.op != INC)
					{
						ignoreAll(tree->child[0], symbolTable);
					}

					semanticAnalysis(tree->child[0], symbolTable, 0);
					semanticAnalysis(tree->child[1], symbolTable, 1);

					if (tree->attr.op != DEC && tree->attr.op != INC)
					{
						ExpType leftType = checkType(tree->child[0], symbolTable);
						ExpType rightType = checkType(tree->child[1], symbolTable);

						tree->expType = leftType;

						bool leftArray = isArray(tree->child[0], symbolTable);
						bool rightArray = isArray(tree->child[1], symbolTable);

						if (tree->child[0]->subkind.exp == OpK)
						{
							name.str(tree->child[0]->child[0]->attr.name);
						}
						else
						{
							name.str(tree->child[0]->attr.name);
						}

						TreeNode* returnVar = (TreeNode*)symbolTable->lookup(name.str());

						//if (leftType != UndefinedType && rightType != UndefinedType) /////////////////////UndeclaredType
						{
							if (returnVar != NULL)
							{
								if (tree->attr.op == ASGN)
								{
									if (leftType != rightType && (leftType != UndefinedType && rightType != UndefinedType))
									{
										std::ostringstream oss;
										oss << "'" << returnToken(tree->attr.op) << "' requires operands of the same type but lhs is " << returnExpType(leftType) << " and rhs is " << returnExpType(rightType) << ".";
										std::string str = oss.str();

										error(str.c_str(), tree->lineno);
									}
								}
								else
								{
									if (leftType != Integer && leftType != UndefinedType)
									{
										std::ostringstream oss;
										oss << "'" << returnToken(tree->attr.op) << "' requires operands of type int but lhs is of " << returnExpType(leftType) << ".";
										std::string str = oss.str();

										error(str.c_str(), tree->lineno);
									}
									if (rightType != Integer && rightType != UndefinedType)
									{
										std::ostringstream oss;
										oss << "'" << returnToken(tree->attr.op) << "' requires operands of type int but rhs is of " << returnExpType(rightType) << ".";
										std::string str = oss.str();

										error(str.c_str(), tree->lineno);
									}
								}

								if (leftArray && !rightArray)
								{
									std::ostringstream oss;
									oss << "'" << returnToken(tree->attr.op) << "' requires both operands be arrays or not but lhs is an array and rhs is not an array.";
									std::string str = oss.str();

									error(str.c_str(), tree->lineno);
								}
								else if (!leftArray && rightArray)
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

						checkType(tree, symbolTable);

						TreeNode* returnVar = (TreeNode*)symbolTable->lookup(name.str());

						if (returnVar != NULL)
						{
							ExpType leftType = returnVar->expType;
							ExpType rightType = Integer;

							if (leftType != rightType)
							{
								std::ostringstream oss;
								oss << "Unary '" << returnToken(tree->attr.op) << "' requires an operand of " << returnExpType(rightType) << " but was given " << returnExpType(leftType) << ".";
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
					if (tree->child[0]->subkind.exp == OpK)
					{
						name.str(tree->child[0]->child[0]->attr.name);
					}
					else
					{
						name.str(tree->child[0]->attr.name);
					}

					TreeNode* returnVar = (TreeNode*)symbolTable->lookup(name.str());

					//if (tree->attr.op == ASGN)
					if (returnVar != NULL)
						if (tree->child[1] != NULL)
							returnVar->isInitialized = true;
				}
				else if (tree->subkind.exp == OpK)
				{
					if (tree->attr.op == LESSER || tree->attr.op == GREATER || tree->attr.op == LEQ || tree->attr.op == GEQ || tree->attr.op == EQ || tree->attr.op == NEQ)
					{
						TreeNode* temp = tree->child[0];
						TreeNode* temp1 = tree->child[1];
						
						ExpType leftType = checkType(temp, symbolTable);
						ExpType rightType = checkType(temp1, symbolTable);

						if (leftType == rightType)
						{
							tree->expType = Boolean;
						}

						bool leftArray = isArray(temp, symbolTable);
						bool rightArray = isArray(temp1, symbolTable);

						//if (leftType != UndefinedType && rightType != UndefinedType) /////////////////////UndeclaredType
						{
							if (leftType != rightType && (leftType != UndefinedType && rightType != UndefinedType))
							{
								std::ostringstream oss;
								oss << "'" << returnToken(tree->attr.op) << "' requires operands of the same type but lhs is " << returnExpType(leftType) << " and rhs is " << returnExpType(rightType) << ".";
								std::string str = oss.str();

								error(str.c_str(), tree->lineno);
							}

							if (leftArray && !rightArray)
							{
								std::ostringstream oss;
								oss << "'" << returnToken(tree->attr.op) << "' requires both operands be arrays or not but lhs is an array and rhs is not an array.";
								std::string str = oss.str();

								error(str.c_str(), tree->lineno);
							}
							else if (!leftArray && rightArray)
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

						ExpType leftType;

						if (tree->attr.op == NOT)
						{
							leftType = Boolean;
						}
						else if (tree->attr.op == CHSIGN)
						{
							leftType = Integer;
						}
						else if (tree->attr.op == QUESTION)
						{
							leftType = Integer;
						}
						else if (tree->attr.op == SIZEOF)
						{
							leftType = Integer;
						}
						
						ExpType rightType = checkType(temp, symbolTable);

						bool leftArray = isArray(temp, symbolTable);

						if (tree->attr.op == NOT && rightType == leftType && !leftArray)
						{
							tree->expType = Boolean;
						}
						else if (tree->attr.op == CHSIGN && rightType == leftType && !leftArray)
						{
							tree->expType = Integer;
						}
						else if (tree->attr.op == QUESTION && rightType == leftType && !leftArray)
						{
							tree->expType = Integer;
						}
						else if (tree->attr.op == SIZEOF && rightType)
						{
							tree->expType = Integer;
						}

						if (rightType != UndefinedType) /////////////////////UndeclaredType
						{
							if (leftType != rightType && tree->attr.op != SIZEOF)
							{
								std::ostringstream oss;
								oss << "Unary '" << returnToken(tree->attr.op) << "' requires an operand of " << returnExpType(leftType) << " but was given " << returnExpType(rightType) << ".";
								std::string str = oss.str();

								error(str.c_str(), tree->lineno);
							}
							else if (tree->attr.op == SIZEOF)
							{
								if (!leftArray)
								{
									std::string str = "The operation 'sizeof' only works with arrays.";

									error(str.c_str(), tree->lineno);

									//returnTempVar->ignoreWarn = true;
								}
							}

							if (tree->attr.op == QUESTION || tree->attr.op == NOT || tree->attr.op == CHSIGN)
							{
								if (leftArray)
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

						ExpType leftType = checkType(temp, symbolTable);
						ExpType rightType = checkType(temp1, symbolTable);

						checkType(tree, symbolTable);

						bool leftArray = isArray(temp, symbolTable);
						bool rightArray = isArray(temp1, symbolTable);
						
						//if (leftType != UndefinedType && rightType != UndefinedType) /////////////////////UndeclaredType
						{
							if (leftType != Integer && leftType != UndefinedType)
							{
								std::ostringstream oss;
								oss << "'" << returnToken(tree->attr.op) << "' requires operands of type int but lhs is of " << returnExpType(leftType) << ".";
								std::string str = oss.str();

								error(str.c_str(), tree->lineno);
							}
							if (rightType != Integer && rightType != UndefinedType)
							{
								std::ostringstream oss;
								oss << "'" << returnToken(tree->attr.op) << "' requires operands of type int but rhs is of " << returnExpType(rightType) << ".";
								std::string str = oss.str();

								error(str.c_str(), tree->lineno);
							}

							if (leftArray || rightArray)
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

						ExpType leftType = checkType(temp, symbolTable);
						ExpType rightType = checkType(temp1, symbolTable);

						if (leftType == rightType)
						{
							tree->expType = leftType;
						}

						bool leftArray = isArray(temp, symbolTable);
						bool rightArray = isArray(temp1, symbolTable);

						//if (leftType != UndefinedType && rightType != UndefinedType) /////////////////////UndeclaredType
						{
							if (leftType != Boolean && leftType != UndefinedType)
							{
								std::ostringstream oss;
								oss << "'" << returnToken(tree->attr.op) << "' requires operands of type bool but lhs is of " << returnExpType(leftType) << ".";
								std::string str = oss.str();

								error(str.c_str(), tree->lineno);
							}
							if (rightType != Boolean && rightType != UndefinedType)
							{
								std::ostringstream oss;
								oss << "'" << returnToken(tree->attr.op) << "' requires operands of type bool but rhs is of " << returnExpType(rightType) << ".";
								std::string str = oss.str();

								error(str.c_str(), tree->lineno);
							}

							if (leftArray || rightArray)
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

							if (returnType != UndefinedType) /////////////////////UndeclaredType
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
					else if (!returnVar->isInitialized && !returnVar->isGlobal && !returnVar->ignoreWarn && !tree->ignore)
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

					checkType(tree, symbolTable);

					if (returnGlobalVar == NULL && returnVar == NULL)
					{
						std::ostringstream errorText;
						errorText << "Symbol '" << name.str() << "' is not declared.";

						error(errorText.str().c_str(), tree->lineno);
					}
					else if (returnGlobalVar != NULL && returnGlobalVar->nodekind == DeclK && returnGlobalVar->subkind.decl == FuncK)
					{
						TreeNode* temp = tree->child[0];
						TreeNode* temp1 = returnGlobalVar->child[0];

						if ((temp != NULL || temp1 != NULL) && (countSiblings(temp) > countSiblings(temp1)))
						{
							std::ostringstream errorText;
							errorText << "Too many parameters passed for function '" << name.str() << "' declared on line " << returnGlobalVar->lineno << ".";

							error(errorText.str().c_str(), tree->lineno);
						}
						else if ((temp != NULL || temp1 != NULL) && (countSiblings(temp) < countSiblings(temp1)))
						{
							std::ostringstream errorText;
							errorText << "Too few parameters passed for function '" << name.str() << "' declared on line " << returnGlobalVar->lineno << ".";

							error(errorText.str().c_str(), tree->lineno);
						}
						if ((temp != NULL && temp1 != NULL))
						{
							int paramNum = 0;

							while (temp != NULL && temp1 != NULL) //For multiple parameters!!
							{
								paramNum++;
								
								ExpType leftType = checkType(temp1, symbolTable);
								ExpType rightType = checkType(temp, symbolTable);

								bool leftArray = temp1->isArray;
								bool rightArray = isArray(temp, symbolTable);

								/////////////////////UndeclaredType

								if (leftType != rightType && rightType != UndefinedType) //"ERROR(%d): Expecting %s(type int) in parameter %i of call to '%s' declared on line %d but got %s.\n" 
								{
									std::ostringstream errorText;
									errorText << "Expecting " << returnExpType(leftType) << " in parameter " << paramNum << " of call to '" << name.str() << "' declared on line " << returnGlobalVar->lineno << " but got " << returnExpType(rightType) << ".";

									error(errorText.str().c_str(), tree->lineno);
								}
								if (leftArray && !rightArray) //"ERROR(%d): Expecting array in parameter %i of call to '%s' declared on line %d.\n"
								{
									std::ostringstream errorText;
									errorText << "Expecting array in parameter " << paramNum << " of call to '" << name.str() << "' declared on line " << returnGlobalVar->lineno << ".";

									error(errorText.str().c_str(), tree->lineno);
								}
								if (!leftArray && rightArray) //"ERROR(%d): Not expecting array in parameter %i of call to '%s' declared on line %d.\n"
								{
									std::ostringstream errorText;
									errorText << "Not expecting array in parameter " << paramNum << " of call to '" << name.str() << "' declared on line " << returnGlobalVar->lineno << ".";

									error(errorText.str().c_str(), tree->lineno);
								}

								temp = temp->sibling;
								temp1 = temp1->sibling;
							}
						}
						else
						{
							tree->expType = returnGlobalVar->expType;
						}

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
					ExpType tempType;

					if (tree->child[0] != NULL)
					{
						semanticAnalysis(tree->child[0], symbolTable, 0); //Read right side first
						tempType = checkType(tree->child[0], symbolTable);
					}

					std::stringstream name;
					name.str(tree->attr.name);

					void *var = tree;
					bool test;

					if (compoundNum > 0)
					{
						test = symbolTable->insert(name.str(), var);
					}
					else
					{
						test = symbolTable->insertGlobal(name.str(), var);
						tree->isGlobal = true;
					}

					if(!test)
					{
						TreeNode *returnVar = (TreeNode *)symbolTable->lookup(name.str());

						std::ostringstream errorText;
						errorText << "Symbol '" << name.str() << "' is already declared at line " << returnVar->lineno << ".";

						error(errorText.str().c_str(), tree->lineno);
					}
					//else
					{
						if (tree->child[0] != NULL)
						{
							////////////////////

							ExpType leftType = tree->expType;
							ExpType rightType = tempType;

							bool constant = isConstant(tree->child[0], symbolTable);

							bool leftArray = tree->isArray;
							bool rightArray = isArray(tree->child[0], symbolTable);

							if (!constant)
							{
								std::ostringstream errorText;
								errorText << "Initializer for variable '" << name.str() << "' is not a constant expression.";

								error(errorText.str().c_str(), tree->lineno);
							}

							if (leftType != rightType && rightType != UndefinedType)
							{
								std::ostringstream errorText;
								errorText << "Initializer for variable '" << name.str() << "' of " << returnExpType(leftType) << " is of " << returnExpType(rightType) << ""; //no period?

								error(errorText.str().c_str(), tree->lineno);
							}

							if (leftArray && !rightArray)
							{
								std::ostringstream errorText;
								errorText << "Initializer for variable '" << name.str() << "' requires both operands be arrays or not but variable is an array and rhs is not an array.";

								error(errorText.str().c_str(), tree->lineno);
							}
							else if (!leftArray && rightArray)
							{
								std::ostringstream errorText;
								errorText << "Initializer for variable '" << name.str() << "' requires both operands be arrays or not but variable is not an array and rhs is an array.";

								error(errorText.str().c_str(), tree->lineno);
							}

							////////////////////

							tree->isInitialized = true;
						}

						TreeNode* returnVar = (TreeNode*)symbolTable->lookup(name.str());

						if (returnVar->isStatic)
						{
							returnVar->ignoreWarn = true;
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

							tree->ignore = true;
						}
					}

					inFunction = tree;

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
						tree->isInitialized = true;

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
			if ((tree->nodekind == DeclK && tree->subkind.decl == VarK) || (tree->nodekind == ExpK && tree->subkind.exp == AssignK))
				{}
			else
				semanticAnalysis(tree->child[i], symbolTable, i);
		}
		
		if (tree->nodekind == ExpK)
		{
			
			if (tree->subkind.exp == OpK)
			{
				if (tree->attr.op == LBRACKET)
				{
					if (tree->child[0] != NULL)
					{
						std::stringstream name;
						name.str(tree->child[0]->attr.name);

						ExpType returnType = checkType(tree->child[0], symbolTable);
						bool leftArray = isArray(tree->child[0], symbolTable);

						TreeNode* returnVar = (TreeNode*)symbolTable->lookup(name.str());

						if (returnVar != NULL)
						{
							tree->expType = returnVar->expType;
						}

					//	if (returnVar != NULL)
						//if (returnType != UndeclaredType) /////////////////////UndeclaredType
						{
							if (!leftArray)
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
					
					symbolTable->applyToAll(checkVariablesUsed);

					symbolTable->leave();
					compoundNum--;
				}
			}
		}

		if (tree->nodekind == StmtK && (tree->subkind.stmt == ForK || tree->subkind.stmt == WhileK))
		{
			loopNum--;
		}

		if (tree->nodekind == DeclK)
		{
			if (tree->subkind.decl == FuncK)
			{
				if (compoundNum > 0)
				{
					//if (!tree->ignore)
					{
						std::stringstream name;
						name.str(tree->attr.name);

						//					printf("Removing previous scope. \n");
						bool typeReturn;

						if (tree->child[1]->child[1] != NULL)
						{
							typeReturn = hasReturn(tree->child[1]->child[1], symbolTable);
						}
						else
						{
							typeReturn = false;
						}

						if (!typeReturn && tree->expType != Void)
						{
							std::ostringstream warningText;

							warningText << "Expecting to return " << returnExpType(tree->expType) << " but function '" << name.str() << "' has no return statement.";
							warning(warningText.str().c_str(), tree->lineno);
						}
					}

					inFunction = NULL;
					
					symbolTable->applyToAll(checkVariablesUsed);
					symbolTable->applyToAll(checkParametersUsed);

					symbolTable->leave();
					compoundNum--;
				}
			}
		}

		if (compoundNum == 0 && tree->sibling == NULL && childNum == -1)
		{
			symbolTable->applyToAllGlobal(checkVariablesUsed);
			symbolTable->applyToAllGlobal(checkFunctionsUsed);
		}

		tree = tree->sibling; 
	}
}
