/*
The yacc program for parser.
Paser the program and build syntax tree.
Including error recovery.
*/

%{
#include"globals.h"
#include"util.h"

%}
/*
Tokens and type definision.
Actually, the ID will be a string.
Other token from the scanner will be int.
All other token is a point to a tree node.
*/
%token INT VOID IF ELSE RETURN WHILE
%token LBRACKET RBRACKET LBRACE RBRACE LPARENT RPARENT
%token LE LT GE GT EQ NE ASSIGN PLUS MINUS TIMES DIVID
%token SEMICOLON COMMA
%token NUM
%token ID
%token ERROR

%union{
    TreeNode* node;
    char* str;
    int val;
}

%type <val> INT VOID IF ELSE RETURN WHILE LBRACKET RBRACKET LBRACE RBRACE LPARENT RPARENT 
%type <val> LE LT GE GT EQ NE ASSIGN PLUS MINUS TIMES DIVID SEMICOLON COMMA NUM ERROR
%type <str> ID
%type <val> relop mulop addop 
%type <node> program declaration_list declaration var_declaration type_specifier 
%type <node> fun_declaration params compound_stmt param_list param local_declarations statement_list
%type <node> statement expression_stmt selection_stmt iteration_stmt return_stmt
%type <node> expression var simple_expression additive_expression term factor call args arg_list 

%%
/*
grammar rules
*/
program : declaration_list
        {
        /*
        the root of the syntax tree
        */
        root=$1;
        }
        ;
declaration_list : declaration_list declaration 
                 {
                 /*
                 store declaration as a chain, by their sibings
                 */
                 TreeNode* t=$1;
                 if($1!=NULL){
                    while(t->sibling!=NULL)
                        t=t->sibling;
                    t->sibling=$2;
                    $$=$1;
                 }
                 else{
                    $$=$2;
                 }
                 }
                 | declaration
                 {
                 $$=$1;
                 }
                 ;
declaration : var_declaration
            {
            $$=$1;
            }
            | fun_declaration{
            $$=$1;
            }
            ;
var_declaration:type_specifier ID SEMICOLON
               {
               /*
               create a node of varible declaration
               */
               if($1==NULL)
                    $1=newNode();
               $$=$1;
               $$->attr.name=$2;
               $$->kind=DeclK;
               $$->subkind.declType=SimVarDcl;
               }
               |type_specifier ID LBRACKET NUM RBRACKET SEMICOLON
               {
               /*
               create a node of varible declaration, it is an array
               */
               if($1==NULL)
                    $1=newNode();
               $$=$1;
               $$->attr.name=$2;
               $$->kind=DeclK;
               $$->subkind.declType=ArrVarDcl;
               if($$->type==Integer)
                    $$->type=IntArray;
                else
                    $$->type=VoidArray;
               /*
               the length of the array is store in the indexOrOperator
               */
               $$->indexOrOperator=$4;
               }
               |error
               {
               $$=newNode();
               Error=1;
               }
               ;
type_specifier:INT
              {
              /*
              create a node here for declarations,
              the declarations will use this node
              */
              $$=newNode();
              $$->type=Integer;
              }
              |VOID
              {
              $$=newNode();
              $$->type=Void;
              }
              ;
fun_declaration:type_specifier ID LPARENT params RPARENT compound_stmt
               {
               $$=$1;
               $$->kind=DeclK;
               $$->subkind.declType=FunDcl;
               /*
               function name
               */
               $$->attr.name=$2;
               /*
               parameters, store as a chain with their sibling
               */
               $$->child[0]=$4;
               $$->child[1]=$6;
               }
               ;
params:param_list
      {
      /*
      parameter chain
      */
      $$=$1;
      }
      |VOID
      {
      $$=NULL;
      }
      ;
param_list:param_list COMMA param
          {
          /*
          parameters store by a chain with siblings
          */
          TreeNode* t=$1;
          if(t!=NULL){
            while(t->sibling!=NULL)
                t=t->sibling;
                t->sibling=$3;
                $$=$1;
          }
          else{
            $$=$3;
          }
          }
          |param
          {
            $$=$1;
          }
          ;
