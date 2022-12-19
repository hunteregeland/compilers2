/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CHAR = 258,
     INT = 259,
     FLOAT = 260,
     VOID = 261,
     IF = 262,
     ELSE = 263,
     WHILE = 264,
     WRITE = 265,
     RETURN = 266,
     COMMA = 267,
     SEMICOLON = 268,
     NEWLINECHAR = 269,
     DOUBLE_EQ = 270,
     NOT_EQ = 271,
     LT_EQ = 272,
     GT_EQ = 273,
     LT = 274,
     GT = 275,
     EQ = 276,
     PLUS_OP = 277,
     MULT_OP = 278,
     SUB_OP = 279,
     DIV_OP = 280,
     EXPONENT = 281,
     LPAREN = 282,
     RPAREN = 283,
     LBRACKET = 284,
     RBRACKET = 285,
     LBRACE = 286,
     RBRACE = 287,
     NUMBER = 288,
     FLOAT_NUM = 289,
     STRINGLITERAL = 290,
     CHARLITERAL = 291,
     ID = 292
   };
#endif
/* Tokens.  */
#define CHAR 258
#define INT 259
#define FLOAT 260
#define VOID 261
#define IF 262
#define ELSE 263
#define WHILE 264
#define WRITE 265
#define RETURN 266
#define COMMA 267
#define SEMICOLON 268
#define NEWLINECHAR 269
#define DOUBLE_EQ 270
#define NOT_EQ 271
#define LT_EQ 272
#define GT_EQ 273
#define LT 274
#define GT 275
#define EQ 276
#define PLUS_OP 277
#define MULT_OP 278
#define SUB_OP 279
#define DIV_OP 280
#define EXPONENT 281
#define LPAREN 282
#define RPAREN 283
#define LBRACKET 284
#define RBRACKET 285
#define LBRACE 286
#define RBRACE 287
#define NUMBER 288
#define FLOAT_NUM 289
#define STRINGLITERAL 290
#define CHARLITERAL 291
#define ID 292




/* Copy the first part of user declarations.  */
#line 1 "parser.y"


// import libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>

// import all accessory files
#include "symbolTable.h"
#include "AST.h"
#include "IRcode.h"
#include "assembly.h"
#include "calculator.h"
#include "ctype.h"

// flex
extern int yylex();
extern int yyparse();
extern FILE* yyin;
void yyerror(const char* s);

// static value definitions for easier readability when determining what is running loop and if statement-wise
#define IN_ELSE_BLOCK 0 // inside else statement
#define IN_IF_BLOCK 1 // inside if statement

#define RUN_ELSE_BLOCK 0 // will run else block
#define RUN_IF_BLOCK 1 // will run if block

#define UPDATE_IF_ELSE 0 // will update the if-else
#define UPDATE_WHILE 1 // will update the while loop

// static value definitions for ir code and mips file choices to print to
#define IR_CODE 0 // (default) main
#define IR_FUNC 1 // functions/loops
#define TEMP_MIPS 0  // (default) middle section, main:
#define MIPS_CODE 1  // top section, var decls
#define MIPS_FUNC 2  // bottom section for functions/while loops

// various variables for tracking
char currentScope[50]; /* global or the name of the function */
char IDArg[50]; // if an argument is an ID, it's name is temporarily stored here
int argIsID = 0; // boolean to determine if an argument is an ID
int argCounter = 0; // how many arguments there are
char *args[50]; // argument array, names stored here
char **argptr = args; // argument array pointer

// two different operator chars to hold a current operator
char operator; // holds current operator in math statements
char op; // holds current operator in conditions

// temporary variables to hold two numbers in a binary math statement
char num1[50]; // first number
char num2[50]; // second number

// boolean values for if-else and while loop logic in parser
int runIfElseBlock = 0; // 1 - run if block;  0 - run else block;
int ifElseCurrentBlock = 0; // 1 - in if statment; 0 - in else statement;
int runWhileBlock = 0; // 1 - run while block;  0 - exit while loop
int inElseOrWhile = 0; //boolean flag to determine if runIfElseBlock or runWhileBlock should be updated
					   // 0 - if/else        1 - while

// while loop variables
int numOfWhileLoops = 0; // counter for amount of while loops, used for making name of while loop in mips
char whileName[50]; // name of the while loop, used for naming it in mips
int registerCounter = 0; // counts the registers for parameters in mips

// initialize scope as global and symbol table
char scope[50] = "G"; // set scope to global



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
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

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 75 "parser.y"
{
	int number;
	char character;
	char* string;
	struct AST* ast;
}
/* Line 193 of yacc.c.  */
#line 250 "parser.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 263 "parser.tab.c"

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
# if defined YYENABLE_NLS && YYENABLE_NLS
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
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
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
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  38
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   224

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  103
/* YYNRULES -- Number of states.  */
#define YYNSTATES  196

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    16,    18,
      20,    21,    29,    30,    38,    39,    47,    48,    56,    60,
      62,    63,    66,    69,    72,    76,    78,    79,    81,    83,
      85,    87,    91,    94,    96,    98,   100,   102,   104,   105,
     108,   110,   114,   119,   123,   128,   132,   137,   142,   145,
     147,   149,   154,   162,   166,   170,   177,   181,   184,   192,
     200,   208,   214,   218,   222,   226,   230,   234,   237,   239,
     241,   243,   245,   247,   249,   251,   253,   255,   257,   259,
     261,   263,   265,   267,   269,   271,   273,   279,   285,   292,
     299,   300,   301,   309,   310,   311,   312,   322,   323,   326,
     330,   334,   338,   342
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      39,     0,    -1,    40,    -1,    41,    40,    -1,    41,    -1,
      42,    -1,    55,    -1,    54,    -1,    63,    -1,    66,    -1,
      -1,     6,    37,    27,    43,    47,    28,    51,    -1,    -1,
       4,    37,    27,    44,    47,    28,    51,    -1,    -1,     3,
      37,    27,    45,    47,    28,    51,    -1,    -1,     5,    37,
      27,    46,    47,    28,    51,    -1,    48,    12,    47,    -1,
      48,    -1,    -1,     4,    37,    -1,     5,    37,    -1,     3,
      37,    -1,    50,    12,    49,    -1,    50,    -1,    -1,    33,
      -1,    34,    -1,    36,    -1,    37,    -1,    29,    52,    30,
      -1,    53,    52,    -1,    53,    -1,    55,    -1,    54,    -1,
      63,    -1,    66,    -1,    -1,    56,    54,    -1,    56,    -1,
       4,    37,    13,    -1,    37,    21,    33,    13,    -1,     3,
      37,    13,    -1,    37,    21,    36,    13,    -1,     5,    37,
      13,    -1,    37,    21,    34,    13,    -1,    37,    21,    37,
      13,    -1,    57,    13,    -1,    62,    -1,    13,    -1,    37,
      21,    37,    13,    -1,    37,    21,    37,    27,    49,    28,
      13,    -1,    10,    37,    13,    -1,    10,    35,    13,    -1,
      10,    37,    31,    33,    32,    13,    -1,    10,    14,    13,
      -1,    57,    13,    -1,    37,    31,    33,    32,    21,    33,
      13,    -1,    37,    31,    33,    32,    21,    59,    13,    -1,
      37,    31,    33,    32,    21,    36,    13,    -1,    37,    27,
      49,    28,    13,    -1,    11,    37,    13,    -1,    11,    33,
      13,    -1,    11,    34,    13,    -1,    11,    36,    13,    -1,
      37,    21,    58,    -1,    59,    58,    -1,    59,    -1,    27,
      -1,    28,    -1,    37,    -1,    33,    -1,    34,    -1,    26,
      -1,    60,    -1,    22,    -1,    24,    -1,    23,    -1,    25,
      -1,    15,    -1,    19,    -1,    20,    -1,    17,    -1,    18,
      -1,    16,    -1,     4,    37,    31,    32,    13,    -1,     3,
      37,    31,    32,    13,    -1,     4,    37,    31,    33,    32,
      13,    -1,     3,    37,    31,    33,    32,    13,    -1,    -1,
      -1,     9,    64,    27,    71,    28,    65,    51,    -1,    -1,
      -1,    -1,     7,    67,    27,    71,    28,    68,    51,    69,
      70,    -1,    -1,     8,    51,    -1,    33,    61,    33,    -1,
      37,    61,    37,    -1,    37,    61,    33,    -1,    34,    61,
      34,    -1,    36,    61,    36,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   137,   137,   174,   180,   188,   193,   198,   203,   208,
     216,   216,   243,   243,   270,   270,   297,   297,   326,   332,
     340,   340,   351,   362,   376,   382,   390,   390,   396,   402,
     408,   418,   425,   431,   439,   444,   449,   454,   461,   461,
     467,   477,   510,   575,   607,   675,   709,   774,   816,   825,
     840,   842,   883,   964,  1011,  1039,  1092,  1110,  1119,  1191,
    1237,  1307,  1385,  1440,  1462,  1484,  1509,  1620,  1624,  1629,
    1630,  1631,  1647,  1659,  1660,  1661,  1665,  1666,  1667,  1668,
    1671,  1672,  1673,  1674,  1675,  1676,  1680,  1685,  1690,  1732,
    1774,  1786,  1774,  1800,  1800,  1805,  1800,  1827,  1827,  1829,
    1848,  1948,  1977,  1995
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CHAR", "INT", "FLOAT", "VOID", "IF",
  "ELSE", "WHILE", "WRITE", "RETURN", "COMMA", "SEMICOLON", "NEWLINECHAR",
  "DOUBLE_EQ", "NOT_EQ", "LT_EQ", "GT_EQ", "LT", "GT", "EQ", "PLUS_OP",
  "MULT_OP", "SUB_OP", "DIV_OP", "EXPONENT", "LPAREN", "RPAREN",
  "LBRACKET", "RBRACKET", "LBRACE", "RBRACE", "NUMBER", "FLOAT_NUM",
  "STRINGLITERAL", "CHARLITERAL", "ID", "$accept", "Program", "DeclList",
  "Decl", "FuncDecl", "@1", "@2", "@3", "@4", "ParamDeclList", "ParamDecl",
  "ArgDeclList", "ArgDecl", "Block", "BlockDeclList", "BlockDecl",
  "StmtList", "VarDecl", "Expr", "IDEQExpr", "MathStmt", "Math",
  "Operator", "CompOperator", "ArrDecl", "WhileStmt", "@5", "@6", "IfStmt",
  "@7", "@8", "@9", "ElseStmt", "Condition", 0
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
     285,   286,   287,   288,   289,   290,   291,   292
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    38,    39,    40,    40,    41,    41,    41,    41,    41,
      43,    42,    44,    42,    45,    42,    46,    42,    47,    47,
      48,    48,    48,    48,    49,    49,    50,    50,    50,    50,
      50,    51,    52,    52,    53,    53,    53,    53,    54,    54,
      54,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    57,    58,    58,    59,
      59,    59,    59,    59,    59,    59,    60,    60,    60,    60,
      61,    61,    61,    61,    61,    61,    62,    62,    62,    62,
      64,    65,    63,    67,    68,    69,    66,    70,    70,    71,
      71,    71,    71,    71
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       0,     7,     0,     7,     0,     7,     0,     7,     3,     1,
       0,     2,     2,     2,     3,     1,     0,     1,     1,     1,
       1,     3,     2,     1,     1,     1,     1,     1,     0,     2,
       1,     3,     4,     3,     4,     3,     4,     4,     2,     1,
       1,     4,     7,     3,     3,     6,     3,     2,     7,     7,
       7,     5,     3,     3,     3,     3,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     5,     5,     6,     6,
       0,     0,     7,     0,     0,     0,     9,     0,     2,     3,
       3,     3,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      38,     0,     0,     0,     0,    93,    90,     0,     0,    50,
       0,     0,     2,     4,     5,     7,     6,    38,     0,    49,
       8,     9,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    26,     0,     1,     3,
       0,    39,     0,    48,    43,    14,     0,    41,    12,     0,
      45,    16,    10,     0,     0,    56,    54,    53,     0,    63,
      64,    65,    62,    76,    78,    77,    79,    74,    69,    70,
      72,    73,     0,    71,    66,    68,    75,    27,    28,    29,
      30,     0,    25,     0,     0,    57,    20,     0,     0,    20,
       0,     0,    20,    20,     0,     0,     0,     0,     0,     0,
       0,    42,    46,    44,    47,    26,    72,    73,    71,    67,
       0,    26,     0,    71,     0,     0,     0,     0,    19,    87,
       0,     0,    86,     0,     0,     0,    80,    85,    83,    84,
      81,    82,     0,     0,     0,     0,    94,    91,     0,     0,
      61,    24,     0,    51,    23,    21,    22,     0,    20,    89,
       0,    88,     0,     0,    99,   102,   103,   101,   100,     0,
       0,    55,     0,     0,     0,     0,    38,    15,    18,    13,
      17,    11,    95,    92,    52,    58,    60,    59,     0,     0,
       0,     0,    33,    35,    34,    36,    37,    97,     0,     0,
       0,    31,    32,     0,    96,    98
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    11,    12,    13,    14,    93,    89,    86,    92,   117,
     118,    81,    82,   167,   181,   182,    15,    16,    17,    18,
      74,    75,    76,   132,    19,    20,    27,   160,    21,    26,
     159,   187,   194,    98
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -145
static const yytype_int16 yypact[] =
{
      14,   -35,   -25,   -23,    -6,  -145,  -145,     8,   109,  -145,
     103,    61,  -145,    14,  -145,  -145,  -145,     0,    20,  -145,
    -145,  -145,    13,    26,    50,    40,    49,    55,    81,    85,
      28,    98,   113,   120,   131,    47,   114,    94,  -145,  -145,
     104,  -145,   141,  -145,  -145,  -145,    23,  -145,  -145,    82,
    -145,  -145,  -145,   119,   119,  -145,  -145,  -145,   127,  -145,
    -145,  -145,  -145,  -145,  -145,  -145,  -145,  -145,  -145,  -145,
     148,   149,   150,    65,  -145,    79,  -145,  -145,  -145,  -145,
    -145,    67,   152,   134,    95,  -145,   105,   154,   136,   105,
     156,   138,   105,   105,   121,   121,   121,   121,   143,   144,
     142,  -145,  -145,  -145,  -145,   114,  -145,  -145,  -145,  -145,
     160,   114,   155,    66,   140,   145,   146,   147,   166,  -145,
     167,   151,  -145,   168,   157,   158,  -145,  -145,  -145,  -145,
    -145,  -145,   159,   153,   161,   -30,  -145,  -145,   171,   162,
    -145,  -145,    63,  -145,  -145,  -145,  -145,   164,   105,  -145,
     164,  -145,   164,   164,  -145,  -145,  -145,  -145,  -145,   164,
     164,  -145,   175,   176,   178,   181,    25,  -145,  -145,  -145,
    -145,  -145,  -145,  -145,  -145,  -145,  -145,  -145,   163,   165,
     169,   173,    25,  -145,  -145,  -145,  -145,   187,    33,    34,
     183,  -145,  -145,   164,  -145,  -145
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -145,  -145,   185,  -145,  -145,  -145,  -145,  -145,  -145,   -88,
    -145,   -57,  -145,  -144,    17,  -145,   -17,  -124,  -145,   184,
     129,    68,  -145,    62,  -145,  -116,  -145,  -145,  -114,  -145,
    -145,  -145,  -145,   170
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      41,   121,    22,   157,   124,   125,   169,   158,   170,   171,
       7,     8,    23,     9,    24,   172,   173,     1,     2,     3,
       4,     5,    28,     6,     7,     8,    44,     9,   178,   179,
     180,    25,     5,    43,     6,     7,     8,    40,     9,    47,
      45,    57,   184,    29,    46,    30,    44,    47,   139,   195,
     185,    10,   186,    48,   141,    87,    88,    49,   184,    58,
     168,    38,    10,    50,    46,    49,   185,    52,   186,    63,
      64,    65,    66,    67,    68,    69,    53,    51,   104,   143,
      70,    71,    54,    72,    73,    63,    64,    65,    66,    67,
      68,    69,   105,   105,    55,   110,   163,   107,    56,   164,
     108,    63,    64,    65,    66,    67,    68,    69,   114,   115,
     116,    59,   106,   107,    90,    91,   108,    63,    64,    65,
      66,    67,    68,    69,    35,    84,    60,    83,   106,   107,
      36,    36,   113,    61,    37,    37,   126,   127,   128,   129,
     130,   131,    31,    32,    62,    33,    34,    77,    78,   183,
      79,    80,    94,    95,    85,    96,    97,   133,   134,   135,
     100,   101,   102,   103,   111,   183,   112,   119,   120,   122,
     123,   136,   137,   140,   138,   147,   142,   144,   148,   150,
     149,   151,   145,   146,   161,   152,   153,   155,   174,   175,
     162,   176,   154,   166,   177,   193,    50,   156,    39,   192,
     188,    42,   189,   191,   109,     0,   190,     0,     0,     0,
     165,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    99
};

