#include"analyze.h"
#include<string.h>
void buildSymtab(TreeNode* node,StTable* handle,TreeNode* paraOfFun,ValueType funType,char* funcName){
    int i;
    int count=0;
    StTable* newHandle;
    TreeNode* paraNode;
    StNode* stPtr;
    StPara* stParaPtr;
    /***
     * compound statement is a new scope
     * */
    if(node->kind==StmtK && node->subkind.stmtType==ComStmt){
        /*
         * create new scope in the symbol table
         * */
        newHandle=stNewScope(handle);
        newHandle->funType=funType;
        strcpy(newHandle->funcName,funcName);
        /***
         * if it is the begin of a function,
         * need to insert the parameters into symbol table
         * */
        while(paraOfFun!=NULL){
            paraOfFun->handle=newHandle;
            stPtr=stInsert(newHandle,paraOfFun->attr.name,paraOfFun->type,paraOfFun->lineno,0);
            if(stPtr==NULL){
                printf("error:line %d:redeclaration of arguement %s\n",node->lineno,node->attr.name);
                Error=1;
            }
            paraOfFun=paraOfFun->sibling;
        }
    }
    else{
        newHandle=handle;
    }
    node->handle=newHandle;

    if(node->kind==DeclK){
        if(node->subkind.declType==SimVarDcl){
            /**
             * simple variable declaration, insert into symbol table
             * **/
            stPtr=stInsert(node->handle,node->attr.name,node->type,node->lineno,0);
            if(stPtr==NULL){
                printf("error:line %d:redeclaration of variable %s\n",node->lineno,node->attr.name);
                Error=1;
            }
            /*
             * preorder travel
             * */
            for(i=0;i<MAXCHILDREN;i++){
                if(node->child[i]!=NULL){
                    buildSymtab(node->child[i],node->handle,NULL,funType,funcName);
                }
            }
            if(node->sibling!=NULL){
                buildSymtab(node->sibling,handle,NULL,funType,funcName);
            }
        }
        else if(node->subkind.declType==ArrVarDcl){
            /**
             * array declaration
             * **/
            stPtr=stInsert(node->handle,node->attr.name,node->type,node->lineno,0);
            if(stPtr==NULL){
                printf("error:line %d:redeclaration of variable %s\n",node->lineno,node->attr.name);
                Error=1;
            }
            /*****
             * preorder travel
             * ***/
            for(i=0;i<MAXCHILDREN;i++){
                if(node->child[i]!=NULL){
                    buildSymtab(node->child[i],node->handle,NULL,funType,funcName);
                }
            }
            if(node->sibling!=NULL){
                buildSymtab(node->sibling,handle,NULL,funType,funcName);
            }
        }
        else{
            /****
             * function declaration
             * ****/
            stPtr=stInsert(node->handle,node->attr.name,node->type,node->lineno,1);
            if(stPtr==NULL){
                printf("error:line %d:redeclaration of function %s\n",node->lineno,node->attr.name);
                Error=1;
            }
            /**need to store the parameter with the function name**/
            else{
                paraNode=node->child[0];
                while(paraNode!=NULL){
                    if(stPtr->para==NULL){
                        stPtr->para=(StPara*)malloc(sizeof(StPara));
                        stParaPtr=stPtr->para;
                        stParaPtr->type=paraNode->type;
                        stParaPtr->next=NULL;
                        count++;
                    }
                    else{
                        stParaPtr->next=(StPara*)malloc(sizeof(StPara));
                        stParaPtr=stParaPtr->next;
                        stParaPtr->type=paraNode->type;
                        stParaPtr->next=NULL;
                        count++;
                    }
                    paraNode=paraNode->sibling;
                }   
                stPtr->count=count;
                /*******
                * the statement is in new function scope
                * ********/
                buildSymtab(node->child[1],node->handle,node->child[0],node->type,node->attr.name);
                /********
                * actually, no sibling
                * but for formalize
                * *******/
                if(node->sibling!=NULL){
                    buildSymtab(node->sibling,handle,NULL,funType,funcName);
                }
            }
        }
    }
    else{
        /*******
         * just preorder travel for other case
         * *******/
        for(i=0;i<MAXCHILDREN;i++){
            if(node->child[i]!=NULL){
                buildSymtab(node->child[i],node->handle,NULL,funType,funcName);
            }
        }
        if(node->sibling!=NULL){
            buildSymtab(node->sibling,handle,NULL,funType,funcName);
        }
    }
}

