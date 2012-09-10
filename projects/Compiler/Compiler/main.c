#include"globals.h"
#include"symtab.h"
#include"analyze.h"
#include"y.tab.h"
#include<stdio.h>
extern FILE* yyin;
int Error=0;;
struct treeNode* root;
int lineno=1;
FILE *fout;
int yyparse();
int main(int argc,char* argv[])
{
    StNode* stPtr;
    char filename[256];
    if(argc!=2){
        printf("Usage:%s <filename>",argv[0]);
    }
    strcpy(filename,argv[1]);
    StTable* gl=stGetGlobal();

    /*****scanning and parsing*****/
    yyin=fopen(filename,"r+");
    yyparse();
    fclose(yyin);
    if(Error==1)
        exit(0);

    /******************************************************
     * print the syntax tree, 
     * remove the comment notation if you want to see it
     * **************************************************/ 
    //printf("++++++++\n");printTree(root,0);printf("+++++++++++++\n");
    
    /****symbol table && type checking*****/
    /*********input output system functions for test************/
    stPtr=stInsert(gl,"input",Integer,0,1);
    if(stPtr==NULL){
        printf("add input to symbol table Error\n");
        Error=1;
    }
    else{
        stPtr->count=0;
    }
    stPtr=stInsert(gl,"output",Integer,0,1);
    if(stPtr==NULL){
        printf("add output to symbol table Error\n");
        Error=1;
    }
    else{
        stPtr->para=(StPara*)malloc(sizeof(StPara));
        stPtr->para->type=Integer;
        stPtr->para->next=NULL;
        stPtr->count=1;
    }

    /********************/
    buildSymtab(root,gl,NULL,Void,NULL);
    if(Error==1){
        exit(0);
    }
    typeCheck(root);
    if(Error==1){
        exit(0);
    }

    /***********************************************
     * print the symbol table,
     * remove the comment notation if you want to see symbol table
     * ***************************************************/
    //printf("++++++++++\n");printSymtab();printf("++++++++\n");

    /****code generation*****/
    fout = fopen("t.asm", "w");
    generate(root, 0);
    fclose(fout);

    stClear();
    freeTree(root);
    return 0;
}