static const yytype_int16 yycheck[] =
{
      17,    89,    37,    33,    92,    93,   150,    37,   152,   153,
      10,    11,    37,    13,    37,   159,   160,     3,     4,     5,
       6,     7,    14,     9,    10,    11,    13,    13,     3,     4,
       5,    37,     7,    13,     9,    10,    11,    37,    13,    13,
      27,    13,   166,    35,    31,    37,    13,    13,   105,   193,
     166,    37,   166,    27,   111,    32,    33,    31,   182,    31,
     148,     0,    37,    13,    31,    31,   182,    27,   182,    22,
      23,    24,    25,    26,    27,    28,    27,    27,    13,    13,
      33,    34,    27,    36,    37,    22,    23,    24,    25,    26,
      27,    28,    27,    27,    13,    28,    33,    34,    13,    36,
      37,    22,    23,    24,    25,    26,    27,    28,     3,     4,
       5,    13,    33,    34,    32,    33,    37,    22,    23,    24,
      25,    26,    27,    28,    21,    21,    13,    33,    33,    34,
      27,    27,    37,    13,    31,    31,    15,    16,    17,    18,
      19,    20,    33,    34,    13,    36,    37,    33,    34,   166,
      36,    37,    33,    34,    13,    36,    37,    95,    96,    97,
      33,    13,    13,    13,    12,   182,    32,    13,    32,    13,
      32,    28,    28,    13,    32,    28,    21,    37,    12,    28,
      13,    13,    37,    37,    13,    28,    28,    34,    13,    13,
      28,    13,    33,    29,    13,     8,    13,    36,    13,   182,
      37,    17,    37,    30,    75,    -1,    37,    -1,    -1,    -1,
     142,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     9,    10,    11,    13,
      37,    39,    40,    41,    42,    54,    55,    56,    57,    62,
      63,    66,    37,    37,    37,    37,    67,    64,    14,    35,
      37,    33,    34,    36,    37,    21,    27,    31,     0,    40,
      37,    54,    57,    13,    13,    27,    31,    13,    27,    31,
      13,    27,    27,    27,    27,    13,    13,    13,    31,    13,
      13,    13,    13,    22,    23,    24,    25,    26,    27,    28,
      33,    34,    36,    37,    58,    59,    60,    33,    34,    36,
      37,    49,    50,    33,    21,    13,    45,    32,    33,    44,
      32,    33,    46,    43,    33,    34,    36,    37,    71,    71,
      33,    13,    13,    13,    13,    27,    33,    34,    37,    58,
      28,    12,    32,    37,     3,     4,     5,    47,    48,    13,
      32,    47,    13,    32,    47,    47,    15,    16,    17,    18,
      19,    20,    61,    61,    61,    61,    28,    28,    32,    49,
      13,    49,    21,    13,    37,    37,    37,    28,    12,    13,
      28,    13,    28,    28,    33,    34,    36,    33,    37,    68,
      65,    13,    28,    33,    36,    59,    29,    51,    47,    51,
      51,    51,    51,    51,    13,    13,    13,    13,     3,     4,
       5,    52,    53,    54,    55,    63,    66,    69,    37,    37,
      37,    30,    52,     8,    70,    51
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
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
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
      case 37: /* "ID" */
#line 126 "parser.y"
	{ fprintf(yyoutput, "%s", (yyvaluep->string)); };
#line 972 "parser.tab.c"
	break;
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
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

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
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
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
#line 137 "parser.y"
    {
		// ast
		(yyval.ast) = (yyvsp[(1) - (1)].ast);

		// output the start of the ast
		printf("\n\n ########################" RESET);
		printf(BPINK " AST STARTED " RESET);
		printf("######################### \n\n" RESET);

		// print the ast
		//printAST($$,0);

		// output the end of the ast
		printf("\n\n #########################" RESET);
		printf(PINK " AST ENDED " RESET);
		printf("########################## \n\n" RESET);

		// append the two ir code files to each other
		appendFiles("IRFuncs.ir", "IRcode.ir");

		// end mips code
		addEndLoop(); // add the endloop function to the bottom of mips for any loops to jump to to get to main
		createEndOfAssemblyCode(); // add the end line of mips to kill the program

		// append the three mips files to each other
		appendFiles("tempMIPS.asm", "MIPScode.asm");
		printf("\n");
		appendFiles("MIPSfuncs.asm", "MIPScode.asm");

		// output that mips was generated
		printf("\n\n #######################" RESET);
		printf(BPINK " MIPS GENERATED " RESET);
		printf("####################### \n\n" RESET);

;}
    break;

  case 3:
#line 174 "parser.y"
    {

				// ast
				(yyvsp[(1) - (2)].ast)->left = (yyvsp[(2) - (2)].ast);
				(yyval.ast) = (yyvsp[(1) - (2)].ast);

			;}
    break;

  case 4:
#line 180 "parser.y"
    {

				// ast
				(yyval.ast) = (yyvsp[(1) - (1)].ast);

;}
    break;

  case 5:
#line 188 "parser.y"
    { // function declaration

			// ast
			(yyval.ast) = (yyvsp[(1) - (1)].ast);

		;}
    break;

  case 6:
#line 193 "parser.y"
    { // variable declaration

			// ast
			(yyval.ast) = (yyvsp[(1) - (1)].ast);

		;}
    break;

  case 7:
#line 198 "parser.y"
    { // statement declaration list

			// ast
			(yyval.ast) = (yyvsp[(1) - (1)].ast);

		;}
    break;

  case 8:
#line 203 "parser.y"
    { // while statement declaration
			
			// ast
			(yyval.ast) = (yyvsp[(1) - (1)].ast);
	
		;}
    break;

  case 9:
#line 208 "parser.y"
    { // if statement declaration

			// ast
			(yyval.ast) = (yyvsp[(1) - (1)].ast);
	
;}
    break;

  case 10:
#line 216 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: Void Function Initialization \n\n" RESET); // void function declaration
								
								// symbol table
								symTabAccess(); // access symbol table
								addSymbolTable((yyvsp[(2) - (3)].string),"VOID"); // add void function to symbol table
								strcpy(scope,(yyvsp[(2) - (3)].string)); // set scope to function name

								// ir code
								createFunctionHeader((yyvsp[(2) - (3)].string)); // create function
								changeIRFile(IR_FUNC); // change file to print block to the function IR code file

								// mips
								createMIPSFunction((yyvsp[(2) - (3)].string)); // create function
	
							// second part of the function, including parameter list, right parentheses, and block
							;}
    break;

  case 11:
#line 231 "parser.y"
    { printf(BGREEN "\nVoid Function End.\n" RESET); // void function end

								// ast
								(yyval.ast) = AST_assignment("FNC",(yyvsp[(1) - (7)].string),(yyvsp[(2) - (7)].string)); // add the function to the ast

								// ir code
								changeIRFile(IR_CODE); // change file back to main file

								// mips
								endMIPSFunction(); // end function in mips
						

						;}
    break;

  case 12:
