%{
#include <stdlib.h>
#include "compiler.h"
#include "y.tab.h"
void yyerror(char *);
%}

%%


[a-z]       { 
                yylval.sIndex = *yytext - 'a';
                return VARIABLE;
            }

0           {
                yylval.iValue = atoi(yytext);
                return INTEGER;
            }

[1-9][0-9]* {
                yylval.iValue = atoi(yytext);
                return INTEGER;
            }

[-()<>=+*/;{}.] {
                return *yytext;
             }

">="            return GE;
"<="            return LE;
"=="            return EQ;
"!="            return NE;
"while"         return WHILE;
"if"            return IF;
"else"          return ELSE;
"<<"            return OUT;
"int"           return INT;
"cout"         return PRINT;

[ \t\n]+        ;       /* ignore whitespace */

.               yyerror("");
%%
int yywrap(void) {
    return 1;
}