/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 75 "parser.y"
{
	int number;
	char character;
	char* string;
	struct AST* ast;
}
/* Line 1529 of yacc.c.  */
#line 130 "parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