#line 243 "parser.y"
    {printf(GRAY "RECOGNIZED RULE: Integer Function Initialization \n\n" RESET); // int function declaration

								// symbol table
								symTabAccess(); // access symbol table
								addSymbolTable((yyvsp[(2) - (3)].string),"INT"); // add int function to symbol table
								strcpy(scope,(yyvsp[(2) - (3)].string)); // set scope to function name

								// ir code
								createFunctionHeader((yyvsp[(2) - (3)].string)); // create function
								changeIRFile(IR_FUNC); // change file to print block to the function IR code file

								// mips
								createMIPSFunction((yyvsp[(2) - (3)].string)); // create function
						 
						 	// second part of the function, including parameter list, right parentheses, and block
						 	;}
    break;

  case 13:
#line 258 "parser.y"
    { printf(BGREEN "\nInt Function End.\n" RESET); // void function end

								// ast
								(yyval.ast) = AST_assignment("FNC",(yyvsp[(1) - (7)].string),(yyvsp[(2) - (7)].string)); // add the function to the ast

								// ir code
								changeIRFile(IR_CODE); // change file back to main file

								// mips code
								endMIPSFunction(); // end function in mips

						
						;}
    break;

  case 14:
#line 270 "parser.y"
    {printf(GRAY "RECOGNIZED RULE: Char Function Initialization \n\n" RESET); // char function declaration

								// symbol table
								symTabAccess(); // access symbol table
								addSymbolTable((yyvsp[(2) - (3)].string),"CHR"); // add char function to symbol table
								strcpy(scope,(yyvsp[(2) - (3)].string)); // set scope to function name

								// ir code
								createFunctionHeader((yyvsp[(2) - (3)].string)); // create function
								changeIRFile(IR_FUNC); // change file to print block to the function IR code file

								// mips
								createMIPSFunction((yyvsp[(2) - (3)].string)); // create function
						 
						 	// second part of the function, including parameter list, right parentheses, and block
							;}
    break;

  case 15:
#line 285 "parser.y"
    { printf(BGREEN "\nChar Function End.\n" RESET); // char function end

								// ast
								(yyval.ast) = AST_assignment("FNC",(yyvsp[(1) - (7)].string),(yyvsp[(2) - (7)].string)); // add the function to the ast

								// ir code
								changeIRFile(IR_CODE); // change file back to main file

								// mips
								endMIPSFunction(); // end function in mips

						
						;}
    break;

  case 16:
#line 297 "parser.y"
    {printf(GRAY "RECOGNIZED RULE: Float Function Initialization \n\n" RESET); // float function declaration

								// symbol table
								symTabAccess(); // access symbol table
								addSymbolTable((yyvsp[(2) - (3)].string),"FLT"); // add float function to symbol table
								strcpy(scope,(yyvsp[(2) - (3)].string)); // set scope to function name

								// ir code
								createFunctionHeader((yyvsp[(2) - (3)].string)); // create function
								changeIRFile(IR_FUNC); // change file to print block to the function IR code file

								// mips
								createMIPSFunction((yyvsp[(2) - (3)].string)); // create function
								
							// second part of the function, including parameter list, right parentheses, and block
						 	;}
    break;

  case 17:
#line 312 "parser.y"
    { printf(BGREEN "\nFloat Function End.\n" RESET); // float function end

								// ast
								(yyval.ast) = AST_assignment("FNC",(yyvsp[(1) - (7)].string),(yyvsp[(2) - (7)].string)); // add the function to the ast

								// ir code
								changeIRFile(IR_CODE); // change file back to main file

								// mips
								endMIPSFunction(); // end function in mips
 
;}
    break;

  case 18:
#line 326 "parser.y"
    { // list of parameters separated by commas

					// ast
					(yyvsp[(1) - (3)].ast)->left = (yyvsp[(2) - (3)].string);
					(yyval.ast) = (yyvsp[(1) - (3)].ast);

				;}
    break;

  case 19:
#line 332 "parser.y"
    { // or single parameter

					// ast
					(yyval.ast) = (yyvsp[(1) - (1)].ast);

				;}
    break;

  case 21:
#line 340 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: Integer Parameter Initialization \n\n" RESET); // integer parameter declaration

					// symbol table
					addItem((yyvsp[(2) - (2)].string),"PAR","INT",scope,0); // add integer parameter to symbol table

					// ir code
					printf(BLUE "IR Code" RESET);
					printf(RED " NOT " RESET);
					printf(BLUE "Created.\n" RESET);


				;}
    break;

  case 22:
#line 351 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: Float Parameter Initialization \n\n" RESET); // float parameter declaration

					// symbol table
					addItem((yyvsp[(2) - (2)].string),"PAR","FLT",scope,0); // add float parameter to symbol table

					// ir code
					printf(BLUE "IR Code" RESET);
					printf(RED " NOT " RESET);
					printf(BLUE "Created.\n" RESET);


				;}
    break;

  case 23:
#line 362 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: Char Parameter Initialization \n\n" RESET); // char parameter declaration

					// symbol table
					addItem((yyvsp[(2) - (2)].string),"PAR","CHR",scope,0); // add char parameter to symbol table

					// ir code
					printf(BLUE "IR Code" RESET);
					printf(RED " NOT " RESET);
					printf(BLUE "Created.\n" RESET);
					

;}
    break;

  case 24:
#line 376 "parser.y"
    { // recursive list of arguments

					// ast
					(yyvsp[(1) - (3)].ast)->left = (yyvsp[(2) - (3)].string);
					(yyval.ast) = (yyvsp[(1) - (3)].ast);

				;}
    break;

  case 25:
#line 382 "parser.y"
    { // or single argument

					// ast
					(yyval.ast) = (yyvsp[(1) - (1)].ast);

				;}
    break;

  case 27:
#line 390 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: Parameter = %s\n\n" RESET, (yyvsp[(1) - (1)].string)); // number argument

				argptr[argCounter] = (yyvsp[(1) - (1)].string); // add number to argument array
				argCounter++; // increment argument counter


			;}
    break;

  case 28:
#line 396 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: Parameter = %s\n\n" RESET, (yyvsp[(1) - (1)].string)); // float argument

				argptr[argCounter] = (yyvsp[(1) - (1)].string); // add float number to argument array
				argCounter++; // increment argument counter


			;}
    break;

  case 29:
#line 402 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: Parameter = %s\n\n" RESET, (yyvsp[(1) - (1)].string)); // char argument

				argptr[argCounter] = (yyvsp[(1) - (1)].string); // add char to argument array
				argCounter++; // increment argument counter
				

			;}
    break;

  case 30:
#line 408 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: Parameter = %s\n\n" RESET, getValue((yyvsp[(1) - (1)].string), "G")); // id argument

				argptr[argCounter] = getValue((yyvsp[(1) - (1)].string), "G"); // add id value to argument array
				strcpy(IDArg, (yyvsp[(1) - (1)].string)); // copy the name of the id into temporary IDArg variable
				argIsID = 1; // set flag so it knows the parameter is an ID, not a number
				argCounter++; // increment argument counter

;}
    break;

  case 31:
#line 418 "parser.y"
    { // blockDeclList is the recursive list of statements inside the block

	strcpy(scope,"G"); // reset scope back to global after statements are parsed

;}
    break;

  case 32:
#line 425 "parser.y"
    { // recursive list of statements

				// ast
				(yyvsp[(1) - (2)].ast)->left = (yyvsp[(2) - (2)].ast);
				(yyval.ast) = (yyvsp[(1) - (2)].ast);

		;}
    break;

  case 33:
#line 431 "parser.y"
    { // or single statement

				// ast
				(yyval.ast) = (yyvsp[(1) - (1)].ast);

;}
    break;

  case 34:
#line 439 "parser.y"
    { // variable declaration

		   // ast
		   (yyval.ast) = (yyvsp[(1) - (1)].ast);

		;}
    break;

  case 35:
#line 444 "parser.y"
    { // statement list

			// ast
			(yyval.ast) = (yyvsp[(1) - (1)].ast);

		;}
    break;

  case 36:
#line 449 "parser.y"
    { // while loop

			//ast
			(yyval.ast) = (yyvsp[(1) - (1)].ast);
		
		;}
    break;

  case 37:
#line 454 "parser.y"
    { // if statement
			// ast
			(yyval.ast) = (yyvsp[(1) - (1)].ast);

;}
    break;

  case 39:
#line 461 "parser.y"
    { // nothing or recursive list of statements
				
				// ast
				(yyvsp[(1) - (2)].ast)->left = (yyvsp[(2) - (2)].ast); 
				(yyval.ast) = (yyvsp[(1) - (2)].ast);
			
			;}
    break;

  case 40:
#line 467 "parser.y"
    { // or single expression
				
				// ast
				(yyval.ast) = (yyvsp[(1) - (1)].ast);
		
;}
    break;

  case 41:
#line 477 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: Integer Variable Declaration\n\n" RESET);	// e.g. int x;

						if (ifElseCurrentBlock == runIfElseBlock) { // if we are in an if block, both are 1, if we are in an else block, both are 0

							// semantic checks
								// is the variable already declared?
								symTabAccess(); // access symbol table
								if (found((yyvsp[(2) - (3)].string),scope) == 1) { // if we find the variable in the symbol table
									printf(RED "\nERROR: Variable '%s' already declared.\n" RESET,(yyvsp[(2) - (3)].string)); // error message
									exit(0); // exit program
								}

							// symbol table
							addItem((yyvsp[(2) - (3)].string), "VAR", "INT", scope, 0); // add variable to the correct symbol table based on scope

							// ast
							(yyval.ast) = AST_assignment("TYPE",(yyvsp[(1) - (3)].string),(yyvsp[(2) - (3)].string)); // add variable to ast

							// ir code
							createIntDefinition((yyvsp[(2) - (3)].string), scope); // create ir code: T0 = x

							// mips code 
							createMIPSIntDecl((yyvsp[(2) - (3)].string),scope); // create mips: Gx: .word 0
							
							// code optimization
								// N/A

							/*
										VarDecl
									INT        ID
							*/
						}
				
			;}
    break;

  case 42:
#line 510 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: Integer Variable Initialization \n\n" RESET); // e.g. x = 1;

						if (ifElseCurrentBlock == runIfElseBlock) { // if we are in an if block, both are 1, if we are in an else block, both are 0

							// semantic checks
								// is the variable already declared
								symTabAccess(); // access symbol table
								if (scope == "G") { // if the scope is global
									if (found((yyvsp[(1) - (4)].string),scope) == 0) { // if we don't find the variable in the global symbol table
										printf(RED "\n::::> CHECK FAILED: Variable '%s' not initialized in the global scope.\n\n" RESET,(yyvsp[(1) - (4)].string)); // error message
										exit(0); // exit program
									}
								} 
								else { // else the scope is function
									if (found((yyvsp[(1) - (4)].string),scope) == 0) { // if we don't find the variable in the function symbol table
										if (found((yyvsp[(1) - (4)].string), "G") == 0) { // if the variable is not found in the global scope
											showSymTable(); // show the symbol tables
											printf(RED "\n::::> CHECK FAILED: Variable '%s' not initialized in the function or global scope.\n\n" RESET,(yyvsp[(1) - (4)].string)); // error message
											exit(0); // exit program
										}
									}
								}

								// is the statement redundant
								if (redundantValue((yyvsp[(1) - (4)].string), scope, (yyvsp[(3) - (4)].string)) == 0) { // if statement is redundant
									printf(RED "::::> CHECK FAILED: Variable %s has already been declared as: %s.\n\n" RESET,(yyvsp[(1) - (4)].string),(yyvsp[(3) - (4)].string)); // error message
									exit(0); // exit program
								}

							// symbol table
							if (strcmp(scope, "G") != 0) { // if scope is in function

								if (found((yyvsp[(1) - (4)].string), scope) == 1) { // if the variable is found in the function's sym table

									updateValue((yyvsp[(1) - (4)].string), scope, (yyvsp[(3) - (4)].string)); // update value in function sym table

								} else if (found((yyvsp[(1) - (4)].string), "G") == 1) { // if the variable is found in the global scope

									updateValue((yyvsp[(1) - (4)].string), "G", (yyvsp[(3) - (4)].string)); // update value in global sym table

								}

							} else { // if scope is global
								updateValue((yyvsp[(1) - (4)].string), scope, (yyvsp[(3) - (4)].string)); // update value normally
							}

							// ast
							(yyval.ast) = AST_BinaryExpression("=",(yyvsp[(1) - (4)].string),(yyvsp[(3) - (4)].string)); // add binary expression to the ast

							// ir code
							createIntAssignment((yyvsp[(1) - (4)].string), (yyvsp[(3) - (4)].string), scope); // create ir code: T0 = 1

							// mips code
							createMIPSIntAssignment((yyvsp[(1) - (4)].string), (yyvsp[(3) - (4)].string), scope); // create mips code for int assignment

							// code optimization
								// N/A

							/*
									=
								ID    NUMBER
							*/

						}

			;}
    break;

  case 43:
