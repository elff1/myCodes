#ifndef _ANALYZE_H_
#define _ANALYZE_H_
#include"globals.h"
#include"symtab.h"
/*******************
 * functions for semantic analyze
 * *******************/

/**build the symbol table, preoder travel of the tree**/
void buildSymtab(TreeNode* node,StTable* handle,TreeNode* paraOfFun,ValueType funType,char* funcName);
/******************
 * type checking
 * including:
 * assignment expression of the varible
 * condition expression of of if&&while
 * return type of a function
 * the parameter to call a function
 * ********************/
void typeCheck(TreeNode* node);

#endif
