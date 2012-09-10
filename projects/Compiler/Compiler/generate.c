#include "generate.h"

int offsetLocal;
int offsetParam;
int currentFunc;

int generate(TreeNode *node, int signal) {
	int i;
	int count = 0;
	int label[2];
	int retValue;
	char opStr[3];
	StTable *newHandle;
	StNode *stNode;
	TreeNode *paraNode;

	if (node == NULL)
		return 0;

	switch(node->kind){
    case DeclK:{
		// declaration
		if(node->subkind.declType == FunDcl) {
			// function declaration
			offsetLocal = 0;
			offsetParam = VAR_LENGTH;

			retValue = codeDataSection();
			if (!retValue) {	/* start text section */
				codeStartText();
				
				/* output function */ 
				currentFunc = ELFHash(FUNC_OUTPUT_NAME,
				    strlen(FUNC_OUTPUT_NAME));
				codeStartFunc(currentFunc);
				codeFuncOutput();
				codeEndFunc(currentFunc);
				
				/* input function */ 
				currentFunc = ELFHash(FUNC_INPUT_NAME,
				    strlen(FUNC_INPUT_NAME));
				codeStartFunc(currentFunc);
				codeFuncInput();
				codeEndFunc(currentFunc);
			}
			currentFunc = ELFHash(node->attr.name,
				strlen(node->attr.name));
			codeStartFunc(currentFunc);
			count = generate(node->child[0], 0); // params
			count += generate(node->child[1], 0);
			codeEndFunc(currentFunc);
			generate(node->sibling, 0);
			return 1;
		} else {
			stNode = stLookup(node->handle, node->attr.name);
			if(node->subkind.declType == SimVarDcl) {
				// simple variable declaration
				//printf("scope of %s is %d\n", node->attr.name, node->handle->scope);
				if(node->handle->scope == 0) {
					// global variable
					codeStartBss();
					codeDeclareGlobalVar(ELFHash(node->attr.name, strlen(node->attr.name)), 1);
					stNode->addr = SCALAR;
				}
				else {
					// local variable
					offsetLocal -= VAR_LENGTH;
					codeSubEsp(VAR_LENGTH);
					stNode->addr = offsetLocal;
					stNode->gOrP = GENERAL;
				}
			} else {
				// array variable declaration
				if(node->handle->scope == 0) {
					// global variable
					codeStartBss();
					codeDeclareGlobalVar(ELFHash(node->attr.name, strlen(node->attr.name)), node->indexOrOperator);
					stNode->addr = ARRAY;
				}
				else {
					// local variable
					offsetLocal -= VAR_LENGTH * node->indexOrOperator;
					codeSubEsp(VAR_LENGTH * node->indexOrOperator);
					stNode->addr = offsetLocal;
					stNode->gOrP = GENERAL;
				}
			}
			generate(node->sibling, 0);
			return 0;
		}
        break;
    }
    case ParaK:{
    	// params
		generate(node->sibling, 0);
    	offsetParam += VAR_LENGTH;
		stNode = stLookup(node->handle, node->attr.name);
		if(stNode == NULL)
			printf("NULL; %s\n", node->attr.name);
		else {
			stNode->addr = offsetParam;
			stNode->gOrP = PARAMETER;
		}
		return 0;

        break;
    }
    case StmtK:{
		// statment
		if(node->subkind.stmtType == ComStmt) {
			// compound statement
			count = generate(node->child[0], 0);
			count += generate(node->child[1], 0);
			generate(node->sibling, 0);
			return count;
		} else if(node->subkind.stmtType == ExprStmt) {
			// expression statement
			count = generate(node->child[0], 0);
			generate(node->sibling, 0);
			return count;
		} else if(node->subkind.stmtType == SeleStmt) {
			// selection statement
			label[0] = creatLabel();

			// condition
			generate(node->child[0], 1);
			codePop(1);
			codeTestCondition(1, 0, label[0]);

			// the main procedure
			count = generate(node->child[1], 0);
			if(node->child[2] != NULL) {
				// else label
				label[1] = creatLabel();
				codeJmp(label[1]);
			}
			codeLabel(label[0]);

			// else procedure
			if(node->child[2] != NULL) {
				count += generate(node->child[2], 0);
				codeLabel(label[1]);
			}
			generate(node->sibling, 0);
			return 0;
		} else if(node->subkind.stmtType == IterStmt) {
			// iteration statement
			label[0] = creatLabel();
			label[1] = creatLabel();

			// the main procedure
			codeJmp(label[0]);
			codeLabel(label[1]);
			count = generate(node->child[1], 0);

			// condition
			codeLabel(label[0]);
			count += generate(node->child[0], 1);
			codePop(1);
			codeTestCondition(1, 1, label[1]);
			generate(node->sibling, 0);
			return 0;
		} else if(node->subkind.stmtType == ReturnStmt) {
			// return statement
			count = generate(node->child[0], 1);
			codePop(1);
			codeEndFunc(currentFunc);
			//generate(node->sibling, 0);
			return 0;
		}
       break;
    }
    case ExprK:{
    	// expression
    	if(node->subkind.exprType == AssignExp) {
    		// assign expression
    		count = generate(node->child[1], 1);
    		count += generate(node->child[0], 0);
    		codePop(1);
    		codeOpAssign(2, 1);
    		if(signal) {
    			codePushInd(ELFHash(node->child[0]->attr.name, strlen(node->child[0]->attr.name)));
    		}
    		generate(node->sibling, signal);
    		return 1;
    	} else {
    		// simple expression
    		if(node->child[1] == NULL) {
    			// simple-expression → additive-expression
    			count = generate(node->child[0], signal);
    		} else {
    			// simple-expression → additive-expression relop additive-expression
    			count = generate(node->child[0], 1);
	    		count += generate(node->child[1], 1);
	    		codePop(2);
	    		codePop(1);

	    		switch(node->indexOrOperator) {
	    		case LE:
	    			strcpy(opStr, "<=");
	    			break;
	    		case LT:
	    			strcpy(opStr, "<");
	    			break;
	    		case GE:
	    			strcpy(opStr, ">=");
	    			break;
	    		case GT:
	    			strcpy(opStr, ">");
	    			break;
	    		case EQ:
	    			strcpy(opStr, "==");
	    			break;
	    		case NE:
	    			strcpy(opStr, "!=");
	    			break;
	    		default:
	    			break;
	    		}
	    		retValue = codeOpBinary(1, 2, opStr);
	    		if(signal)
	    			codePushReg(retValue, 0);
	    	}
    		generate(node->sibling, signal);
    		return 1;
    	}
        break;
    }
    case VarK:{
    	// variable declaration
    	if(node->subkind.varType == SimpVar) {
    		// simple variable
    		stNode = stLookup(node->handle, node->attr.name);
			//printf("%d: scope of %s is %d\n", currentFunc, node->attr.name, stNode->scope);
	    	if(stNode->scope == 0) {
	    		// global variable
	    		if(signal) {
	    			// the right operand
	    			if(stNode->addr == SCALAR)
	    				codePushGlobalVar(ELFHash(node->attr.name, strlen(node->attr.name)), 0);
	    			else
	    				codePushGlobalArray(ELFHash(node->attr.name, strlen(node->attr.name)));
	    		} else {
	    			// the left operand
	    			codeLeaGlobal(2, ELFHash(node->attr.name, strlen(node->attr.name)), 0);
	    		}
	    	} else {
	    		// local variable
	    		if(signal) {
	    			// the right operand
	    			codePushInd(stNode->addr);
	    		} else {
	    			// the left operand
	    			codeLeaLocal(2, stNode->addr);
	    		}
	    	}
	    	return 1;
    	} else {
    		// array variable
    		count = generate(node->child[0], 1);

    		// pop the idx into eax
    		codePop(1);

    		// get the array base offset
    		stNode = stLookup(node->handle, node->attr.name);
    		if(stNode != NULL) {
    			if(stNode->scope == 0) {
    				// global
    				retValue = codeGetArrayOffset(0, 1, VAR_LENGTH, 1);
    				if(signal) {
    					// use as right operand
    					codePushMem(ELFHash(node->attr.name, strlen(node->attr.name)), retValue);
    				} else {
    					// use as left oprand
    					// put the addr into ebx
    					codeLeaGlobal(2, ELFHash(node->attr.name, strlen(node->attr.name)), retValue);
    				}
    			} else {
    				// local
    				if(stNode->gOrP == GENERAL) {
    					// outer param
    					retValue = codeGetArrayOffset(stNode->addr, 1, VAR_LENGTH, 0);
    				} else {
    					// inner param
    					retValue = codeGetArrayOffset(stNode->addr, 1, VAR_LENGTH, -1);
    				}
    				if(signal) {
    					// use as left oprand
    					codePushReg(retValue, 1);
    				} else {
    					// use as right oprand
    					codeMoveReg(2, retValue);
    				}
    			}
    			return count;
    		}
    	}
    	
        break;
    }
    case AddexprK:{
    	// addition expression
		count = generate(node->child[0], 1);
		if(node->child[1] != NULL) {
			count += generate(node->child[1], 1);
			codePop(2);
			codePop(1);
	    	if(node->indexOrOperator == PLUS)
	    		strcpy(opStr, "+");
	    	else
	    		strcpy(opStr, "-");
	    	retValue = codeOpBinary(1, 2, opStr);
	    	if(signal)
				codePushReg(retValue, 0);
		}
		return 1;

        break;
    }
    case TermK:{
    	// term
    	if(node->subkind.termType == Single) {
    		// single term
    		count = generate(node->child[0], signal);
    	} else {
    		// multiple terms
    		count = generate(node->child[0], 1);
			count += generate(node->child[1], 1);
			codePop(2);
			codePop(1);
	    	if(node->indexOrOperator == TIMES)
	    		strcpy(opStr, "*");
	    	else
	    		strcpy(opStr, "/");
	    	retValue = codeOpBinary(1, 2, opStr);
	    	if(signal)
				codePushReg(retValue, 0);
    	}
    	return 1;

        break;
    }
    case FactK:{
    	// factor
    	if(node->subkind.factorType == Expr) {
    		// expression term
    		generate(node->child[0], 1);
    	} else if(node->subkind.factorType == Var) {
    		// variable term
    		generate(node->child[0], 1);
    	} else if(node->subkind.factorType == Call) {
    		// call term
    		generate(node->child[0], signal);
    	} else {
    		// number term
    		codePushCons(node->attr.val);
    	}
    	return 1;

        break;
    }
    case CallK:{
    	// call
    	count = generate(node->child[0], 1);

    	codeCallFunc(ELFHash(node->attr.name, strlen(node->attr.name)));
    	codeCleanStack(count * VAR_LENGTH);
    	if(signal)
    		codePushReg(1, 0);
    	return count;

        break;
    }
    default:
    	return 0;
    }
    return 0;
}