#line 575 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: Char Variable Declaration \n\n" RESET); // e.g. char c;

						if (ifElseCurrentBlock == runIfElseBlock) { // if we are in an if block, both are 1, if we are in an else block, both are 0
							// semantic checks
								// is the variable already declared?
								symTabAccess(); // access symbol table
								if (found((yyvsp[(2) - (3)].string),scope) == 1) { // if we find the variable in the symbol table
									exit(0); // variable already declared
								}

							// symbol table	
							addItem((yyvsp[(2) - (3)].string), "VAR", "CHR", scope, 0); // add char variable to the symbol table

							// ast
							(yyval.ast) = AST_assignment("TYPE",(yyvsp[(1) - (3)].string),(yyvsp[(2) - (3)].string)); // add char variable to the ast

							// ir code
							createCharDefinition((yyvsp[(2) - (3)].string), scope); // create ir code: T1 = c

							// mips
							printf(CYAN "MIPS Not Needed.\n\n\n" RESET); // mips currently not needed
							
							// code optimization
								// N/A

							/*
									VarDecl
								CHAR	   ID
							*/	

						}				
			
			;}
    break;

  case 44:
#line 607 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: Char Variable Initialization \n\n" RESET); // e.g. c = 'a';	

						if (ifElseCurrentBlock == runIfElseBlock) { // if we are in an if block, both are 1, if we are in an else block, both are 0

							// remove apostrophes from charliteral
							char* str = removeApostrophes((yyvsp[(3) - (4)].string)); // symbol table function to return char without apostrophes

							// semantic checks
								// is the variable already declared?
								symTabAccess(); // access symbol table
								if (scope == "G") { // if the scope is global
									if (found((yyvsp[(1) - (4)].string),scope) == 0) { // if the variable is not found in the global scope
										printf(RED "\n::::> CHECK FAILED: Variable '%s' not initialized in the global scope.\n\n" RESET,(yyvsp[(1) - (4)].string)); // error message
										exit(0); // exit program
									}
								}
								else { // else we are in function scope
									if (found((yyvsp[(1) - (4)].string),scope) == 0) { // if the variable is not found in the function scope
										if (found((yyvsp[(1) - (4)].string), "G") == 0) { // if the variable is not found in the global scope
											showSymTable(); // access symbol table
											printf(RED "\n::::> CHECK FAILED: Variable '%s' not initialized in the function or global scope.\n\n" RESET,(yyvsp[(1) - (4)].string)); // error message
											exit(0); // exit program
										}
									}
								}

								// is the statement redundant
								if (redundantValue((yyvsp[(1) - (4)].string), scope, str) == 0) { // if statement is redundant
									printf(RED "::::> CHECK FAILED: Variable '%s' has already been declared as: %s.\n\n" RESET,(yyvsp[(1) - (4)].string),(yyvsp[(3) - (4)].string)); // error message
									exit(0); // exit the program
								}

							// symbol table
							if (strcmp(scope, "G") != 0) { // if scope is in function

								if (found((yyvsp[(1) - (4)].string), scope) == 1) { // if the variable is found in the function's sym table

									updateValue((yyvsp[(1) - (4)].string), scope, str); // update value in function sym table

								} else if (found((yyvsp[(1) - (4)].string), "G") == 1) { // if the variable is found in the global scope

									updateValue((yyvsp[(1) - (4)].string), "G", str); // update value in global sym table

								}

							} else { // if scope is global
								updateValue((yyvsp[(1) - (4)].string), scope, str); // update value normally
							}
							
							// ast
							(yyval.ast) = AST_BinaryExpression("=",(yyvsp[(1) - (4)].string),str); // add binary expression to ast

							// ir code
							createCharAssignment((yyvsp[(1) - (4)].string), str, scope); // create it code: T1 = 'a'

							// mips code
							createMIPSCharAssignment((yyvsp[(1) - (4)].string), str, scope); // create mips

							// code optimization
								// N/A

							/*
									=
								ID	   CHARLITERAL
							*/

						}

			;}
    break;

  case 45:
#line 675 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: Float Variable Declaration\n\n" RESET);	// e.g. float f;

						if (ifElseCurrentBlock == runIfElseBlock) { // if we are in an if block, both are 1, if we are in an else block, both are 0

							// semantic checks
								// is the variable already declared?
								symTabAccess(); // access symbol table
								if (found((yyvsp[(2) - (3)].string),scope) == 1) { // if the variable is found in the symbol table
									printf(RED "\nERROR: Variable '%s' already declared.\n" RESET,(yyvsp[(2) - (3)].string)); // error message
									exit(0); // exit program
								}

							// symbol table
							addItem((yyvsp[(2) - (3)].string), "VAR", "FLT", scope, 0); // add the float variable to the symbol table

							// ast
							(yyval.ast) = AST_assignment("TYPE",(yyvsp[(1) - (3)].string),(yyvsp[(2) - (3)].string)); // add the float variable to the ast

							// ir code
							createFloatDefinition((yyvsp[(2) - (3)].string), scope); // create ir code: T2 = f

							// mips code
							printf(CYAN "MIPS Not Needed.\n\n\n" RESET); // mips currently not necessary
							
							// code optimization
								// N/A

							/*
										VarDecl
									INT        ID
							*/

						}

				;}
    break;

  case 46:
#line 709 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: Float Variable Initialization \n\n" RESET); // e.g. f = 1.0;
							
						if (ifElseCurrentBlock == runIfElseBlock) { // if we are in an if block, both are 1, if we are in an else block, both are 0

							// semantic checks
								// is the variable already declared
								symTabAccess(); // access symbol table
								if (scope == "G") { // if the scope is global
									if (found((yyvsp[(1) - (4)].string),scope) == 0) { // if the variable is not found in the global scope
										printf(RED "\n::::> CHECK FAILED: Variable '%s' not initialized in the global scope.\n\n" RESET,(yyvsp[(1) - (4)].string)); // error message
										exit(0); // exit program
									}
								} 
								else { // else the scope is function
									if (found((yyvsp[(1) - (4)].string),scope) == 0) { // if the variable is not found in the function scope
										if (found((yyvsp[(1) - (4)].string), "G") == 0) { // if the variable is not found in the global scope
											showSymTable(); // show the symbol table
											printf(RED "\n::::> CHECK FAILED: Variable '%s' not initialized in the function or global scope.\n\n" RESET,(yyvsp[(1) - (4)].string)); // error message
											exit(0); // exit program
										}
									}
								}

								// is the statement redundant
								if (redundantValue((yyvsp[(1) - (4)].string), scope, (yyvsp[(3) - (4)].string)) == 0) { // if statement is redundant
									printf(RED "\n::::> CHECK FAILED: Variable '%s' has already been declared as: %s.\n\n" RESET,(yyvsp[(1) - (4)].string),(yyvsp[(3) - (4)].string)); // error message
									exit(0); // exit program
								}

							// symbol table
							if (strcmp(scope, "G") != 0) { // if scope is in function

								if (found((yyvsp[(1) - (4)].string), scope) == 1) { // if the variable is found in the function's sym table

									updateValue((yyvsp[(1) - (4)].string), scope, (yyvsp[(3) - (4)].string)); // update value in function sym table

								} else if (found((yyvsp[(1) - (4)].string), "G") == 1) { // if the variable is found in the global scope

									updateValue((yyvsp[(1) - (4)].string), "G", (yyvsp[(3) - (4)].string)); // update value in global sym table

								}

							} else { // if scope is global
								updateValue((yyvsp[(1) - (4)].string), scope, (yyvsp[(3) - (4)].string)); // update value normally
							}

							// ast
							(yyval.ast) = AST_BinaryExpression("=",(yyvsp[(1) - (4)].string),(yyvsp[(3) - (4)].string)); // add float variable to ast

							// ir code
							createFloatAssignment((yyvsp[(1) - (4)].string),(yyvsp[(3) - (4)].string), scope); // create ir code: T3 = 1.0

							// mips code
							createMIPSFloatAssignment((yyvsp[(1) - (4)].string), (yyvsp[(3) - (4)].string), scope); // create mips

							// code optimization
								// N/A

							/*
									=
								ID    NUMBER
							*/

						}

				;}
    break;

  case 47:
#line 774 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: Assignment Statement\n\n" RESET); // e.g. x = y;

					if (ifElseCurrentBlock == runIfElseBlock) { // if we are in an if block, both are 1, if we are in an else block, both are 0

						// semantic checks
							// are both variables already declared?
							symTabAccess(); // access symbol table
							printf("\n"); // print newline
							if (found((yyvsp[(1) - (4)].string),scope) == 0 || found((yyvsp[(3) - (4)].string),scope) == 0) { // if both variables are not found in the scope
								printf(RED "\nERROR: Variable %s or %s not declared.\n\n" RESET,(yyvsp[(1) - (4)].string),(yyvsp[(3) - (4)].string)); // error message
								exit(0); // exit program
							}

							// does the second id have a value?
							//initialized($3, scope);

							// are the id's both variables?
							//compareKinds($1, $3, scope);

							// are the types of the id's the same
							compareTypes((yyvsp[(1) - (4)].string), (yyvsp[(3) - (4)].string), scope);

						// symbol table
						updateValue((yyvsp[(1) - (4)].string), scope, getValue((yyvsp[(3) - (4)].string), scope)); // update the value of the first id in the symbol table

						// ast
						(yyval.ast) = AST_BinaryExpression("=",(yyvsp[(1) - (4)].string),(yyvsp[(3) - (4)].string)); // add expression to the ast

						// ir code
						createIDtoIDAssignment((yyvsp[(1) - (4)].string), (yyvsp[(3) - (4)].string), scope); // create ir code: T0 = T1

						// mips code
						createMIPSIDtoIDAssignment((yyvsp[(1) - (4)].string), (yyvsp[(3) - (4)].string), scope); // create mips

						// code optimization
							// mark the two id's as used
							isUsed((yyvsp[(1) - (4)].string), scope);
							isUsed((yyvsp[(3) - (4)].string), scope);

					}


				;}
    break;

  case 48:
#line 816 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: Addition Statement\n\n" RESET); // id = math statement, e.g. x = 10 - 8;

					if (ifElseCurrentBlock == runIfElseBlock) { // if we are in an if block, both are 1, if we are in an else block, both are 0

						// ast
						(yyval.ast) = (yyvsp[(1) - (2)].ast);

					}

				;}
    break;

  case 49:
#line 825 "parser.y"
    { // array declaration

;}
    break;

  case 50:
#line 840 "parser.y"
    {  // just a semicolon

	;}
    break;

  case 51:
#line 842 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: Assignment Statement\n\n" RESET); // e.g. x = y like above, but can also be present in a stmtList

		if (ifElseCurrentBlock == runIfElseBlock) { // if we are in an if block, both are 1, if we are in an else block, both are 0

			// semantic checks
				// are both variables already declared?
				symTabAccess(); // access symbole table
				printf("\n"); // print newline
				if (found((yyvsp[(1) - (4)].string),scope) == 0 || found((yyvsp[(3) - (4)].string),scope) == 0) { // if both variables are not found in the scope
					printf(RED "\nERROR: Variable %s or %s not declared.\n\n" RESET,(yyvsp[(1) - (4)].string),(yyvsp[(3) - (4)].string)); // error message
					exit(0); // exit progrma
				}

				// does the second id have a value?
				initialized((yyvsp[(3) - (4)].string), scope);

				// are the id's both variables?
				compareKinds((yyvsp[(1) - (4)].string), (yyvsp[(3) - (4)].string), scope);

				// are the types of the id's the same
				compareTypes((yyvsp[(1) - (4)].string), (yyvsp[(3) - (4)].string), scope);

			// symbol table
			updateValue((yyvsp[(1) - (4)].string), scope, getValue((yyvsp[(3) - (4)].string), scope)); // update value of first id in symbol table

			// ast
			(yyval.ast) = AST_BinaryExpression("=",(yyvsp[(1) - (4)].string),(yyvsp[(3) - (4)].string)); // add expression to the ast

			// ir code
			createIDtoIDAssignment((yyvsp[(1) - (4)].string), (yyvsp[(3) - (4)].string), scope); // create ir code: T0 = T1

			// mips code
			createMIPSIDtoIDAssignment((yyvsp[(1) - (4)].string), (yyvsp[(3) - (4)].string), scope); // create mips

			// code optimization
				// mark the two id's as used
				isUsed((yyvsp[(1) - (4)].string), scope);
				isUsed((yyvsp[(3) - (4)].string), scope);

		}

	;}
    break;

  case 52:
