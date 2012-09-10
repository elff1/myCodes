#ifndef _GLOBALS_H_
#define _GLOBALS_H_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"symtab.h"
/********************************************
 *              for scanner
 * ******************************************/
struct treeNode;
extern struct treeNode* root;
extern int Error;
extern int lineno;
/*******************************************
 *              for parser
 *******************************************/
typedef enum {DeclK, ParaK, StmtK, ExprK, VarK, AddexprK,TermK,FactK,CallK,ArgsK } NodeKind;

typedef enum {SimVarDcl,ArrVarDcl,FunDcl} DeclType;
typedef enum {ArrayVar,SimpVar}VarType;
typedef enum {ComStmt,ExprStmt,SeleStmt,IterStmt,ReturnStmt} StmtType;
typedef enum {AssignExp,SimpExp} ExprType;
typedef enum {Multiple,Single}TermType;
typedef enum {Expr,Var,Call,Num}FactorType;
typedef enum {Simple,Array}ParaType;

#ifndef _ENUM_VALUETYPE_
#define _ENUM_VALUETYPE_
typedef enum {Void,Integer,Boolean,IntArray,VoidArray,BoolArray} ValueType;
#endif

#define MAXCHILDREN 4
/*******************
 * structure of the syntax tree node
 * **************/
typedef struct treeNode{
    struct treeNode* child[MAXCHILDREN];
    struct treeNode* sibling;
    int lineno;
    NodeKind kind;
    union{
        DeclType declType;
        VarType varType;
        StmtType stmtType;
        ExprType exprType;
        TermType termType;
        FactorType factorType;
        ParaType paraType;
    } subkind;

    union{
        int val;
        char* name;
    }attr;/***attribute**/
    int indexOrOperator;/***the index of the array or operator of a expression***/
    ValueType type;/***the type of this node, for expression***/
    StTable* handle;/***the scope of the node in the symbol table***/
}TreeNode;

#endif
