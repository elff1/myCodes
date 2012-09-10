#include"symtab.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SHIFT 4
StTable global;
typedef struct stList{
    StTable* p;
    struct stList* next;
}StList;
StList* listHead=NULL;
int hash(char* key)
{
    int tmp=0;
    int i=0;
    while(key[i]!='\0'&&i<256){
        tmp=((tmp<<SHIFT)+key[i])%SIZE;
        i++;
    }
    return tmp;
}
static void freeNode(StNode* p)
{
    StPara* para;
    if(p->next!=NULL)
        freeNode(p->next);
    if(p->isFun){
        while(p->para!=NULL){
            para=p->para;
            p->para=p->para->next;
            free(para);
        }
    }
    free(p->name);
    free(p);
}
static void clear(StList* p){
    int i;
    if(p->next!=NULL){
        clear(p->next);
    }
    for(i=0;i<SIZE;i++){
        if(p->p->table[i]!=NULL){
            freeNode(p->p->table[i]);
            p->p->table[i]=NULL;
        }
    }
    free(p->p);
    free(p);
}
void stClear()
{
    int i;
    if(listHead!=NULL){
        clear(listHead->next);
    }
    else{
        listHead->p=&global;
    }
    for(i=0;i<SIZE;i++){
        if(listHead->p->table[i]!=NULL){
            freeNode(listHead->p->table[i]);
            listHead->p->table[i]=NULL;
        }
    }
}
StTable* stGetGlobal()
{
    int i;
    StTable* p=&global;
    if(listHead==NULL){
        for(i=0;i<SIZE;i++)
            global.table[i]=NULL;
        global.parent=NULL;
        global.scope=0;
        global.funcName[0]='\0';
        listHead=(StList*)malloc(sizeof(StList));
        listHead->p=&global;
        listHead->next=NULL;
    }
    return p;
}
StTable* stNewScope(StTable* handle){
    StTable* p;
    StList* l;
    int i;
    p=(StTable*)malloc(sizeof(StTable)*(SIZE+1));
    for(i=0;i<SIZE;i++)
        p->table[i]=NULL;
    p->parent=handle;
    p->scope=handle->scope+1;
    l=(StList*)malloc(sizeof(StList));
    l->p=p;
    if(listHead==NULL){
        listHead=l;
    }
    else{
        l->next=listHead->next;
        listHead->next=l;
    }
    return p;
}
StNode* stInsert(StTable* handle, char* name,ValueType type,int loc,int isFun)
{
    StNode* p;
    int val;
    int len;
    if(handle==NULL)
        return ;
    val=hash(name);
    len=strlen(name);
    if(handle->table[val]==NULL){
        handle->table[val]=(StNode*)malloc(sizeof(StNode));
        handle->table[val]->name=(char*)malloc(sizeof(char)*(len+1));
        strcpy(handle->table[val]->name,name);
        handle->table[val]->type=type;
        handle->table[val]->addr=loc;
        handle->table[val]->scope=handle->scope;
        handle->table[val]->count=0;
        handle->table[val]->para=NULL;
        handle->table[val]->isFun=isFun;
        handle->table[val]->next=NULL;
        return handle->table[val];
    }
    p=handle->table[val];
    while(p->next!=NULL){
        if(strcmp(name,p->name)==0)
            return NULL;
        p=p->next;
    }
    if(strcmp(name,p->name)==0)
        return NULL;
    p->next=(StNode*)malloc(sizeof(StNode));
    p->next->name=(char*)malloc(sizeof(char)*(len+1));
    strcpy(p->next->name,name);
    p->next->type=type;
    p->next->addr=loc;
    p->next->scope=handle->scope;
    p->next->count=0;
    p->next->para=NULL;
    p->next->isFun=isFun;
    p->next->next=NULL;
    return p->next;
}
StNode* stLookup(StTable* handle,char* name)
{
    int val;
    StTable* h;
    StNode* p;
    val=hash(name);
    h=handle;
    while(h!=NULL){
        p=h->table[val];
        while(p!=NULL){
            if(strcmp(p->name,name)==0){
                return p;
            }
            p=p->next;
        }
        h=h->parent;
    }
    return NULL;
}

void printSymtab()
{
    int i;
    StList* l=listHead;
    StNode* p;
    while(l!=NULL){
        for(i=0;i<SIZE;i++){
            p=l->p->table[i];
            while(p!=NULL){
                printf("%s|%d|%d\n",p->name,p->type,p->addr);
                p=p->next;
            }
        }
        printf("===========\n");
        l=l->next;
    }
}