#line 883 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: ID = Function\n" RESET); // e.g. x = addValue(1,2);

		if (ifElseCurrentBlock == runIfElseBlock) { // if we are in an if block, both are 1, if we are in an else block, both are 0

			// set scope to function
			strcpy(scope, (yyvsp[(3) - (7)].string));

			// loop through arguments and do parser functions
			for (int i = 0; i < argCounter; i++) { // from 0 to however many arguments there are

				printf(BGREEN "Parameter Accepted.\n" RESET); // output to console

				// ir code
				printf(BLUE "IR Code" RESET);
				printf(RED " NOT " RESET);
				printf(BLUE "Created.\n" RESET); // ir code not yet created

				// variables for getting parameter name based on index
				char itemName[50]; // stores name of parameter
				char itemID[50]; // stores id of the parameter
				char result[50]; // stores the result of below function

				// get parameter name based on index of for loop
				sprintf(itemID, "%d", i); // convert i into a string
				sprintf(itemName, "%s", getNameByID(itemID, scope)); // add the name of the parameter into itemName
				strcpy(result, ""); // redundant
				strcat(result, itemName); // store itemName in result

				// variables to hold the type of the parameter
				char type[50];
				int isInt, isFloat, isChar;

				// get the type of the parameter
				sprintf(type, "%s", getVariableType(itemName, scope));
				
				// determine whether the type is INT, FLT, or CHR
				isInt = strcmp(type, "INT"); // compare type to "INT"
				isFloat = strcmp(type, "FLT"); // compare type to "FLT"
				isChar = strcmp(type, "CHR"); // compare type to "CHR"

				if (isInt == 0) { // if the parameter is an integer
					if (argIsID == 1) { // if parameter is an ID

						// mips
						createIntIDParameter(IDArg, i+1, "G"); // create mips for an id parameter
						argIsID = 0; // revert argIsID to 0 (it gets set to 1 when it sees an ID parameter in ArgDeclList)

					} 
					else { // if parameter is an integer

						// mips
						createIntParameter(args[i], i+1, scope); // create mips for an integer parameter

					}
				} else if (isFloat == 0) { // if parameter is a float

					// mips
					createFloatParameter(args[i], i+1, scope); // create mips for a float parameter
	
				} else if (isChar == 0) { // if parameter is a char

					// mips
					createMIPSCharAssignment(result, args[i], scope); // create mips for a char parameter

				}
				
			}
			argCounter = 0; // revert argCounter to 0 (it gets incremented when counting arguments in ArgDeclList)

			// set scope back to global
			strcpy(scope, "G");

			// symbol table
			printf(BGREEN "Function Call & Parameters Accepted.\n" RESET); // output to console

			// mips again
			callMIPSFunction((yyvsp[(3) - (7)].string)); // create mips for the calling of a function
			setVariableToReturn((yyvsp[(1) - (7)].string), (yyvsp[(3) - (7)].string), scope); // update the variable for the return type of this function

		}

	;}
    break;

  case 53:
#line 964 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: Write Statement (Variable)\n" RESET); // e.g. write x;

		if (ifElseCurrentBlock == runIfElseBlock) { // if we are in an if block, both are 1, if we are in an else block, both are 0

			// semantic checks
				// is the id initialized as a value?
				initialized((yyvsp[(2) - (3)].string), scope); // symbol table function: exits if not initialized
			
			// symbol table
				// N/A

			// ast
			(yyval.ast) = AST_BinaryExpression("Expr", (yyvsp[(1) - (3)].string), getValue((yyvsp[(2) - (3)].string), scope)); // add the write statement to the ast

			// ir code
			createWriteId((yyvsp[(2) - (3)].string), scope); // create ir code: output T0

			// mips
			// get the type of the variable
			char* type = getVariableType((yyvsp[(2) - (3)].string), scope);

			// determine if its int or char
			int isInt = strcmp(type, "INT"); // compare type to "INT"
			int isChar = strcmp(type, "CHR"); // compare type to "CHR"
			int isFloat = strcmp(type, "FLT"); // compare type to "FLT"

			// run correct mips function according to type
			if (isInt == 0) { // if the variable is an integer
				createMIPSWriteInt((yyvsp[(2) - (3)].string), scope); // create mips
			} 
			else if (isChar == 0) { // if the variable is a char
				createMIPSWriteChar((yyvsp[(2) - (3)].string), scope); // create mips
			} 
			else if (isFloat == 0) { // if the variable is a float
				createMIPSWriteFloat((yyvsp[(2) - (3)].string), scope); // create mips
			}

			// code optimization
				// mark the id as used
				isUsed((yyvsp[(2) - (3)].string), scope);

			/*
						Expr
				WRITE     getValue(ID)
			*/
		}

	;}
    break;

  case 54:
#line 1011 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: Write Statement (Etc. String)\n" RESET); // e.g. write "Hello World!";

		if (ifElseCurrentBlock == runIfElseBlock) { // if we are in an if block, both are 1, if we are in an else block, both are 0

			// semantic checks
				// N/A

			// symbol table
				// N/A

			// ast
			(yyval.ast) = AST_BinaryExpression("Expr", (yyvsp[(1) - (3)].string), (yyvsp[(2) - (3)].string)); // add expression to the ast

			// ir code
			char str[50]; // variable to hold string without apostrophes
			strcpy(str, removeApostrophes((yyvsp[(2) - (3)].string))); // remove apostrophes and copy string into str
			createWriteString(str); // create ir code: output "Hello World!""

			// mips code
			defineMIPSTempString(str); // create mips temp definition at the top of the file to hold the string
			createMIPSWriteString((yyvsp[(2) - (3)].string), scope); // create mips code to display the string in scope

			// code optimization
				// mark the id as used
				isUsed((yyvsp[(2) - (3)].string), scope);

		}

	;}
    break;

  case 55:
#line 1039 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: Write Statement (Array Element)\n" RESET); // e.g. write arr[0];

		if (ifElseCurrentBlock == runIfElseBlock) { // if we are in an if block, both are 1, if we are in an else block, both are 0

			// concatenate the array in this format: "$2[$4]"
			char elementID[50]; // holds the id of the element in the array
			strcpy(elementID, (yyvsp[(2) - (6)].string)); // elementID: arr
			strcat(elementID, "["); // elementID: arr[
			strcat(elementID, (yyvsp[(4) - (6)].string)); // elementID: arr[0
			strcat(elementID, "]"); // elementID: arr[0]

			// semantic checks
				// is the id initialized as a value?
				initialized(elementID, scope); // symbol table function: exits if not initialized
				
			// symbol table
				// N/A

			// ast
			(yyval.ast) = AST_BinaryExpression("Expr", (yyvsp[(1) - (6)].string), getValue(elementID, scope)); // add expression to ast

			// ir code
			createWriteId(elementID, scope); // create ir code: T0 = arr[0]

			// mips code
				// get the type of the element
				char* type = getVariableType(elementID, scope); // symbol table function that returns type

				// determine if its int or char
				int isInt = strcmp(type, "INT"); // compare type to "INT"
				int isChar = strcmp(type, "CHR"); // compare type to "CHR"
				int isFloat = strcmp(type, "FLT"); // compare type to "FLT"

				// run correct mips function according to type
				if (isInt == 0) { // if the elemnt is an integer
					removeBraces(elementID); // remove the braces to make its name in mips
					createMIPSWriteInt(elementID, scope); // create mips to write the element
				} 
				else if (isChar == 0) { // if the element is a char
					removeBraces(elementID); // remove the braces to make its name in mips
					createMIPSWriteChar(elementID, scope); // create mips to write the element
				} 
				else if (isFloat == 0) { // if the element is a float
					removeBraces(elementID); // remove the braces to make its name in mips
					createMIPSWriteFloat(elementID, scope); // create mips to write the element
				}

			// code optimization
				// mark the id as used
				isUsed((yyvsp[(2) - (6)].string), scope);

		}

	;}
    break;

  case 56:
#line 1092 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: Print New Line\n\n" RESET); // e.g. write ~nl;

		if (ifElseCurrentBlock == runIfElseBlock) { // if we are in an if block, both are 1, if we are in an else block, both are 0

			// ast
			(yyval.ast) = AST_BinaryExpression("Expr", (yyvsp[(1) - (3)].string), "NEWLINE"); // add newline expression to ast

			// symbol table
			printf(BGREEN "Symbol Table Not Needed.\n" RESET); // output to console

			// ir code
			createNewLine(); // create ir code: output *newline*

			// mips
			makeMIPSNewLine(scope); // create newline in mips

		}

	;}
    break;

  case 57:
#line 1110 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: Math Statement\n\n" RESET); // e.g. x = 3 - 1; same as above, just can also be in a stmtList

		if (ifElseCurrentBlock == runIfElseBlock) { // if we are in an if block, both are 1, if we are in an else block, both are 0

			// ast
			(yyval.ast) = (yyvsp[(1) - (2)].ast);

		}

	;}
    break;

  case 58:
#line 1119 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: Modify Integer Array Index\n\n" RESET); // e.g. arr[0] = 1;

		if (ifElseCurrentBlock == runIfElseBlock) { // if we are in an if block, both are 1, if we are in an else block, both are 0

			// add backets to id
			char temp[50]; // temp variable to hold id with brackets
			sprintf(temp,"%s[%s]",(yyvsp[(1) - (7)].string),(yyvsp[(3) - (7)].string)); // fills temp with: arr[0] for example

			// convert index to integer
			int index = atoi((yyvsp[(3) - (7)].string)); // stores converted integer in index variable

			// symbol table
			updateArrayValue((yyvsp[(1) - (7)].string), index, scope, "INT", (yyvsp[(6) - (7)].string)); // update value of the array element in the symbol table

			// symbol table
			if (strcmp(scope, "G") != 0) { // if scope is in function

				if (found(temp, scope) == 1) { // if the variable is found in the function's sym table

					updateArrayValue((yyvsp[(1) - (7)].string), index, scope, "INT", (yyvsp[(6) - (7)].string)); // update value in function sym table

				} else if (found(temp, "G") == 1) { // if the variable is found in the global scope

					updateArrayValue((yyvsp[(1) - (7)].string), index, "G", "INT", (yyvsp[(6) - (7)].string)); // update value in global sym table

				} else { // variable not found

					showSymTable(); // show symbol table
					printf(RED "\nERROR: Variable '%s' does not exist.\n\n" RESET, temp); // error message
					exit(0); // exit program

				}

			} else { // if scope is global
				updateArrayValue((yyvsp[(1) - (7)].string), index, scope, "INT", (yyvsp[(6) - (7)].string)); // update value normally
			}

			// ast
			(yyval.ast) = AST_assignment((yyvsp[(1) - (7)].string),(yyvsp[(3) - (7)].string),(yyvsp[(6) - (7)].string)); // add expression to the ast

			// ir code
			createIntAssignment(temp, (yyvsp[(6) - (7)].string), scope); // create ir code

			// mips code
			if (strcmp(scope, "G") != 0) { // if scope is function

				if (found(temp, scope) == 1) { // if the variable is found in the function's sym table

					removeBraces(temp); // remove the braces to make its name in mips
					createMIPSIntAssignment(temp, (yyvsp[(6) - (7)].string), scope); // create mips to update the array element

				} else if (found(temp, "G") == 1) { // if the variable is found in the global scope

					removeBraces(temp); // remove the braces to make its name in mips
					createMIPSIntAssignment(temp, (yyvsp[(6) - (7)].string), "G"); // create mips to update the array element

				} else { // variable not found

					showSymTable(); // show symbol table
					printf(RED "\nERROR: Variable '%s' does not exist.\n\n" RESET, temp); // error message
					exit(0); // exit program

				}

			} 
			else { // if scope is global
				removeBraces(temp); // remove the braces to make its name in mips
				createMIPSIntAssignment(temp, (yyvsp[(6) - (7)].string), scope); // create mips to update the array element
			}

		}

	;}
    break;

  case 59:
