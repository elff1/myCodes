#!/bin/sh
yacc -d parser.y
flex scanner.l
gcc main.c generate.c encode.c symtab.c util.c y.tab.c lex.yy.c analyze.c -o CMinusCompiler -lfl
