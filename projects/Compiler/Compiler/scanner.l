/*
   the lex program for scanner
*/

%{
#include"globals.h"
#include"y.tab.h"
#include"util.h"
%}

digit [0-9]
number {digit}+
letter [a-zA-Z]
identifier {letter}+
newline \n
whitespace [ \t]+

%%

"int" {yylval.val=INT;return INT;}
"void" {yylval.val=VOID;return VOID;}
"if" {yylval.val=IF;return IF;}
"else" {yylval.val=ELSE;return ELSE;}
"return" {yylval.val=RETURN;return RETURN;}
"while" {yylval.val=WHILE;return WHILE;}
"[" {yylval.val=LBRACKET;return LBRACKET;}
"]" {yylval.val=RBRACKET;return RBRACKET;}
"{" {yylval.val=LBRACE;return LBRACE;}
"}" {yylval.val=RBRACE;return RBRACE;}
"(" {yylval.val=LPARENT;return LPARENT;}
")" {yylval.val=RPARENT;return RPARENT;}
";" {yylval.val=SEMICOLON;return SEMICOLON;}
"<=" {yylval.val=LE;return LE;}
"<" {yylval.val=LT;return LT;}
">=" {yylval.val=GE;return GE;}
">" {yylval.val=GT;return GT;}
"==" {yylval.val=EQ;return EQ;}
"!=" {yylval.val=NE;return NE;}
"=" {yylval.val=ASSIGN;return ASSIGN;}
"+" {yylval.val=PLUS;return PLUS;}
"-" {yylval.val=MINUS;return MINUS;}
"*" {yylval.val=TIMES;return TIMES;}
"/" {yylval.val=DIVID;return DIVID;}
"," {yylval.val=COMMA;return COMMA;}
{number} {yylval.val=atoi(yytext);return NUM;}
{identifier} {yylval.str=copyString(yytext);return ID;}
{whitespace} {}
{newline} {lineno++;}
. {printf("NONE\n");yylval.val=ERROR;return ERROR;}

%%