#line 1191 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: Modify Integer Array Index (Math)\n\n" RESET); // e.g. arr[0] = 1 + 2;

		if (ifElseCurrentBlock == runIfElseBlock) { // if we are in an if block, both are 1, if we are in an else block, both are 0

			system("python3 calculate.py"); // perform calculation
	
			char result[100]; // store result of calculation
			readEvalOutput(&result); // read the output and store in result
			clearCalcInput(); // clear the input to the calculator
			printf(RED"\nResult from evaluation ==> %s \n"RESET,result); // output result to console
	
			// convert index to integer
			int index = atoi((yyvsp[(3) - (7)].string)); // convert index to integer and store in index variable

			// symbol table
			updateArrayValue((yyvsp[(1) - (7)].string), index, scope, "INT", result); // update array element in symbol table

			// ast
			(yyval.ast) = AST_assignment((yyvsp[(1) - (7)].string),(yyvsp[(3) - (7)].string),result); // add expression to symbol table

			// ir code
			char temp[50]; // temp variable to hold id with brackets
			sprintf(temp,"%s[%s]",(yyvsp[(1) - (7)].string),(yyvsp[(3) - (7)].string)); // fills temp with: arr[0] for example
			createIntAssignment(temp, result, scope); // create ir code

			// mips code
			if (strcmp(scope, "G") != 0) { // if scope is in function
				if (found(temp, scope) == 1) { // if the variable is found in the function scope
					removeBraces(temp); // remove the braces to make its name in mips
					createMIPSIntAssignment(temp, result, scope); // create mips to update the array element
				} 
				else if (found(temp, "G") == 1) { // if the variable is found in the global scope
					removeBraces(temp); // remove the braces to make its name in mips
					createMIPSIntAssignment(temp, result, "G"); // create mips to update the array element
				} 
				else { // variable not found
					showSymTable(); // show symbol table
					printf(RED "\nERROR: Variable '%s' does not exist.\n\n" RESET, temp); // error message
					exit(0); // exit program
				}
			} else { // if scope is global
				removeBraces(temp); // remove the braces to make its name in mips
				createMIPSIntAssignment(temp, result, scope); // create mips to update the array element
			}
		}
	
	;}
    break;

  case 60:
#line 1237 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: Modify Char Array Index\n\n" RESET); // e.g. arr[0] = 'c';

		if (ifElseCurrentBlock == runIfElseBlock) { // if we are in an if block, both are 1, if we are in an else block, both are 0

			// add brackets to id for sym table searches
			char temp[50]; // temp variable to hold id with brackets
			sprintf(temp,"%s[%s]",(yyvsp[(1) - (7)].string),(yyvsp[(3) - (7)].string)); // fills temp with: arr[0] for example

			// convert index to integer
			int index = atoi((yyvsp[(3) - (7)].string)); // store converted array index in index variable

			// remove apostrophes from charliteral
			char* str = removeApostrophes((yyvsp[(6) - (7)].string)); // remove apostrophes function from symbol table

			// symbol table
			if (strcmp(scope, "G") != 0) { // if scope is in function

				if (found(temp, scope) == 1) { // if the variable is found in the function's sym table

					updateArrayValue((yyvsp[(1) - (7)].string), index, scope, "CHR", str); // update value in function sym table

				} else if (found(temp, "G") == 1) { // if the variable is found in the global scope

					updateArrayValue((yyvsp[(1) - (7)].string), index, "G", "CHR", str); // update value in global sym table

				} else { // variable not found

					showSymTable(); // show symbol table
					printf(RED "\nERROR: Variable '%s' does not exist.\n\n" RESET, temp); // error message
					exit(0); // exit program

				}

			} else { // if scope is global
				updateArrayValue((yyvsp[(1) - (7)].string), index, scope, "CHR", str); // update value normally
			}

			// ast
			(yyval.ast) = AST_assignment((yyvsp[(1) - (7)].string),(yyvsp[(3) - (7)].string),str); // add expression to the ast

			// ir code
			createIntAssignment(temp, str, scope); // create ir code

			// mips code
			if (strcmp(scope, "G") != 0) { // if scope is in function

				if (found(temp, scope) == 1) { // if the variable is found in the function's sym table

					removeBraces(temp); // remove the braces to make its name in mips
					createMIPSCharAssignment(temp, str, scope); // create mips to update the array element

				} else if (found(temp, "G") == 1) { // if the variable is found in the global scope

					removeBraces(temp); // remove the braces to make its name in mips
					createMIPSCharAssignment(temp, str, "G"); // create mips to update the array element

				} else { // variable not found

					showSymTable(); // show symbol table
					printf(RED "\nERROR: Variable '%s' does not exist.\n\n" RESET, temp); // error message
					exit(0); // exit program

				}

			} else { // if scope is global
				removeBraces(temp); // remove the braces to make its name in mips
				createMIPSCharAssignment(temp, str, scope); // create mips to update the array element
			}
		}

	;}
    break;

  case 61:
#line 1307 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: Call Function\n\n" RESET); // e.g. addValue(1,2);

		if (ifElseCurrentBlock == runIfElseBlock) { // if we are in an if block, both are 1, if we are in an else block, both are 0

			// set scope to function
			strcpy(scope, (yyvsp[(1) - (5)].string));

			// loop through arguments
			for (int i = 0; i < argCounter; i++) {

				printf(BGREEN "Parameter Accepted.\n" RESET); // output to console

				// ir code
				printf(BLUE "IR Code" RESET);
				printf(RED " NOT " RESET);
				printf(BLUE "Created.\n" RESET); // ir code not yet created

				// variables for getting parameter name based on index
				char itemName[50]; // stores name of parameter
				char itemID[50]; // stores id of the parameter
				char result[50]; // stores the result of below function

				// get parameter name based on index of for loop
				sprintf(itemID, "%d", i); // convert i into a string
				sprintf(itemName, "%s", getNameByID(itemID, scope)); // add the name of the parameter into itemName
				strcpy(result, ""); // redundant
				strcat(result, itemName); // store itemName in result

				// variables to hold the type of the parameter
				char type[50];
				int isInt, isFloat, isChar;

				// get the type of the parameter
				sprintf(type, "%s", getVariableType(itemName, scope));
				
				// get type of parameter
				isInt = strcmp(type, "INT"); // compare type to "INT"
				isFloat = strcmp(type, "FLT"); // compare type to "FLT"
				isChar = strcmp(type, "CHR"); // compare type to "CHR"

				// run mips based on type
				if (isInt == 0) { // if parameter is an integer
					if (argIsID == 1) { // if parameter is an ID
						createIntIDParameter(IDArg, i+1, scope); // create integer ID parameter in mips
						argIsID = 0; // reset argIsID to 0 (gets changed to 1 in argDeclList)
					} 
					else { // if parameter is an integer number
						createIntParameter(args[i], i+1, scope); // create integer parameter in mips
					}
				} 
				else if (isFloat == 0) { // if parameter is a float
					createFloatParameter(args[i], i+1, scope); // create float parameter in mips
				} 
				else if (isChar == 0) { // if parameter is a char
					createMIPSCharAssignment(result, args[i], scope); // create char parameter in mips
				}
			}
			argCounter = 0; // reset argCounter to 0 (gets set to 1 when counting arguments in argDeclList)

			// set scope back to global
			strcpy(scope, "G");

			// symbol table
			printf(BGREEN "Function Call & Parameters Accepted.\n" RESET); // output to console

			// ast
			(yyval.ast) = AST_assignment((yyvsp[(1) - (5)].string),(yyvsp[(2) - (5)].string),(yyvsp[(4) - (5)].string)); // add expression to the ast

			// ir code
			printf(BLUE "IR Code" RESET);
			printf(RED " NOT " RESET);
			printf(BLUE "Created.\n" RESET); // ir code currently not needed

			// mips
			callMIPSFunction((yyvsp[(1) - (5)].string)); // create function call in mips

		}

	;}
    break;

  case 62:
#line 1385 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: Return Statement (ID)\n\n" RESET); // e.g. return x; (inside a function)

		if (ifElseCurrentBlock == runIfElseBlock) { // if we are in an if block, both are 1, if we are in an else block, both are 0

			// symbol table
			updateValue(scope, "G", getValue((yyvsp[(2) - (3)].string), scope)); // update the value of the function in the global table
			printf(BGREEN "Updated ID Return Value of Function.\n" RESET); // output to console

			// ir code
			printf(BLUE "IR Code" RESET);
			printf(RED " NOT " RESET);
			printf(BLUE "Created.\n" RESET); // ir code not currently needed

			// temp variables
			char str[50]; // temp string to hold variable type
			strcpy(str, getVariableType((yyvsp[(2) - (3)].string), scope)); // store variable type in 'str'

			char str1[50]; // temp string to hold "G{scope}"
			strcpy(str1, "G"); // store "G" in 'str1'
			strcat(str1, scope); // concatenate the scope to 'str1'

			char str2[50]; // temp string to hold "{scope}Return" for function return variable in mips
			strcpy(str2, scope); // store scope in 'str2'
			strcat(str2, "Return"); // concatenate "Return" to 'str2'
			
			// mips based on type
			if (strcmp(str, "INT") == 0) { // if the id is an integer

				// ir code
				createReturnIDStatement((yyvsp[(2) - (3)].string)); // create ir code: return T2

				// mips
				createMIPSReturnStatementNumber(str2, (yyvsp[(2) - (3)].string), getValue((yyvsp[(2) - (3)].string), scope), scope); // create mips return variable

			} 
			else if (strcmp(str, "FLT") == 0) { // if the id is a float

				// ir code
				createReturnIDStatement((yyvsp[(2) - (3)].string)); // create ir code: return T2

				// mips
				createMIPSFloatAssignment("", getValue((yyvsp[(2) - (3)].string), scope), str1); // create mips return variable

			} 
			else if (strcmp(str, "CHR") == 0) { // if the id is char

				// ir code
				createReturnIDStatement((yyvsp[(2) - (3)].string)); // create ir code: return T2

				// mips
				createMIPSCharAssignment("", getValue((yyvsp[(2) - (3)].string), scope), str1); // create mips return variable
			}
			
		}

	;}
    break;

  case 63:
#line 1440 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: Return Statement (Int Number)\n\n" RESET);

		if (ifElseCurrentBlock == runIfElseBlock) { // if we are in an if block, both are 1, if we are in an else block, both are 0
			// symbol table
			updateValue(scope, "G", (yyvsp[(2) - (3)].string));
			printf(BGREEN "Updated Integer Return Value of Function.\n" RESET);

			// ir code
			printf(BLUE "IR Code" RESET);
			printf(RED " NOT " RESET);
			printf(BLUE "Created.\n" RESET);

			// mips
			// create scope so that it has G and then the function scope, since
			// we are accessing the global variable that is called the function name
			char str[50];
			strcpy(str, "G");
			strcat(str, scope);

			createMIPSIntAssignment("", (yyvsp[(2) - (3)].string), str);
		}

	;}
    break;

  case 64:
#line 1462 "parser.y"
    {

		if (ifElseCurrentBlock == runIfElseBlock) { // if we are in an if block, both are 1, if we are in an else block, both are 0
			// symbol table
			updateValue(scope, "G", (yyvsp[(2) - (3)].string));
			printf(BGREEN "Updated Float Return Value of Function.\n" RESET);

			// ir code
			printf(BLUE "IR Code" RESET);
			printf(RED " NOT " RESET);
			printf(BLUE "Created.\n" RESET);

			// mips
			// create scope so that it has G and then the function scope, since
			// we are accessing the global variable that is called the function name
			char str[50];
			strcpy(str, "G");
			strcat(str, scope);

			createMIPSFloatAssignment("", (yyvsp[(2) - (3)].string), str);
		}

	;}
    break;

  case 65:
