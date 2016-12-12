%{
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "compiler.h"

/* prototypes */
nodeType *opr(int oper, int nops, ...);
nodeType *id(int i);
nodeType *con(int value);
void freeNode(nodeType *p);
int ex(nodeType *p,int enter);
int yylex(void);

void yyerror(char *s);
int sym[26];                    /* symbol table */
%}

%union {
    int iValue;                 /* integer value */
    char sIndex;                /* symbol table index */
    nodeType *nPtr;             /* node pointer */
};

%token <iValue> INTEGER
%token <sIndex> VARIABLE
%token WHILE IF PRINT INT
%nonassoc IFX
%nonassoc ELSE

%left GE LE EQ NE '>' '<'
%left '+' '-'
%left '*' '/'
%left OUT
%nonassoc UMINUS

%type <nPtr> stmt expr stmt_list

%%

program:
        function                { exit(0); }
        ;

function:
          function stmt         { ex($2,0); freeNode($2); }
        | /* NULL */
        ;

stmt:
          ';'                            { $$ = opr(';', 2, NULL, NULL); }//printf("fuck:1\n");}
        | expr ';'                       { $$ = $1; }//printf("fuck:2\n");}
        | PRINT OUT expr ';'             { $$ = opr(PRINT, 1, $3); }//printf("fuck:3\n");}
        | VARIABLE '=' expr ';'          { $$ = opr('=', 2, id($1), $3); }//printf("fuck:4\n");}
        | INT VARIABLE '=' expr ';'      { $$ = opr('=', 2, id($2), $4); }//printf("fuck:9\n");}
        | WHILE '(' expr ')' stmt        { $$ = opr(WHILE, 2, $3, $5); }//printf("fuck:5\n");}
        | IF '(' expr ')' stmt %prec IFX { $$ = opr(IF, 2, $3, $5); }//printf("fuck:6\n");}
        | IF '(' expr ')' stmt ELSE stmt { $$ = opr(IF, 3, $3, $5, $7); }//printf("fuck:7\n");}
        | '{' stmt_list '}'              { $$ = $2; }//printf("fuck:8\n");}
        ;

stmt_list:
          stmt                  { $$ = $1; }
        | stmt_list stmt        { $$ = opr(';', 2, $1, $2); }
        ;

expr:
          INTEGER               { $$ = con($1); }//printf("ex:1\n");}
        | VARIABLE              { $$ = id($1); }//printf("ex:2\n");}
        | '-' expr %prec UMINUS { $$ = opr(UMINUS, 1, $2); }//printf("ex:3\n");}
        | expr '+' expr         { $$ = opr('+', 2, $1, $3); }//printf("ex:4\n");}
        | expr '-' expr         { $$ = opr('-', 2, $1, $3); }//printf("ex:5\n");}
        | expr '*' expr         { $$ = opr('*', 2, $1, $3); }//printf("ex:6\n");}
        | expr '/' expr         { $$ = opr('/', 2, $1, $3); }//printf("ex:7\n");}
        | expr '<' expr         { $$ = opr('<', 2, $1, $3); }//printf("ex:8\n");}
        | expr '>' expr         { $$ = opr('>', 2, $1, $3); }//printf("ex:9\n");}
        | expr GE expr          { $$ = opr(GE, 2, $1, $3); }//printf("ex:10\n");}
        | expr LE expr          { $$ = opr(LE, 2, $1, $3); }//printf("ex:11\n");}
        | expr NE expr          { $$ = opr(NE, 2, $1, $3); }//printf("ex:12\n");}
        | expr EQ expr          { $$ = opr(EQ, 2, $1, $3); }//printf("ex:13\n");}
        | '(' expr ')'          { $$ = $2; }//printf("ex:14\n");}
        ;

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

nodeType *id(int i) {
    nodeType *p;

    /* allocate node */
    if ((p = malloc(sizeof(nodeType))) == NULL)
        yyerror("out of memory");

    /* copy information */
    p->type = typeId;
    p->id.i = i;

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