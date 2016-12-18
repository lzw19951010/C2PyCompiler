%{
#include <stdlib.h>
#include "compiler.h"
#include "y.tab.h"
void yyerror(char *);
%}

%%

"//"[^\n]*[\n]  {
    return IGNORE;
}

0           {
                yylval.iValue = atoi(yytext);
                return INTEGER;
            }

[1-9][0-9]* {
                yylval.iValue = atoi(yytext);
                return INTEGER;
            }

[-\[\]()<>=+*/,;{}."] {
                return *yytext;
             }

">="            return GE;
"<="            return LE;
"=="            return EQ;
"!="            return NE;
"&&"            return AND;
"||"            return OR;
"while"         return WHILE;
"for"           return FOR;
"if"            return IF;
"else"          return ELSE;
"<<"            return OUT;
">>"            return IN;
"++"            return ADDONE;
"--"            return MINUONE;
"int"           return INT;
"void"          return VOID;
"char"          return CHAR;
"double"        return DOUBLE;
"cout"          return PRINT;
"cin"           return INPUT;
"return"        return RETURN;

"strlen("[^\n)]*")" { 
                strcpy(yylval.sIndex,yytext+3);
                return STRLEN;
}

[a-zA-Z][_a-zA-Z0-9]* { 
                strcpy(yylval.sIndex,yytext);
                return VARIABLE;
}

"#include "[<|"][_a-zA-Z0-9.]*[>|"] {
	return IGNORE;
}

"using namespace "[_a-zA-Z0-9.]*[;] {
    return IGNORE;
}



[ \t\n']+        ;       /* ignore whitespace */

.               yyerror("UNKNOWNC");
%%
int yywrap(void) {
    return 1;
}
