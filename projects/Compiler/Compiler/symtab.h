#ifndef _SYMTAB_H_
#define _SYMTAB_H_
/******************************
 * symbol table
 * one can:
 * get the global scope
 * create a new scope with its parent scope
 * insert into a table
 * search for a element
 * clear all the tables
 * print the tables
 * ****************************/

/************************************
 * the value type, can also see in globals.h     
 * *********************************/
#ifndef _ENUM_VALUETYPE_
#define _ENUM_VALUETYPE_
typedef enum {Void,Integer,Boolean,IntArray,VoidArray,BoolArray} ValueType;
#endif

/*size of a table*/
#define SIZE 211

/* a function may have parameters, store with list */
typedef struct stPara{
    ValueType type;
    struct stPara *next;
}StPara;

/************************
 * the structure for store informations
 * **********************/
typedef struct stNode{
    char* name;
    int addr;
    int gOrP;
    int scope;
    ValueType type;
    int count;
    StPara* para;
    int isFun;
    struct stNode* next;
} StNode;
/*********************************
 * symbol table, a table is also a scope
 * ******************************/
typedef struct stTable{
    StNode* table[SIZE];
    ValueType funType;/*type of the current function,for checking return*/
    struct stTable* parent;
    int scope;/*in which scope, from 0(the global scope)*/
    char funcName[256];
} StTable;
/*********get the global table, as a root**********/
StTable* stGetGlobal();
/*********clear the tables*************/
void stClear();
/**************************
 * when the program enter a new scope,
 * create a new table
 * **********************/
StTable* stNewScope(StTable* table);
/*************************
 * insert into a table
 * ***********************/
StNode* stInsert(StTable* table, char *name,ValueType type,int loc,int isFun);
/***********
 * look up a with name
 * may search up until the global scope
 * ***************/
StNode* stLookup(StTable* table, char* name);
/**print the table*************/
void printSymtab();

#endif
