#ifndef _UTIL_H_
#define _UTIL_H_
/************************
 *some useful function
 *********************** */
#include"globals.h"
/********************************
 * create a new tree node
 * ********************************/
TreeNode* newNode();
/******************************
 *copy a string
 * **********************/
char* copyString(char* p);
/*********************************
 * print message when a type error is checked
 * ****************************/
void typeError(TreeNode* p, char* msg);
/******************************
 * print the syntax tree
 * ************************/
int printTree(TreeNode* t,int level);
/******************
 * free the tree
 * **********************/
int freeTree(TreeNode* t);
#endif