param:type_specifier ID
     {
     /*
     node of parameters, it is a simple type
     */
     $$=$1;
     $$->kind=ParaK;
     $$->subkind.paraType=Simple;
     $$->attr.name=$2;
     }
     |type_specifier ID LBRACKET RBRACKET
     {
     /*
     node of parameters, it is a array type
     */
     $$=$1;
     $$->kind=ParaK;
     $$->subkind.paraType=Array;
     $$->attr.name=$2;
     if($$->type==Integer)
        $$->type=IntArray;
     else
        $$->type=VoidArray;
     }
     ;
compound_stmt:LBRACE local_declarations statement_list RBRACE
             {
             /*
             a compound statament form a new scope
             including declarations and statements
             */
             $$=newNode();
             /*
             declarations, store by a chain
             */
             $$->child[0]=$2;
             /*
             statements, store by a chain
             */
             $$->child[1]=$3;
             $$->kind=StmtK;
             $$->subkind.stmtType=ComStmt;
             }
             ;
local_declarations:local_declarations var_declaration
                  {
                  /*
                  varabile declarations, store by a chain
                  */
                  TreeNode* t=$1;
                  if(t!=NULL){
                    while(t->sibling!=NULL)
                        t=t->sibling;
                    t->sibling=$2;
                    $$=$1;
                  }
                  else{
                    $$=$2;
                  }
                  }
                  |
                  {
                    $$=NULL;
                  }
                  ;
statement_list:statement_list statement
              {
              /*
              statements, store by a chain
              */
              TreeNode* t=$1;
              if(t!=NULL){
                while(t->sibling!=NULL)
                    t=t->sibling;
                t->sibling=$2;
                $$=$1;
              }
              else{
                $$=$2;
              }
              }
              |
              {
                $$=NULL;
              }
              ;
statement:expression_stmt
         {
         /*
         a statement have different type, just link them
         */
         $$=$1;
         }
         |compound_stmt
         {
         $$=$1;
         }
         |selection_stmt
         {
         $$=$1;
         }
         |iteration_stmt
         {
         $$=$1;
         }
         |return_stmt
         {
         $$=$1;
         }
         |error
         {
         /*
         error recovery, by replace this node as a NULL value
         */
         $$=NULL;
         Error=1;
         }
         ;
expression_stmt:expression SEMICOLON
                {
                /*
                a expression statement
                */
                $$=newNode();
                $$->kind=StmtK;
                $$->subkind.stmtType=ExprStmt;
                /*the actually expression node*/
                $$->child[0]=$1;
                }
               |SEMICOLON{
               /*
               empty statement,
               but still need to use this node to form a chain
               */
               $$=newNode();
               $$->kind=StmtK;
               $$->subkind.stmtType=ExprStmt;
               }
               ;
selection_stmt:IF LPARENT expression RPARENT statement
              {
              $$=newNode();
              $$->kind=StmtK;
              $$->subkind.stmtType=SeleStmt;
              /*
              the condition expression
              */
              $$->child[0]=$3;
              /*
              the statements
              */
              $$->child[1]=$5;
              }
              |IF LPARENT expression RPARENT statement ELSE statement
              {
              /*
              a if statement with a else part
              */
              $$=newNode();
              $$->kind=StmtK;
              $$->subkind.stmtType=SeleStmt;
              /*
              condition
              */
              $$->child[0]=$3;
              /*
              the if statement
              */
              $$->child[1]=$5;
              /*
              the else statement
              */
              $$->child[2]=$7;
              }
              ;
iteration_stmt:WHILE LPARENT expression RPARENT statement
              {
              /*
              while statement
              */
              $$=newNode();
              $$->kind=StmtK;
              $$->subkind.stmtType=IterStmt;
              /*
              the condition expression
              */
              $$->child[0]=$3;
              /*
              the statements
              */
              $$->child[1]=$5;
              }
              ;
return_stmt:RETURN SEMICOLON
           {
           /*
           a return statement without express for void type
           */
           $$=newNode();
           $$->kind=StmtK;
           $$->subkind.stmtType=ReturnStmt;
           }
           |RETURN expression SEMICOLON
           {
           /*
           a return statement with expression, for int type
           */
           $$=newNode();
           $$->kind=StmtK;
           $$->subkind.stmtType=ReturnStmt;
           $$->child[0]=$2;
           }
           ;