#line 1484 "parser.y"
    {

		if (ifElseCurrentBlock == runIfElseBlock) { // if we are in an if block, both are 1, if we are in an else block, both are 0
			// symbol table
			updateValue(scope, "G", (yyvsp[(2) - (3)].string));
			printf(BGREEN "Updated Char Return Value of Function.\n" RESET);

			// ir code
			printf(BLUE "IR Code" RESET);
			printf(RED " NOT " RESET);
			printf(BLUE "Created.\n" RESET);

			// mips
			char str[50];
			strcpy(str, "G");
			strcat(str, scope);
			createMIPSCharAssignment("", (yyvsp[(2) - (3)].string), str);
		}

;}
    break;

  case 66:
#line 1509 "parser.y"
    {

	// ast
	// TODO: EVAN
	if (scope == "G" && inElseOrWhile != UPDATE_WHILE) { // ADD CHECK HERE FOR IF NOT IN WHILE LOOP, IF IN WHILE LOOP, NEED TO DO ELSE

		system("python3 calculate.py");
		
		char result[100];
		readEvalOutput(&result);
		clearCalcInput();
		printf(RED"\nResult from evaluation ==> %s \n"RESET,result);

		// semantic checks
			// inside Math

		// calculations: code optimization
			// turn the integer returned from calculate() into a string

		// symbol table

		if (strcmp(scope, "G") != 0) { // if scope is in function

			if (found((yyvsp[(1) - (3)].string), scope) == 1) { // if the variable is found in the function's sym table

				updateValue((yyvsp[(1) - (3)].string), scope, result); // update value in function sym table

			} else if (found((yyvsp[(1) - (3)].string), "G") == 1) { // if the variable is found in the global scope

				updateValue((yyvsp[(1) - (3)].string), "G", result); // update value in global sym table

			}

		} else { // if scope is global
			updateValue((yyvsp[(1) - (3)].string), scope, result); // update value normally
		}

		// ast
		(yyval.ast) = AST_BinaryExpression("=", (yyvsp[(1) - (3)].string), result);

		
		char type[50];

		strcpy(type,getVariableType((yyvsp[(1) - (3)].string),scope));

		if (strcmp(type,"INT") == 0){
			// ir code
			createIntAssignment((yyvsp[(1) - (3)].string), result, scope);

			// mips code
			createMIPSIntAssignment((yyvsp[(1) - (3)].string), result, scope);
		}

		else if(strcmp(type,"FLT") == 0){
			// ir code
			createFloatAssignment((yyvsp[(1) - (3)].string), result, scope);

			// mips code
			createMIPSFloatAssignment((yyvsp[(1) - (3)].string), result, scope);
		}

		
		// code optimization
		// mark the id as used
		isUsed((yyvsp[(1) - (3)].string), scope);

	} else {

		if (scope != "G" && inElseOrWhile != UPDATE_WHILE) { // in a function

			if (op == '+') {

				// ir code
				createFunctionAddition((yyvsp[(1) - (3)].string));

				// mips
				createMIPSParameterAddition((yyvsp[(1) - (3)].string), scope);

			} else if (op == '-') {

				// ir code
				createFunctionSubtraction((yyvsp[(1) - (3)].string));

				// mips
				createMIPSSubtraction((yyvsp[(1) - (3)].string), num1, num2, scope);
			}
		
		} else { // in a while loop

			if (op == '+') {

				// ir code
				createFunctionAddition((yyvsp[(1) - (3)].string));

				// mips
				createMIPSLoopAddition(scope);
			} else if (op == '-') {

				// ir code
				createFunctionSubtraction((yyvsp[(1) - (3)].string));

				// mips
				createMIPSLoopSubtraction(scope);
			}

		}

	}

;}
    break;

  case 67:
#line 1620 "parser.y"
    {

;}
    break;

  case 68:
#line 1624 "parser.y"
    {

;}
    break;

  case 69:
#line 1629 "parser.y"
    {addToInputCalc((yyvsp[(1) - (1)].string));;}
    break;

  case 70:
#line 1630 "parser.y"
    {addToInputCalc((yyvsp[(1) - (1)].string));;}
    break;

  case 71:
#line 1631 "parser.y"
    {
			addToInputCalc(getValue((yyvsp[(1) - (1)].string),scope)); 
			strcpy(num1, (yyvsp[(1) - (1)].string));

			//printf(BORANGE "inElseOrWhile: %s\nUPDATE_WHILE: %d\n", inElseOrWhile, UPDATE_WHILE);
			
			if (inElseOrWhile == UPDATE_WHILE) {

				createMIPSAddIDToRegister((yyvsp[(1) - (1)].string), registerCounter, scope);
				registerCounter++;
				
			}


		;}
    break;

  case 72:
#line 1647 "parser.y"
    {
			addToInputCalc((yyvsp[(1) - (1)].string)); 
			strcpy(num2, (yyvsp[(1) - (1)].string)); 

			if (inElseOrWhile == UPDATE_WHILE) {

				createMIPSAddNumberToRegister((yyvsp[(1) - (1)].string), registerCounter);
				registerCounter++;

			}
		
		;}
    break;

  case 73:
#line 1659 "parser.y"
    {addToInputCalc((yyvsp[(1) - (1)].string));;}
    break;

  case 74:
#line 1660 "parser.y"
    {addToInputCalc("**");;}
    break;

  case 75:
#line 1661 "parser.y"
    {addToInputCalc((yyvsp[(1) - (1)].ast));;}
    break;

  case 76:
#line 1665 "parser.y"
    {op = '+';;}
    break;

  case 77:
#line 1666 "parser.y"
    {op = '-';;}
    break;

  case 78:
#line 1667 "parser.y"
    {op = '*';;}
    break;

  case 79:
#line 1668 "parser.y"
    {op = '/';;}
    break;

  case 80:
#line 1671 "parser.y"
    {;}
    break;

  case 81:
#line 1672 "parser.y"
    {;}
    break;

  case 82:
#line 1673 "parser.y"
    {;}
    break;

  case 83:
#line 1674 "parser.y"
    {;}
    break;

  case 84:
#line 1675 "parser.y"
    {;}
    break;

  case 85:
#line 1676 "parser.y"
    {;}
    break;

  case 86:
#line 1680 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: Integer Array Initialization Without Range\n\n" RESET);
				//int foo[]; //We should only have arrays be declared with range imo.



			;}
    break;

  case 87:
#line 1685 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: Char Array Initialization Without Range\n\n" RESET);
				//char foo[]; //We should only have arrays be declared with range imo.

			

			;}
    break;

  case 88:
#line 1690 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: Integer Array Initialization With Range\n\n" RESET);
				// e.g. int foo[4];

						if (ifElseCurrentBlock == runIfElseBlock) {
							// semantic checks
							symTabAccess();

								// is the range > 0?
								if (atoi((yyvsp[(4) - (6)].string)) <= 0) {
									printf(RED "\nERROR: Array range must be greater than 0.\n" RESET,(yyvsp[(2) - (6)].string));
									showSymTable(); // show symbol table
									exit(0); // array already declared
								}

								// is the array already declared in this scope?			
								// add "[0]" to the ID
								char temp[50];	
								sprintf(temp,"%s[0]",(yyvsp[(2) - (6)].string));

								if (found(temp, scope) == 1) {
									printf(RED "\nERROR: Array '%s' already declared in this scope.\n" RESET,(yyvsp[(2) - (6)].string));
									showSymTable(); // show symbol table
									exit(0); // array already declared
								}

							// symbol table
							addArray((yyvsp[(2) - (6)].string), "ARR", "INT", (yyvsp[(4) - (6)].string), scope);

							// ast
							(yyval.ast) = AST_assignment("ARR",(yyvsp[(1) - (6)].string),(yyvsp[(2) - (6)].string));

							// ir code
							int range = atoi((yyvsp[(4) - (6)].string));
							//printf("\n%d\n", range);
							for (int i = 0; i < range; i++) {
								char temp[50];	
								sprintf(temp,"%s[%d]",(yyvsp[(2) - (6)].string),i);
								createIntDefinition(temp, scope);
							}
							printf("\n\n");
						}

			;}
    break;

  case 89:
#line 1732 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: Char Array Initialization With Range\n\n" RESET);
				// e.g. char foo[5];
	
						if (ifElseCurrentBlock == runIfElseBlock) {
							// semantic checks
							symTabAccess();

								// is the range > 0?
								if (atoi((yyvsp[(4) - (6)].string)) <= 0) {
									printf(RED "\nERROR: Array range must be greater than 0.\n" RESET,(yyvsp[(2) - (6)].string));
									showSymTable(); // show symbol table
									exit(0); // array already declared
								}
								// is the array already declared?
								// add "[0]" to the ID
								char temp[50];	
								sprintf(temp,"%s[0]",(yyvsp[(2) - (6)].string));
								
								if (found(temp, scope) == 1) {
									printf(RED "\nERROR: Array '%s' already declared in this scope.\n" RESET,(yyvsp[(2) - (6)].string));
									showSymTable();
									exit(0); // variable already declared
								}

							// symbol table
							addArray((yyvsp[(2) - (6)].string), "ARR", "CHR", (yyvsp[(4) - (6)].string), scope);

							// ast
							(yyval.ast) = AST_assignment("ARR",(yyvsp[(1) - (6)].string),(yyvsp[(2) - (6)].string));

							// ir code
							int range = atoi((yyvsp[(4) - (6)].string));
							//printf("\n%d\n", range);
							for (int i = 0; i < range; i++) {
								sprintf(temp,"%s[%d]",(yyvsp[(2) - (6)].string),i);
								createIntDefinition(temp, scope);
							}
							printf("\n\n");
						}

;}
    break;

  case 90:
#line 1774 "parser.y"
    { inElseOrWhile = UPDATE_WHILE;
					
					sprintf(whileName, "whileLoop%d",numOfWhileLoops);
					createMIPSFunction(whileName);  //create while loop function in MIPS
					callMIPSLoop(whileName);
					numOfWhileLoops++;
					changeIRFile(IR_FUNC);
					changeMIPSFile(MIPS_FUNC); //add block code to while loop function 

					// ir code
					createWhileStatement(numOfWhileLoops-1);

						;}
    break;

  case 91:
#line 1786 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: While Statement Initialization \n\n" RESET);							 
						 
							//inElseOrWhile = 0; //reset before block since Condition has been run already

						 ;}
    break;

  case 92:
#line 1790 "parser.y"
    { 
							
							printf(GRAY "\nRECOGNIZED RULE: While Statement Block\n\n" RESET);
							MIPSWhileJump(whileName);
							changeIRFile(IR_CODE);
							changeMIPSFile(TEMP_MIPS); //change MIPS file location back to default (main:)
							//current = 0;

;}
    break;

  case 93:
#line 1800 "parser.y"
    {inElseOrWhile = UPDATE_IF_ELSE;;}
    break;

  case 94:
#line 1800 "parser.y"
    { printf(GRAY "RECOGNIZED RULE: If-Else Statement Initialization \n\n" RESET);
						
						inElseOrWhile = 0; //reset before block since Condition has been run already		 
						ifElseCurrentBlock = IN_IF_BLOCK;
						 
						 ;}
    break;

  case 95:
#line 1805 "parser.y"
    { printf(GRAY "\nRECOGNIZED RULE: If-Else: IF Statement Block\n\n" RESET);

							if (runIfElseBlock == RUN_IF_BLOCK) {
								
								printf(BORANGE "Done with If Statement.\n\n" RESET);

							}

							ifElseCurrentBlock = IN_ELSE_BLOCK;

						 ;}
    break;

  case 96:
#line 1815 "parser.y"
    { printf(GRAY "\nRECOGNIZED RULE: If-Else: ELSE Statement Block\n\n" RESET);

							if (runIfElseBlock == RUN_ELSE_BLOCK) {
								
								printf(BORANGE "Done With Else Statement.\n\n" RESET);

							}
							runIfElseBlock = 0; // reset the pass variable
							ifElseCurrentBlock = 0; // reset the current variable

;}
    break;

  case 99:
