%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "compiler.h"

/* prototypes */
nodeType *opr(int oper, int nops, ...);
nodeType *id(char* s);
nodeType *con(int value);
void freeNode(nodeType *p);
int ex(nodeType *p);
int yylex(void);

void yyerror(char *s);
int sym[26];                    /* symbol table */
%}

%union {
    int iValue;                 /* integer value */
    char sIndex[80];                /* symbol table index */
    nodeType *nPtr;             /* node pointer */
};

%token <iValue> INTEGER
%token <sIndex> VARIABLE STRLEN
%token WHILE FOR IF PRINT INT INPUT ADDONE MINUONE CHAR DOUBLE VOID RETURN IGNORE SIMICOLON
%nonassoc IFX
%nonassoc ELSE

%left AND OR
%left GE LE EQ NE '>' '<'
%left '+' '-'
%left '*' '/'
%left OUT IN
%nonassoc UMINUS

%type <nPtr> stmt expr expr_list stmt_list argument argument_list variable_list

%%

program:
        function                { printf("\nif __name__ == '__main__':\n\tmain()\n"); exit(0); }
        ;

function:
          function stmt         { ex($2); freeNode($2); }
        | /* NULL */
        ;

stmt:
          ';'                            { ; } 
        | PRINT OUT expr ';'             { $$ = opr(PRINT, 1, $3); } 
        | INPUT IN expr ';'              { $$ = opr(INPUT, 1, $3); } 
        | expr ADDONE ';'                { $$ = opr(ADDONE, 1, $1); } 
        | expr MINUONE ';'               { $$ = opr(MINUONE, 1, $1); } 
        | VARIABLE '=' expr ';'          { $$ = opr('=', 2, id($1), $3); } 
        | INT VARIABLE '=' expr ';'      { $$ = opr('=', 2, id($2), $4); } 
        | INT VARIABLE ';'      { $$ = opr('?', 1, id($2)); } 
        | DOUBLE VARIABLE ';'      { $$ = opr('?', 1, id($2)); } 
        | CHAR VARIABLE ';'      { $$ = opr('?', 1, id($2)); } 
        | CHAR VARIABLE '[' ']' '=' '"' VARIABLE '"' ';'      { $$ = opr('?', 2, id($2), id($7)); } 
        | CHAR VARIABLE '[' INTEGER ']' '=' '"' VARIABLE '"' ';'      { $$ = opr('?', 3, id($2), con($4), id($8));}
		| INT VARIABLE '[' INTEGER ']' ';'     { $$ = opr('[', 2, id($2), con($4)); } 
        | CHAR VARIABLE '[' INTEGER ']' ';'    { $$ = opr('[', 2, id($2), con($4)); } 
        | DOUBLE VARIABLE '[' INTEGER ']' ';'  { $$ = opr('[', 2, id($2), con($4)); } 
        | CHAR VARIABLE '=' expr ';'     { $$ = opr(CHAR, 2, id($2), $4); } 
        | DOUBLE VARIABLE '=' expr ';'   { $$ = opr('=', 2, id($2), $4); } 
		| VARIABLE '[' expr ']' '=' expr ';'     { $$ = opr('[', 3, id($1), $3, $6); } 
        | WHILE '(' expr ')' stmt        { $$ = opr(WHILE, 2, $3, $5); } 
        | FOR '(' expr ';' expr ';' expr ')' stmt        { $$ = opr(FOR, 4, $3, $5, $7, $9); } 
        | IGNORE 				         { $$ = id(""); }
        | VOID VARIABLE '(' argument_list ')' stmt    { $$ = opr(VOID, 3, id($2), $4, $6); }
        | INT VARIABLE '(' argument_list ')' stmt    { $$ = opr(VOID, 3, id($2), $4, $6); }
        | VOID VARIABLE '(' ')' stmt    { $$ = opr(VOID, 3, id($2), id(""), $5); }
        | INT VARIABLE '(' ')' stmt    { $$ = opr(VOID, 3, id($2), id(""), $5); }
        | RETURN expr ';'                { $$ = opr(RETURN, 1, $2);}
        | IF '(' expr ')' stmt %prec IFX { $$ = opr(IF, 2, $3, $5); } 
        | IF '(' expr ')' stmt ELSE stmt { $$ = opr(IF, 3, $3, $5, $7); } 
        | '{' stmt_list '}'              { $$ = $2; } 
        | expr ';'                       { $$ = opr(SIMICOLON, 1, $1); }
        ;

