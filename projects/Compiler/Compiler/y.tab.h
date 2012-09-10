
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     VOID = 259,
     IF = 260,
     ELSE = 261,
     RETURN = 262,
     WHILE = 263,
     LBRACKET = 264,
     RBRACKET = 265,
     LBRACE = 266,
     RBRACE = 267,
     LPARENT = 268,
     RPARENT = 269,
     LE = 270,
     LT = 271,
     GE = 272,
     GT = 273,
     EQ = 274,
     NE = 275,
     ASSIGN = 276,
     PLUS = 277,
     MINUS = 278,
     TIMES = 279,
     DIVID = 280,
     SEMICOLON = 281,
     COMMA = 282,
     NUM = 283,
     ID = 284,
     ERROR = 285
   };
#endif
/* Tokens.  */
#define INT 258
#define VOID 259
#define IF 260
#define ELSE 261
#define RETURN 262
#define WHILE 263
#define LBRACKET 264
#define RBRACKET 265
#define LBRACE 266
#define RBRACE 267
#define LPARENT 268
#define RPARENT 269
#define LE 270
#define LT 271
#define GE 272
#define GT 273
#define EQ 274
#define NE 275
#define ASSIGN 276
#define PLUS 277
#define MINUS 278
#define TIMES 279
#define DIVID 280
#define SEMICOLON 281
#define COMMA 282
#define NUM 283
#define ID 284
#define ERROR 285




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 26 "parser.y"

    TreeNode* node;
    char* str;
    int val;



/* Line 1676 of yacc.c  */
#line 120 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


