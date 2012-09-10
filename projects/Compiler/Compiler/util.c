#include"globals.h"
#include"util.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
TreeNode* newNode()
{
    int i;
    TreeNode* p=(TreeNode*)malloc(sizeof(TreeNode));
    for(i=0;i<MAXCHILDREN;i++)
        p->child[i]=NULL;
    p->sibling=NULL;
    p->lineno=lineno;
    return p;
}

char* copyString(char* p)
{
    int len;
    char* s;
    len=strlen(p)+1;
    s=(char*)malloc(sizeof(char)*len);
    strcpy(s,p);
    return s;
}
void typeError(TreeNode* p,char *msg)
{
    if(p!=NULL&&msg!=NULL)
        printf("Type Error:line:%d:%s\n",p->lineno,msg);
    else if(p!=NULL)
        printf("Type Error:line:%d:\n",p->lineno);
    else if(msg!=NULL)
        printf("Type Error::%s",msg);
    else
        printf("Type Error::\n");
}
int printTree(TreeNode* t,int level)
{
    int i;
    for(i=0;i<level;i++){
        printf("|");
    }
    
    printf("%d ",t->lineno);
    switch(t->kind){
    case DeclK:{
        printf("DeclK %d", t->subkind.declType);
        printf("\n");
        break;
    }
    case ParaK:{
        printf("ParaK %d", t->subkind.paraType);
        printf("\n");
        break;
    }
    case StmtK:{
       printf("StmtK %d", t->subkind.stmtType);
       printf("\n");
       break;
    }
    case ExprK:{
        printf("ExprK %d", t->subkind.exprType);
        printf("\n");    
        break;
    }
    case VarK:{
        printf("VarK %d", t->subkind.varType);
        printf("\n");    
        break;
    }
    case AddexprK:{
        printf("AddexprK");
        printf("\n");
        break;
    }
    case TermK:{
        printf("TermK %d", t->subkind.termType);
        printf("\n");
        break;
    }
    case FactK:{
        printf("FactK %d", t->subkind.factorType);
        printf("\n");
        break;
    }
    case CallK:{
        printf("CallK");
        printf("\n");    
        break;
    }
    case ArgsK:{
        printf("ArgsK");
        printf("\n");    
        break;
    }
    }
    
    for(i=0;i<MAXCHILDREN;i++){
        if(t->child[i]!=NULL)
            printTree(t->child[i],level+1);
    }
    if(t->sibling!=NULL)
        printTree(t->sibling,level);
    return 0;
}
int freeTree(TreeNode* t)
{
    int i;
    for(i=0;i<MAXCHILDREN;i++){
        if(t->child[i]!=NULL)
            freeTree(t->child[i]);
    }
    if(t->sibling!=NULL)
        freeTree(t->sibling);
    free(t);
    return 0;
}