stmt_list:
          stmt                  { $$ = $1; }
        | stmt_list stmt        { $$ = opr(';', 2, $1, $2); }
        ;

argument:
          INT VARIABLE '[' ']'     { $$ = id($2);}
        | CHAR VARIABLE '[' ']'    { $$ = id($2);}
        | DOUBLE VARIABLE '[' ']'  { $$ = id($2);}
        | INT VARIABLE          { $$ = id($2);}
        | CHAR VARIABLE         { $$ = id($2);}
        | DOUBLE VARIABLE       { $$ = id($2);}
        ;

argument_list:
          argument               { $$ = $1; }
        | argument_list ',' argument { $$ = opr(',', 2, $1, $3); }
        ;

expr:
          INTEGER               { $$ = con($1); } 
        | VARIABLE              { $$ = id($1); } 
        | STRLEN				{ $$ = id($1); }
        | VARIABLE '(' variable_list ')' {$$ = opr('(', 2, id($1), $3); }
        | VARIABLE '[' expr ']' { $$ = opr(']', 2, id($1), $3); }
        | '-' expr %prec UMINUS { $$ = opr(UMINUS, 1, $2); } 
        | expr '+' expr         { $$ = opr('+', 2, $1, $3); } 
        | expr '-' expr         { $$ = opr('-', 2, $1, $3); } 
        | expr '*' expr         { $$ = opr('*', 2, $1, $3); } 
        | expr '/' expr         { $$ = opr('/', 2, $1, $3); } 
        | expr '<' expr         { $$ = opr('<', 2, $1, $3); } 
        | expr '>' expr         { $$ = opr('>', 2, $1, $3); } 
        | expr '=' expr         { $$ = opr('=', 2, $1, $3); } 
        | expr GE expr          { $$ = opr(GE, 2, $1, $3); } 
        | expr LE expr          { $$ = opr(LE, 2, $1, $3); } 
        | expr NE expr          { $$ = opr(NE, 2, $1, $3); } 
        | expr EQ expr          { $$ = opr(EQ, 2, $1, $3); } 
        | '(' expr ')'          { $$ = $2; } 
        | expr ADDONE           { $$ = opr(ADDONE, 1, $1); } 
        | expr AND expr_list          { $$ = opr(AND, 2, $1, $3); } 
        | expr OR expr_list           { $$ = opr(OR, 2, $1, $3); } 
        ;

expr_list:
          expr               { $$ = $1; }
        | expr AND expr_list { $$ = opr(AND, 2, $1, $3); }
        | expr OR expr_list  { $$ = opr(OR, 2, $1, $3); }
        ;

variable_list:
		  VARIABLE 						{ $$ = id($1); }
		| variable_list ',' VARIABLE	{ $$ = opr(',', 2, $1, id($3)); }

%%

nodeType *con(int value) {
    nodeType *p;

    /* allocate node */
    if ((p = malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeCon;
    p->con.value = value;

    return p;
}

nodeType *id(char* s) {
    nodeType *p;

    /* allocate node */
    if ((p = malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeId;
    strcpy(p->id.s,s);
    return p;
}

nodeType *opr(int oper, int nops, ...) {
    va_list ap;
    nodeType *p;
    int i;

    /* allocate node, extending op array */
    if ((p = malloc(sizeof(nodeType) + (nops-1) * sizeof(nodeType *))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeOpr;
    p->opr.oper = oper;
    p->opr.nops = nops;
    va_start(ap, nops);
    for (i = 0; i < nops; i++)
    {
        p->opr.op[i] = va_arg(ap, nodeType*);
        //printf("argu:%d\n",p->opr.op[i]->type);
    }
    va_end(ap);
    return p;
}

/* free memory*/
void freeNode(nodeType *p) {
    int i;

    if (!p) return;
    if (p->type == typeOpr) {
        for (i = 0; i < p->opr.nops; i++)
            freeNode(p->opr.op[i]);
    }
    free (p);
}

void yyerror(char *s) {
    fprintf(stdout, "%s\n", s);
}

int main(void) {
    yyparse();
    return 0;
}