#line 1829 "parser.y"
    {

				int temp1, temp2;
				temp1 = atoi((yyvsp[(1) - (3)].string));
				temp2 = atoi((yyvsp[(3) - (3)].string));

				if (compareIntOp((yyvsp[(2) - (3)].ast), temp1, temp2) && inElseOrWhile == UPDATE_IF_ELSE) {
					runIfElseBlock = 1;
				}
				if (compareIntOp((yyvsp[(2) - (3)].ast), temp1, temp2) && inElseOrWhile == UPDATE_WHILE) {
					if(strcmp((yyvsp[(2) - (3)].ast),"==") == 0){
						printf(BORANGE "\nWARNING: Possible infinite loop detected.\n" RESET);
					}
					createWhileCondition((yyvsp[(1) - (3)].string), (yyvsp[(2) - (3)].ast), (yyvsp[(3) - (3)].string));
					endMIPSWhile((yyvsp[(1) - (3)].string),(yyvsp[(2) - (3)].ast),(yyvsp[(3) - (3)].string),scope,1,1);
					runWhileBlock = 1;
				}


		;}
    break;

  case 100:
#line 1848 "parser.y"
    {

				char type1[50];
				char type2[50];
				strcpy(type1, getVariableType((yyvsp[(1) - (3)].string), scope));
				strcpy(type2, getVariableType((yyvsp[(3) - (3)].string), scope));
				//printf(BORANGE "type1: %s\ntype2: %s\n" RESET, type1, type2);

				// semantic checks
				// are the types the same?
				int check;
				check = strcmp(type1, type2);

				if (!check) { // if the types are the same
					printf(BGREEN "\nID types are the same.\n" RESET);
				} else {
					printf(RED "\nERROR: Trying to compare two ID's that are not of the same type.\n" RESET);
					showSymTable();
					exit(0);
				}

				// are the variables intitalized as a value?
				check = strcmp(getValue((yyvsp[(1) - (3)].string), scope), "NULL");

				if (!check) { // if first ID is NULL
					printf(RED "\nERROR: ID '%s' is not assigned to a value.\n" RESET, (yyvsp[(1) - (3)].string));
					showSymTable();
					exit(0);
				}

				check = strcmp(getValue((yyvsp[(3) - (3)].string), scope), "NULL");

				if (!check) { // if second ID is NULL
					printf(RED "\nERROR: ID '%s' is not assigned to a value.\n" RESET, (yyvsp[(3) - (3)].string));
					showSymTable();
					exit(0);
				}

				// go further based on type of id's
				int typeInt, typeFloat, typeChar;
				typeInt = strcmp(type1, "INT");
				typeFloat = strcmp(type1, "FLT");
				typeChar = strcmp(type1, "CHR");

				if (!typeInt) { // if type is integer
					int temp1, temp2;
					temp1 = atoi(getValue((yyvsp[(1) - (3)].string), scope));
					temp2 = atoi(getValue((yyvsp[(3) - (3)].string), scope));
					//printf(BORANGE "temp1: %d\ntemp2: %d\n" RESET, temp1, temp2);

					if (compareIntOp((yyvsp[(2) - (3)].ast), temp1, temp2) && inElseOrWhile == UPDATE_IF_ELSE) {
					runIfElseBlock = 1;
					}
					if (compareIntOp((yyvsp[(2) - (3)].ast), temp1, temp2) && inElseOrWhile == UPDATE_WHILE) {
						if(strcmp((yyvsp[(2) - (3)].ast),"==") == 0){
							printf(BORANGE "\nWARNING: Possible infinite loop detected.\n" RESET);
						}
						createWhileCondition((yyvsp[(1) - (3)].string), (yyvsp[(2) - (3)].ast), (yyvsp[(3) - (3)].string));
						endMIPSWhile((yyvsp[(1) - (3)].string),(yyvsp[(2) - (3)].ast),(yyvsp[(3) - (3)].string),scope,0,0);
						runWhileBlock = 1;
					}
				}
				else if (!typeFloat) { // if type is float
					float temp1, temp2;
					temp1 = atof(getValue((yyvsp[(1) - (3)].string), scope));
					temp2 = atof(getValue((yyvsp[(3) - (3)].string), scope));
					//printf(BORANGE "temp1: %f\ntemp2: %f\n" RESET, temp1, temp2);

					if (compareFloatOp((yyvsp[(2) - (3)].ast), temp1, temp2) && inElseOrWhile == UPDATE_IF_ELSE) {
					runIfElseBlock = 1;
					}
					if (compareFloatOp((yyvsp[(2) - (3)].ast), temp1, temp2) && inElseOrWhile == UPDATE_WHILE) {
						if(strcmp((yyvsp[(2) - (3)].ast),"==") == 0){
							printf(BORANGE "\nWARNING: Possible infinite loop detected.\n" RESET);
						}
						createWhileCondition((yyvsp[(1) - (3)].string), (yyvsp[(2) - (3)].ast), (yyvsp[(3) - (3)].string));
						endMIPSWhile((yyvsp[(1) - (3)].string),(yyvsp[(2) - (3)].ast),(yyvsp[(3) - (3)].string),scope,0,0);
						runWhileBlock = 1;
					}
				}
				else if (!typeChar) { // if type is char
					char temp1[50], temp2[50];
					strcpy(temp1, getValue((yyvsp[(1) - (3)].string), scope));
					strcpy(temp2, getValue((yyvsp[(3) - (3)].string), scope));
					//printf(BORANGE "temp1: %s\ntemp2: %s\n" RESET, temp1, temp2);

					if (compareCharOp((yyvsp[(2) - (3)].ast), temp1, temp2) && inElseOrWhile == UPDATE_IF_ELSE) {
					runIfElseBlock = 1;
					}
					if (compareCharOp((yyvsp[(2) - (3)].ast), temp1, temp2) && inElseOrWhile == UPDATE_WHILE) {
						if(strcmp((yyvsp[(2) - (3)].ast),"==") == 0){
							printf(BORANGE "\nWARNING: Possible infinite loop detected.\n" RESET);
						}
						createWhileCondition((yyvsp[(1) - (3)].string), (yyvsp[(2) - (3)].ast), (yyvsp[(3) - (3)].string));
						endMIPSWhile((yyvsp[(1) - (3)].string),(yyvsp[(2) - (3)].ast),(yyvsp[(3) - (3)].string),scope,0,0);
						runWhileBlock = 1;
					}
				}


		;}
    break;

  case 101:
#line 1948 "parser.y"
    {

				// is the variable intitalized as a value?
				int check;
				check = strcmp(getValue((yyvsp[(1) - (3)].string), scope), "NULL");

				if (!check) { // if first ID is NULL
					printf(RED "\nERROR: ID '%s' is not assigned to a value.\n" RESET, (yyvsp[(1) - (3)].string));
					showSymTable();
					exit(0);
				}

				int temp1, temp2;
				temp1 = atoi(getValue((yyvsp[(1) - (3)].string), scope));
				temp2 = atoi((yyvsp[(3) - (3)].string));

				if (compareIntOp((yyvsp[(2) - (3)].ast), temp1, temp2) && inElseOrWhile == UPDATE_IF_ELSE) {
					runIfElseBlock = 1;
				}
				if (compareIntOp((yyvsp[(2) - (3)].ast), temp1, temp2) && inElseOrWhile == UPDATE_WHILE) {
					if(strcmp((yyvsp[(2) - (3)].ast),"==") == 0){
						printf(BORANGE "\nWARNING: Possible infinite loop detected.\n" RESET);
					}
					createWhileCondition((yyvsp[(1) - (3)].string), (yyvsp[(2) - (3)].ast), (yyvsp[(3) - (3)].string));
					endMIPSWhile((yyvsp[(1) - (3)].string),(yyvsp[(2) - (3)].ast),(yyvsp[(3) - (3)].string),scope,0,1);
					runWhileBlock = 1;
				}


		;}
    break;

  case 102:
#line 1977 "parser.y"
    {

				float temp1, temp2;
				temp1 = atof((yyvsp[(1) - (3)].string));
				temp2 = atof((yyvsp[(3) - (3)].string));
				//printf(BORANGE "temp1: %f\ntemp2: %f\n" RESET, temp1, temp2);

				if (compareFloatOp((yyvsp[(2) - (3)].ast), temp1, temp2) && inElseOrWhile == UPDATE_IF_ELSE) {
					runIfElseBlock = 1;
				}
				if (compareFloatOp((yyvsp[(2) - (3)].ast), temp1, temp2) && inElseOrWhile == UPDATE_WHILE) {
					if(strcmp((yyvsp[(2) - (3)].ast),"==") == 0){
						printf(BORANGE "\nWARNING: Possible infinite loop detected.\n" RESET);
					}
					endMIPSWhile((yyvsp[(1) - (3)].string),(yyvsp[(2) - (3)].ast),(yyvsp[(3) - (3)].string),scope,1,1);
					runWhileBlock = 1;
				}

		;}
    break;

  case 103:
#line 1995 "parser.y"
    {

				char temp1[50], temp2[50];
				strcpy(temp1, (yyvsp[(1) - (3)].string));
				strcpy(temp2, (yyvsp[(3) - (3)].string));
				//printf(BORANGE "temp1: %s\ntemp2: %s\n" RESET, temp1, temp2);

				if (compareCharOp((yyvsp[(2) - (3)].ast), temp1, temp2) && inElseOrWhile == UPDATE_IF_ELSE) {
					runIfElseBlock = 1;
				}
				if (compareCharOp((yyvsp[(2) - (3)].ast), temp1, temp2) && inElseOrWhile == UPDATE_WHILE) {
					if(strcmp((yyvsp[(2) - (3)].ast),"==") == 0){
						printf(BORANGE "\nWARNING: Possible infinite loop detected.\n" RESET);
					}
					endMIPSWhile((yyvsp[(1) - (3)].string),(yyvsp[(2) - (3)].ast),(yyvsp[(3) - (3)].string),scope,1,1);
					runWhileBlock = 1;
				}

		;}
    break;


/* Line 1267 of yacc.c.  */
#line 3907 "parser.tab.c"
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
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  if (yyn == YYFINAL)
    YYACCEPT;

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
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


#line 2027 "parser.y"


int main(int argc, char**argv)
{

	/*
	#ifdef YYDEBUG
		yydebug = 1;
	#endif
	*/

	printf(BOLD "\n\n ###################### COMPILER STARTED ###################### \n\n" RESET);
	clearCalcInput();
	initializeSymbolTable();
	changeIRFile(IR_CODE);
	changeMIPSFile(TEMP_MIPS);

	// initialize ir code file
	initIRcodeFile();

	// initialize mips code file
	initAssemblyFile();
	
	if (argc > 1){
	  if(!(yyin = fopen(argv[1], "r")))
          {
		perror(argv[1]);
		return(1);
	  }
	}
	yyparse();
	

	printf("\n\n #######################" RESET);
	printf(BOLD " COMPILER ENDED " RESET);
	printf("####################### \n\n" RESET);
	
	printf("\n\n ######################" RESET);
	printf(BPINK " SHOW SYMBOL TABLE " RESET);
	printf("##################### \n\n\n\n" RESET);
	showSymTable();

	//printf("\n\n ######################" RESET);
	//printf(BPINK " SHOW ARRAY TABLES " RESET);
	//printf("##################### \n\n\n\n" RESET);
	//showArrTable();

	printf("\n\n\n ######################" RESET);
	printf(PINK " END SYMBOL TABLE " RESET);
	printf("###################### \n\n" RESET);
	
	//printf("\n\n\n ######################" RESET);
	//printf(PINK " REMOVE UNUSED VARIABLES " RESET);
	//printf("###################### \n\n\n\n" RESET);
	//cleanAssemblyCodeOfUnsuedVariables();
	//printf("############################################# \n\n\n\n" RESET);
}

void yyerror(const char* s) {
	fprintf(stderr, RED "\nBison Parse Error: %s\n" RESET, s);
	showSymTable();
	exit(1);
}
