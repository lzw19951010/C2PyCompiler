/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INTEGER = 258,
    VARIABLE = 259,
    WHILE = 260,
    FOR = 261,
    IF = 262,
    PRINT = 263,
    INT = 264,
    INPUT = 265,
    ADDONE = 266,
    MINUONE = 267,
    CHAR = 268,
    DOUBLE = 269,
    VOID = 270,
    RETURN = 271,
    IFX = 272,
    ELSE = 273,
    AND = 274,
    OR = 275,
    GE = 276,
    LE = 277,
    EQ = 278,
    NE = 279,
    OUT = 280,
    IN = 281,
    UMINUS = 282
  };
#endif
/* Tokens.  */
#define INTEGER 258
#define VARIABLE 259
#define WHILE 260
#define FOR 261
#define IF 262
#define PRINT 263
#define INT 264
#define INPUT 265
#define ADDONE 266
#define MINUONE 267
#define CHAR 268
#define DOUBLE 269
#define VOID 270
#define RETURN 271
#define IFX 272
#define ELSE 273
#define AND 274
#define OR 275
#define GE 276
#define LE 277
#define EQ 278
#define NE 279
#define OUT 280
#define IN 281
#define UMINUS 282

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 19 "compiler.y" /* yacc.c:1909  */

    int iValue;                 /* integer value */
    char sIndex[80];                /* symbol table index */
    nodeType *nPtr;             /* node pointer */

#line 114 "y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
