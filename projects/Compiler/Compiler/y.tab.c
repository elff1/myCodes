
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 7 "parser.y"

#include"globals.h"
#include"util.h"



/* Line 189 of yacc.c  */
#line 80 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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

/* Line 214 of yacc.c  */
#line 26 "parser.y"

    TreeNode* node;
    char* str;
    int val;



/* Line 214 of yacc.c  */
#line 184 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 196 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   121

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  65
/* YYNRULES -- Number of states.  */
#define YYNSTATES  104

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   285

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    18,    25,
      27,    29,    31,    38,    40,    42,    46,    48,    51,    56,
      61,    64,    65,    68,    69,    71,    73,    75,    77,    79,
      81,    84,    86,    92,   100,   106,   109,   113,   117,   119,
     121,   126,   130,   132,   134,   136,   138,   140,   142,   144,
     148,   150,   152,   154,   158,   160,   162,   164,   168,   170,
     172,   174,   179,   181,   182,   186
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      32,     0,    -1,    33,    -1,    33,    34,    -1,    34,    -1,
      35,    -1,    37,    -1,    36,    29,    26,    -1,    36,    29,
       9,    28,    10,    26,    -1,     1,    -1,     3,    -1,     4,
      -1,    36,    29,    13,    38,    14,    41,    -1,    39,    -1,
       4,    -1,    39,    27,    40,    -1,    40,    -1,    36,    29,
      -1,    36,    29,     9,    10,    -1,    11,    42,    43,    12,
      -1,    42,    35,    -1,    -1,    43,    44,    -1,    -1,    45,
      -1,    41,    -1,    46,    -1,    47,    -1,    48,    -1,     1,
      -1,    49,    26,    -1,    26,    -1,     5,    13,    49,    14,
      44,    -1,     5,    13,    49,    14,    44,     6,    44,    -1,
       8,    13,    49,    14,    44,    -1,     7,    26,    -1,     7,
      49,    26,    -1,    50,    21,    49,    -1,    51,    -1,    29,
      -1,    29,     9,    49,    10,    -1,    53,    52,    53,    -1,
      53,    -1,    15,    -1,    16,    -1,    18,    -1,    17,    -1,
      19,    -1,    20,    -1,    53,    54,    55,    -1,    55,    -1,
      22,    -1,    23,    -1,    55,    56,    57,    -1,    57,    -1,
      24,    -1,    25,    -1,    13,    49,    14,    -1,    50,    -1,
      58,    -1,    28,    -1,    29,    13,    59,    14,    -1,    60,
      -1,    -1,    60,    27,    49,    -1,    49,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    45,    45,    53,    69,    74,    78,    82,    94,   114,
     120,   129,   135,   151,   158,   163,   179,   184,   194,   209,
     228,   245,   249,   266,   270,   277,   281,   285,   289,   293,
     302,   313,   323,   337,   359,   377,   386,   397,   408,   415,
     425,   438,   448,   456,   457,   458,   459,   460,   461,   463,
     473,   478,   479,   481,   497,   505,   506,   508,   519,   529,
     537,   545,   558,   563,   567,   583
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "VOID", "IF", "ELSE", "RETURN",
  "WHILE", "LBRACKET", "RBRACKET", "LBRACE", "RBRACE", "LPARENT",
  "RPARENT", "LE", "LT", "GE", "GT", "EQ", "NE", "ASSIGN", "PLUS", "MINUS",
  "TIMES", "DIVID", "SEMICOLON", "COMMA", "NUM", "ID", "ERROR", "$accept",
  "program", "declaration_list", "declaration", "var_declaration",
  "type_specifier", "fun_declaration", "params", "param_list", "param",
  "compound_stmt", "local_declarations", "statement_list", "statement",
  "expression_stmt", "selection_stmt", "iteration_stmt", "return_stmt",
  "expression", "var", "simple_expression", "relop", "additive_expression",
  "addop", "term", "mulop", "factor", "call", "args", "arg_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    31,    32,    33,    33,    34,    34,    35,    35,    35,
      36,    36,    37,    38,    38,    39,    39,    40,    40,    41,
      42,    42,    43,    43,    44,    44,    44,    44,    44,    44,
      45,    45,    46,    46,    47,    48,    48,    49,    49,    50,
      50,    51,    51,    52,    52,    52,    52,    52,    52,    53,
      53,    54,    54,    55,    55,    56,    56,    57,    57,    57,
      57,    58,    59,    59,    60,    60
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     6,     1,
       1,     1,     6,     1,     1,     3,     1,     2,     4,     4,
       2,     0,     2,     0,     1,     1,     1,     1,     1,     1,
       2,     1,     5,     7,     5,     2,     3,     3,     1,     1,
       4,     3,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     3,     1,     1,     1,     3,     1,     1,
       1,     4,     1,     0,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     9,    10,    11,     0,     0,     4,     5,     0,     6,
       1,     3,     0,     0,     0,     7,     0,    11,     0,     0,
      13,    16,     0,    17,     0,     0,     8,     0,    21,    12,
      15,    18,     0,    20,     0,     0,     0,    29,     0,     0,
       0,    19,     0,    31,    60,    39,    25,    22,    24,    26,
      27,    28,     0,    58,    38,    42,    50,    54,    59,     0,
      35,     0,     0,     0,     0,    63,    30,     0,    43,    44,
      46,    45,    47,    48,    51,    52,     0,     0,    55,    56,
       0,     0,    36,     0,    57,     0,    65,     0,    62,    37,
      58,    41,    49,    53,     0,     0,    40,    61,     0,    32,
      34,    64,     0,    33
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,     8,     9,    19,    20,    21,
      46,    32,    35,    47,    48,    49,    50,    51,    52,    53,
      54,    76,    55,    77,    56,    80,    57,    58,    87,    88
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -40
static const yytype_int8 yypact[] =
{
      87,   -40,   -40,   -40,    10,    62,   -40,   -40,    -7,   -40,
     -40,   -40,    -2,     3,    12,   -40,    26,    24,    18,    54,
      51,   -40,    29,    85,    84,    47,   -40,    86,   -40,   -40,
     -40,   -40,     1,   -40,    68,    32,    -8,   -40,    88,     6,
      89,   -40,    28,   -40,   -40,     8,   -40,   -40,   -40,   -40,
     -40,   -40,    72,    78,   -40,    57,    61,   -40,   -40,    28,
     -40,    74,    28,    90,    28,    28,   -40,    28,   -40,   -40,
     -40,   -40,   -40,   -40,   -40,   -40,    28,    28,   -40,   -40,
      28,    91,   -40,    92,   -40,    93,   -40,    94,    80,   -40,
     -40,    70,    61,   -40,    41,    41,   -40,   -40,    28,   103,
     -40,   -40,    41,   -40
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -40,   -40,   -40,   105,    79,    39,   -40,   -40,   -40,    95,
      97,   -40,   -40,   -13,   -40,   -40,   -40,   -40,   -39,     7,
     -40,   -40,    36,   -40,    37,   -40,    33,   -40,   -40,   -40
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -24
static const yytype_int8 yytable[] =
{
      61,    13,     1,    63,     2,     3,   -23,    13,   -23,   -23,
      10,    14,   -23,   -23,   -23,     2,    17,    64,    15,    42,
      81,    65,    12,    83,    15,    85,    86,   -23,    89,   -23,
     -23,    16,    60,    37,    44,    45,    22,    38,   -14,    39,
      40,    42,    37,    28,    41,    42,    38,    23,    39,    40,
       2,     3,    28,    18,    42,    26,    44,    45,    43,   101,
      44,    45,    -2,     1,    18,     2,     3,    43,    24,    44,
      45,    34,    68,    69,    70,    71,    72,    73,    25,    74,
      75,    99,   100,    90,    90,    78,    79,    90,     1,   103,
       2,     3,    74,    75,    27,    28,    31,    36,    66,    67,
      82,    59,    62,    96,    84,    94,    95,    98,    97,   102,
      11,    33,    91,    93,    92,     0,     0,     0,     0,     0,
      30,    29
};

static const yytype_int8 yycheck[] =
{
      39,     9,     1,    42,     3,     4,     5,     9,     7,     8,
       0,    13,    11,    12,    13,     3,     4,     9,    26,    13,
      59,    13,    29,    62,    26,    64,    65,    26,    67,    28,
      29,    28,    26,     1,    28,    29,    10,     5,    14,     7,
       8,    13,     1,    11,    12,    13,     5,    29,     7,     8,
       3,     4,    11,    14,    13,    26,    28,    29,    26,    98,
      28,    29,     0,     1,    25,     3,     4,    26,    14,    28,
      29,    32,    15,    16,    17,    18,    19,    20,    27,    22,
      23,    94,    95,    76,    77,    24,    25,    80,     1,   102,
       3,     4,    22,    23,     9,    11,    10,    29,    26,    21,
      26,    13,    13,    10,    14,    14,    14,    27,    14,     6,
       5,    32,    76,    80,    77,    -1,    -1,    -1,    -1,    -1,
      25,    24
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,     4,    32,    33,    34,    35,    36,    37,
       0,    34,    29,     9,    13,    26,    28,     4,    36,    38,
      39,    40,    10,    29,    14,    27,    26,     9,    11,    41,
      40,    10,    42,    35,    36,    43,    29,     1,     5,     7,
       8,    12,    13,    26,    28,    29,    41,    44,    45,    46,
      47,    48,    49,    50,    51,    53,    55,    57,    58,    13,
      26,    49,    13,    49,     9,    13,    26,    21,    15,    16,
      17,    18,    19,    20,    22,    23,    52,    54,    24,    25,
      56,    49,    26,    49,    14,    49,    49,    59,    60,    49,
      50,    53,    55,    57,    14,    14,    10,    14,    27,    44,
      44,    49,     6,    44
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 46 "parser.y"
    {
        /*
        the root of the syntax tree
        */
        root=(yyvsp[(1) - (1)].node);
        }
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 54 "parser.y"
    {
                 /*
                 store declaration as a chain, by their sibings
                 */
                 TreeNode* t=(yyvsp[(1) - (2)].node);
                 if((yyvsp[(1) - (2)].node)!=NULL){
                    while(t->sibling!=NULL)
                        t=t->sibling;
                    t->sibling=(yyvsp[(2) - (2)].node);
                    (yyval.node)=(yyvsp[(1) - (2)].node);
                 }
                 else{
                    (yyval.node)=(yyvsp[(2) - (2)].node);
                 }
                 }
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 70 "parser.y"
    {
                 (yyval.node)=(yyvsp[(1) - (1)].node);
                 }
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 75 "parser.y"
    {
            (yyval.node)=(yyvsp[(1) - (1)].node);
            }
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 78 "parser.y"
    {
            (yyval.node)=(yyvsp[(1) - (1)].node);
            }
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 83 "parser.y"
    {
               /*
               create a node of varible declaration
               */
               if((yyvsp[(1) - (3)].node)==NULL)
                    (yyvsp[(1) - (3)].node)=newNode();
               (yyval.node)=(yyvsp[(1) - (3)].node);
               (yyval.node)->attr.name=(yyvsp[(2) - (3)].str);
               (yyval.node)->kind=DeclK;
               (yyval.node)->subkind.declType=SimVarDcl;
               }
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 95 "parser.y"
    {
               /*
               create a node of varible declaration, it is an array
               */
               if((yyvsp[(1) - (6)].node)==NULL)
                    (yyvsp[(1) - (6)].node)=newNode();
               (yyval.node)=(yyvsp[(1) - (6)].node);
               (yyval.node)->attr.name=(yyvsp[(2) - (6)].str);
               (yyval.node)->kind=DeclK;
               (yyval.node)->subkind.declType=ArrVarDcl;
               if((yyval.node)->type==Integer)
                    (yyval.node)->type=IntArray;
                else
                    (yyval.node)->type=VoidArray;
               /*
               the length of the array is store in the indexOrOperator
               */
               (yyval.node)->indexOrOperator=(yyvsp[(4) - (6)].val);
               }
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 115 "parser.y"
    {
               (yyval.node)=newNode();
               Error=1;
               }
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 121 "parser.y"
    {
              /*
              create a node here for declarations,
              the declarations will use this node
              */
              (yyval.node)=newNode();
              (yyval.node)->type=Integer;
              }
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 130 "parser.y"
    {
              (yyval.node)=newNode();
              (yyval.node)->type=Void;
              }
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 136 "parser.y"
    {
               (yyval.node)=(yyvsp[(1) - (6)].node);
               (yyval.node)->kind=DeclK;
               (yyval.node)->subkind.declType=FunDcl;
               /*
               function name
               */
               (yyval.node)->attr.name=(yyvsp[(2) - (6)].str);
               /*
               parameters, store as a chain with their sibling
               */
               (yyval.node)->child[0]=(yyvsp[(4) - (6)].node);
               (yyval.node)->child[1]=(yyvsp[(6) - (6)].node);
               }
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 152 "parser.y"
    {
      /*
      parameter chain
      */
      (yyval.node)=(yyvsp[(1) - (1)].node);
      }
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 159 "parser.y"
    {
      (yyval.node)=NULL;
      }
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 164 "parser.y"
    {
          /*
          parameters store by a chain with siblings
          */
          TreeNode* t=(yyvsp[(1) - (3)].node);
          if(t!=NULL){
            while(t->sibling!=NULL)
                t=t->sibling;
                t->sibling=(yyvsp[(3) - (3)].node);
                (yyval.node)=(yyvsp[(1) - (3)].node);
          }
          else{
            (yyval.node)=(yyvsp[(3) - (3)].node);
          }
          }
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 180 "parser.y"
    {
            (yyval.node)=(yyvsp[(1) - (1)].node);
          }
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 185 "parser.y"
    {
     /*
     node of parameters, it is a simple type
     */
     (yyval.node)=(yyvsp[(1) - (2)].node);
     (yyval.node)->kind=ParaK;
     (yyval.node)->subkind.paraType=Simple;
     (yyval.node)->attr.name=(yyvsp[(2) - (2)].str);
     }
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 195 "parser.y"
    {
     /*
     node of parameters, it is a array type
     */
     (yyval.node)=(yyvsp[(1) - (4)].node);
     (yyval.node)->kind=ParaK;
     (yyval.node)->subkind.paraType=Array;
     (yyval.node)->attr.name=(yyvsp[(2) - (4)].str);
     if((yyval.node)->type==Integer)
        (yyval.node)->type=IntArray;
     else
        (yyval.node)->type=VoidArray;
     }
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 210 "parser.y"
    {
             /*
             a compound statament form a new scope
             including declarations and statements
             */
             (yyval.node)=newNode();
             /*
             declarations, store by a chain
             */
             (yyval.node)->child[0]=(yyvsp[(2) - (4)].node);
             /*
             statements, store by a chain
             */
             (yyval.node)->child[1]=(yyvsp[(3) - (4)].node);
             (yyval.node)->kind=StmtK;
             (yyval.node)->subkind.stmtType=ComStmt;
             }
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 229 "parser.y"
    {
                  /*
                  varabile declarations, store by a chain
                  */
                  TreeNode* t=(yyvsp[(1) - (2)].node);
                  if(t!=NULL){
                    while(t->sibling!=NULL)
                        t=t->sibling;
                    t->sibling=(yyvsp[(2) - (2)].node);
                    (yyval.node)=(yyvsp[(1) - (2)].node);
                  }
                  else{
                    (yyval.node)=(yyvsp[(2) - (2)].node);
                  }
                  }
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 245 "parser.y"
    {
                    (yyval.node)=NULL;
                  }
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 250 "parser.y"
    {
              /*
              statements, store by a chain
              */
              TreeNode* t=(yyvsp[(1) - (2)].node);
              if(t!=NULL){
                while(t->sibling!=NULL)
                    t=t->sibling;
                t->sibling=(yyvsp[(2) - (2)].node);
                (yyval.node)=(yyvsp[(1) - (2)].node);
              }
              else{
                (yyval.node)=(yyvsp[(2) - (2)].node);
              }
              }
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 266 "parser.y"
    {
                (yyval.node)=NULL;
              }
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 271 "parser.y"
    {
         /*
         a statement have different type, just link them
         */
         (yyval.node)=(yyvsp[(1) - (1)].node);
         }
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 278 "parser.y"
    {
         (yyval.node)=(yyvsp[(1) - (1)].node);
         }
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 282 "parser.y"
    {
         (yyval.node)=(yyvsp[(1) - (1)].node);
         }
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 286 "parser.y"
    {
         (yyval.node)=(yyvsp[(1) - (1)].node);
         }
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 290 "parser.y"
    {
         (yyval.node)=(yyvsp[(1) - (1)].node);
         }
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 294 "parser.y"
    {
         /*
         error recovery, by replace this node as a NULL value
         */
         (yyval.node)=NULL;
         Error=1;
         }
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 303 "parser.y"
    {
                /*
                a expression statement
                */
                (yyval.node)=newNode();
                (yyval.node)->kind=StmtK;
                (yyval.node)->subkind.stmtType=ExprStmt;
                /*the actually expression node*/
                (yyval.node)->child[0]=(yyvsp[(1) - (2)].node);
                }
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 313 "parser.y"
    {
               /*
               empty statement,
               but still need to use this node to form a chain
               */
               (yyval.node)=newNode();
               (yyval.node)->kind=StmtK;
               (yyval.node)->subkind.stmtType=ExprStmt;
               }
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 324 "parser.y"
    {
              (yyval.node)=newNode();
              (yyval.node)->kind=StmtK;
              (yyval.node)->subkind.stmtType=SeleStmt;
              /*
              the condition expression
              */
              (yyval.node)->child[0]=(yyvsp[(3) - (5)].node);
              /*
              the statements
              */
              (yyval.node)->child[1]=(yyvsp[(5) - (5)].node);
              }
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 338 "parser.y"
    {
              /*
              a if statement with a else part
              */
              (yyval.node)=newNode();
              (yyval.node)->kind=StmtK;
              (yyval.node)->subkind.stmtType=SeleStmt;
              /*
              condition
              */
              (yyval.node)->child[0]=(yyvsp[(3) - (7)].node);
              /*
              the if statement
              */
              (yyval.node)->child[1]=(yyvsp[(5) - (7)].node);
              /*
              the else statement
              */
              (yyval.node)->child[2]=(yyvsp[(7) - (7)].node);
              }
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 360 "parser.y"
    {
              /*
              while statement
              */
              (yyval.node)=newNode();
              (yyval.node)->kind=StmtK;
              (yyval.node)->subkind.stmtType=IterStmt;
              /*
              the condition expression
              */
              (yyval.node)->child[0]=(yyvsp[(3) - (5)].node);
              /*
              the statements
              */
              (yyval.node)->child[1]=(yyvsp[(5) - (5)].node);
              }
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 378 "parser.y"
    {
           /*
           a return statement without express for void type
           */
           (yyval.node)=newNode();
           (yyval.node)->kind=StmtK;
           (yyval.node)->subkind.stmtType=ReturnStmt;
           }
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 387 "parser.y"
    {
           /*
           a return statement with expression, for int type
           */
           (yyval.node)=newNode();
           (yyval.node)->kind=StmtK;
           (yyval.node)->subkind.stmtType=ReturnStmt;
           (yyval.node)->child[0]=(yyvsp[(2) - (3)].node);
           }
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 398 "parser.y"
    {
          /*
          a assignment expression
          */
          (yyval.node)=newNode();
          (yyval.node)->kind=ExprK;
          (yyval.node)->subkind.exprType=AssignExp;
          (yyval.node)->child[0]=(yyvsp[(1) - (3)].node);
          (yyval.node)->child[1]=(yyvsp[(3) - (3)].node);
          }
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 408 "parser.y"
    {
          /*
          a simple expression
          */
          (yyval.node)=(yyvsp[(1) - (1)].node);
          }
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 416 "parser.y"
    {
   /*
   the identifiter
   */
   (yyval.node)=newNode();
   (yyval.node)->kind=VarK;
   (yyval.node)->subkind.varType=SimpVar;
   (yyval.node)->attr.name=(yyvsp[(1) - (1)].str);
   }
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 426 "parser.y"
    {
   /*
   array type
   */
   (yyval.node)=newNode();
   (yyval.node)->kind=VarK;
   (yyval.node)->subkind.varType=ArrayVar;
   (yyval.node)->attr.name=(yyvsp[(1) - (4)].str);
   /*the expression value of the index*/
   (yyval.node)->child[0]=(yyvsp[(3) - (4)].node);
   }
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 439 "parser.y"
    {
                 /*simple expressions, my be a relation expression*/
                 (yyval.node)=newNode();
                 (yyval.node)->kind=ExprK;
                 (yyval.node)->subkind.exprType=SimpExp;
                 (yyval.node)->indexOrOperator=(yyvsp[(2) - (3)].val);
                 (yyval.node)->child[0]=(yyvsp[(1) - (3)].node);
                 (yyval.node)->child[1]=(yyvsp[(3) - (3)].node);
                 }
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 448 "parser.y"
    {
                 /*additive expression, just +,-,*,/  */
                 (yyval.node)=newNode();
                 (yyval.node)->kind=ExprK;
                 (yyval.node)->subkind.exprType=SimpExp;
                 (yyval.node)->child[0]=(yyvsp[(1) - (1)].node);
                 }
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 456 "parser.y"
    {(yyval.val)=(yyvsp[(1) - (1)].val);}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 457 "parser.y"
    {(yyval.val)=(yyvsp[(1) - (1)].val);}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 458 "parser.y"
    {(yyval.val)=(yyvsp[(1) - (1)].val);}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 459 "parser.y"
    {(yyval.val)=(yyvsp[(1) - (1)].val);}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 460 "parser.y"
    {(yyval.val)=(yyvsp[(1) - (1)].val);}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 461 "parser.y"
    {(yyval.val)=(yyvsp[(1) - (1)].val);}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 464 "parser.y"
    {
                   (yyval.node)=newNode();
                   (yyval.node)->kind=AddexprK;
                   (yyval.node)->indexOrOperator=(yyvsp[(2) - (3)].val);
                   /*addivite_expression*/
                   (yyval.node)->child[0]=(yyvsp[(1) - (3)].node);
                   /*term*/
                   (yyval.node)->child[1]=(yyvsp[(3) - (3)].node);
                   }
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 474 "parser.y"
    {
                   (yyval.node)=(yyvsp[(1) - (1)].node);
                   }
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 478 "parser.y"
    {(yyval.val)=(yyvsp[(1) - (1)].val);}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 479 "parser.y"
    {(yyval.val)=(yyvsp[(1) - (1)].val);}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 482 "parser.y"
    {
    
    (yyval.node)=newNode();
    (yyval.node)->kind=TermK;
    (yyval.node)->subkind.termType=Multiple;
    (yyval.node)->indexOrOperator=(yyvsp[(2) - (3)].val);
    /*
    term
    */
    (yyval.node)->child[0]=(yyvsp[(1) - (3)].node);
    /*
    factor
    */
    (yyval.node)->child[1]=(yyvsp[(3) - (3)].node);
    }
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 497 "parser.y"
    {
    (yyval.node)=newNode();
    (yyval.node)->kind=TermK;
    (yyval.node)->subkind.termType=Single;
    /*just a single factor*/
    (yyval.node)->child[0]=(yyvsp[(1) - (1)].node);
    }
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 505 "parser.y"
    {(yyval.val)=(yyvsp[(1) - (1)].val);}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 506 "parser.y"
    {(yyval.val)=(yyvsp[(1) - (1)].val);}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 509 "parser.y"
    {
      /*
      a factor be be different kind
      here is a epression
      */
      (yyval.node)=newNode();
      (yyval.node)->kind=FactK;
      (yyval.node)->subkind.factorType=Expr;
      (yyval.node)->child[0]=(yyvsp[(2) - (3)].node);
      }
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 520 "parser.y"
    {
      /*
      variable
      */
      (yyval.node)=newNode();
      (yyval.node)->kind=FactK;
      (yyval.node)->subkind.factorType=Var;
      (yyval.node)->child[0]=(yyvsp[(1) - (1)].node);
      }
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 530 "parser.y"
    {
      /*call function*/
      (yyval.node)=newNode();
      (yyval.node)->subkind.factorType=Call;
      (yyval.node)->kind=FactK;
      (yyval.node)->child[0]=(yyvsp[(1) - (1)].node);
      }
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 537 "parser.y"
    {
      (yyval.node)=newNode();
      (yyval.node)->kind=FactK;
      (yyval.node)->subkind.factorType=Num;
      (yyval.node)->type=Integer;
      (yyval.node)->attr.val=(yyvsp[(1) - (1)].val);
      }
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 546 "parser.y"
    {
    /*call a function*/
    (yyval.node)=newNode();
    (yyval.node)->kind=CallK;
    (yyval.node)->attr.name=(yyvsp[(1) - (4)].str);
    (yyval.node)->indexOrOperator;
    /*
    arguements, store by a chain with their siblings
    */
    (yyval.node)->child[0]=(yyvsp[(3) - (4)].node);
    }
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 559 "parser.y"
    {
    (yyval.node)=(yyvsp[(1) - (1)].node);
    }
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 563 "parser.y"
    {
    (yyval.node)=NULL;
    }
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 568 "parser.y"
    {
        /*
        the arguement of a call statement is expression that form a chain
        */
        TreeNode* t=(yyvsp[(1) - (3)].node);
        if(t!=NULL){
            while(t->sibling!=NULL)
                t=t->sibling;
            t->sibling=(yyvsp[(3) - (3)].node);
            (yyval.node)=(yyvsp[(1) - (3)].node);
        }
        else{
            (yyval.node)=(yyvsp[(3) - (3)].node);
        }
        }
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 584 "parser.y"
    {
        (yyval.node)=(yyvsp[(1) - (1)].node);
        }
    break;



/* Line 1455 of yacc.c  */
#line 2337 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 590 "parser.y"

int yyerror(char* msg){
    printf("%s:%d\n",msg,lineno);
    return 0;
}