expression:var ASSIGN expression
          {
          /*
          a assignment expression
          */
          $$=newNode();
          $$->kind=ExprK;
          $$->subkind.exprType=AssignExp;
          $$->child[0]=$1;
          $$->child[1]=$3;
          }
          |simple_expression{
          /*
          a simple expression
          */
          $$=$1;
          }
          ;
var:ID
   {
   /*
   the identifiter
   */
   $$=newNode();
   $$->kind=VarK;
   $$->subkind.varType=SimpVar;
   $$->attr.name=$1;
   }
   |ID LBRACKET expression RBRACKET
   {
   /*
   array type
   */
   $$=newNode();
   $$->kind=VarK;
   $$->subkind.varType=ArrayVar;
   $$->attr.name=$1;
   /*the expression value of the index*/
   $$->child[0]=$3;
   }
   ;
simple_expression:additive_expression relop additive_expression
                 {
                 /*simple expressions, my be a relation expression*/
                 $$=newNode();
                 $$->kind=ExprK;
                 $$->subkind.exprType=SimpExp;
                 $$->indexOrOperator=$2;
                 $$->child[0]=$1;
                 $$->child[1]=$3;
                 }
                 |additive_expression{
                 /*additive expression, just +,-,*,/  */
                 $$=newNode();
                 $$->kind=ExprK;
                 $$->subkind.exprType=SimpExp;
                 $$->child[0]=$1;
                 }
                 ;
relop:LE{$$=$1;}
     |LT{$$=$1;}
     |GT{$$=$1;}
     |GE{$$=$1;}
     |EQ{$$=$1;}
     |NE{$$=$1;}
     ;
additive_expression:additive_expression addop term
                   {
                   $$=newNode();
                   $$->kind=AddexprK;
                   $$->indexOrOperator=$2;
                   /*addivite_expression*/
                   $$->child[0]=$1;
                   /*term*/
                   $$->child[1]=$3;
                   }
                   |term
                   {
                   $$=$1;
                   }
                   ;
addop:PLUS{$$=$1;}
     |MINUS{$$=$1;}
     ;
term:term mulop factor
    {
    
    $$=newNode();
    $$->kind=TermK;
    $$->subkind.termType=Multiple;
    $$->indexOrOperator=$2;
    /*
    term
    */
    $$->child[0]=$1;
    /*
    factor
    */
    $$->child[1]=$3;
    }
    |factor{
    $$=newNode();
    $$->kind=TermK;
    $$->subkind.termType=Single;
    /*just a single factor*/
    $$->child[0]=$1;
    }
    ;
mulop:TIMES{$$=$1;}
     |DIVID{$$=$1;}
     ;
factor:LPARENT expression RPARENT
      {
      /*
      a factor be be different kind
      here is a epression
      */
      $$=newNode();
      $$->kind=FactK;
      $$->subkind.factorType=Expr;
      $$->child[0]=$2;
      }
      |var
      {
      /*
      variable
      */
      $$=newNode();
      $$->kind=FactK;
      $$->subkind.factorType=Var;
      $$->child[0]=$1;
      }
      |call
      {
      /*call function*/
      $$=newNode();
      $$->subkind.factorType=Call;
      $$->kind=FactK;
      $$->child[0]=$1;
      }
      |NUM{
      $$=newNode();
      $$->kind=FactK;
      $$->subkind.factorType=Num;
      $$->type=Integer;
      $$->attr.val=$1;
      }
      ;
call:ID LPARENT args RPARENT
    {
    /*call a function*/
    $$=newNode();
    $$->kind=CallK;
    $$->attr.name=$1;
    $$->indexOrOperator;
    /*
    arguements, store by a chain with their siblings
    */
    $$->child[0]=$3;
    }
    ;
args:arg_list
    {
    $$=$1;
    }
    |
    {
    $$=NULL;
    }
    ;
arg_list:arg_list COMMA expression
        {
        /*
        the arguement of a call statement is expression that form a chain
        */
        TreeNode* t=$1;
        if(t!=NULL){
            while(t->sibling!=NULL)
                t=t->sibling;
            t->sibling=$3;
            $$=$1;
        }
        else{
            $$=$3;
        }
        }
        |expression
        {
        $$=$1;
        }
        ;


%%
int yyerror(char* msg){
    printf("%s:%d\n",msg,lineno);
    return 0;
}