/****type checking****/
void typeCheck(TreeNode* node)
{
    TreeNode* argPtr=NULL;
    StPara* stParaPtr=NULL;
    StNode* stPtr;
    int i;
    /***postorder travel***/
    for(i=0;i<MAXCHILDREN;i++){
        if(node->child[i]!=NULL){
            typeCheck(node->child[i]);
        }
    }
    /***check***/
    switch(node->kind){
    case DeclK:{
    /*declaration, already have types, no operation*/
        switch(node->subkind.declType){
        case SimVarDcl:{
            break;
        }
        case ArrVarDcl:{
            break;
        }
        case FunDcl:{
            break;
        }
        }
    break;
    }
    case ParaK:{
        /*parameters, already have types, no operation*/
        switch(node->subkind.paraType){
        case Simple:{
            
            break;
        }
        case Array:{
            
            break;
        }
        }
    break;
    }
    case StmtK:{
        switch(node->subkind.stmtType){
        case ComStmt:{
        /*compound statement, nothing to check*/
            if(node->child[0]!=NULL)
                node->type=node->child[0]->type;
            else{}
            break;
        }
        case ExprStmt:{
        /*expression statement, nothing to check*/
            if(node->child[0]!=NULL)
                node->type=node->child[0]->type;
            break;
        }
        case SeleStmt:{
        /*if statement, check if the condition is boolean*/
            if(node->child[0]->type!=Boolean){
                printf("error:line %d:condition must be a boolean value\n",node->lineno);
                Error=1;
            }
            
            break;
        }
        case IterStmt:{
        /*while statement, check if the condition is boolean*/
            if(node->child[0]->type!=Boolean){
                printf("error:line %d:condition must be a boolean value\n",node->lineno);
                Error=1;
            }
            break;
        }
        case ReturnStmt:{
        /*reutrn statement, check if the type is compatible with the funcation declaration*/
            if(node->child[0]==NULL){
                if(node->handle->funType!=Void){
                    printf("error:line %d:return value not compatible\n",node->lineno);
                    Error=1;
                }
            }
            else{
                node->type=node->child[0]->type;
                if(node->handle->funType!=node->child[0]->type){
                    printf("error:line %d:return value not compatible\n",node->lineno);
                    Error=1;
                }
            }
            break;
        }
        }
    break;
    }
    case ExprK:{
        switch(node->subkind.exprType){
        case AssignExp:{
        /*assigment expresstion, check if the type is compatible*/
            if(node->child[0]->type!=node->child[1]->type){
                printf("error:line %d:type error while assign to %s\n",node->lineno,node->child[0]->attr.name);
                Error=1;
            }
            node->type=node->child[0]->type;
            break;
        }
        case SimpExp:{
            if(node->child[1]==NULL){
                /***just one expresstion***/
                node->type=node->child[0]->type;
            }
            else{
                if(node->child[0]->type!=node->child[1]->type){
                    printf("error:line %d:operand type not compatible\n",node->lineno);
                    Error=1;
                }
                node->type=Boolean;
            }
            break;
        }
        }
    break;
    }
    case VarK:{
        switch(node->subkind.varType){
        /**variables, check if it is declared**/
        case ArrayVar:{
            stPtr=stLookup(node->handle,node->attr.name);
            if(stPtr==NULL){
                printf("error:line %d:%s has not been declared as a variable\n",node->lineno,node->attr.name);
                Error=1;
                node->type=Integer;
            }
            else{
                if(stPtr->type==IntArray)
                    node->type=Integer;
                else if(stPtr->type==VoidArray)
                    node->type=Void;
                else
                    node->type=Boolean;
            }
            break;
        }
        case SimpVar:{
            stPtr=stLookup(node->handle,node->attr.name);
            if(stPtr==NULL){
                printf("error:line %d:%s is not a variable\n",node->lineno,node->attr.name);
                Error=1;
                node->type=Integer;
            }
            else{
                node->type=stPtr->type;
            }
            break;
        }
        }
    break;
    }
    case AddexprK:{
        if(node->child[0]->type!=node->child[1]->type){
            printf("error:line %d:operand type not compatible\n",node->lineno);
            Error=1;
        }
        node->type=node->child[0]->type;
        break;
    }
    case TermK:{
        switch(node->subkind.termType){
        case Multiple:{
            /***term type with mulop, check if two operand is compatible**/
            if(node->child[0]->type!=node->child[1]->type){
                printf("error:line %d:operand type not compatible\n",node->lineno);
                Error=1;
            }
            node->type=node->child[0]->type;
            break;
        }
        case Single:{
        /**single factor, just assign type**/
            node->type=node->child[0]->type;
            break;
        }
        }
    break;
    }
    case FactK:{
        switch(node->subkind.factorType){
        case Expr:{
        /**expression, **/
            node->type=node->child[0]->type;
            break;
        }
        case Var:{
        /**variable, assign type of variable**/
            node->type=node->child[0]->type;
            break;
        }
        case Call:{
        /**call factor, assign the type of the function**/
            node->type=node->child[0]->type;
            break;
        }
        case Num:{
        /**just a Integer**/
            node->type=Integer;
            break;
        } 
        }
    break;
    }
    case CallK:{
    /***call function***/
        stPtr=stLookup(node->handle,node->attr.name);
        if(stPtr==NULL || stPtr->isFun==0){
        /**check if the function is declared**/
            printf("error: line %d: %s is not a function name\n",node->lineno,node->attr.name);
            Error=1;
            node->type=Integer;
        }
        else{
            /**check if the arguements is all right**/
            argPtr=node->child[0];
            stParaPtr=stPtr->para;
            while(argPtr!=NULL && stParaPtr!=NULL){
                if(argPtr->type!=stParaPtr->type){
                    printf("error:line %d:arguement type not compatible\n",node->lineno);
                    Error=1;
                }
                argPtr=argPtr->sibling;
                stParaPtr=stParaPtr->next;
            }
            if(argPtr!=NULL || stParaPtr!=NULL){
                printf("error:line %d:arguement number not compatible\n",node->lineno);
                    Error=1;
            }
            node->type=stPtr->type;
        }
        break;
    }
    case ArgsK:{
        break;
    }
    }
    /*****travel the sibling******/

    if(node->sibling!=NULL){
        typeCheck(node->sibling);
    }
}
