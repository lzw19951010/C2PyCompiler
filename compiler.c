#include <stdio.h>
#include "compiler.h"
#include "y.tab.h"

static int lbl;
int numOfTab = 0;

void printTab()
{
    int i;
    for(i = 0;i < numOfTab;i++)
    {
	printf("\t");
    }
}

int ex(nodeType *p) {
    
    int i;    

    if (!p) return 0;

    //printf("type:%d\n",p->type);
    switch(p->type) {
    case typeCon:       
        //printf("sw:1\n");
        printf("%d", p->con.value);
        break;
    case typeId:        
        //printf("sw:2\n");
        printf("%s", p->id.s);
        break;
    case typeOpr:
        switch(p->opr.oper) {
        case SIMICOLON:
            printTab();
        	ex(p->opr.op[0]);
        	printf("\n");
        	break;
        case '?':
            if (p->opr.nops == 2) {
                printTab();
                ex(p->opr.op[0]);
                printf(" = \"");
                ex(p->opr.op[1]);
                printf("\"\n");
            }
            else if (p->opr.nops == 3) {
                printTab();
                ex(p->opr.op[0]);
                //printf("[");
                //ex(p->opr.op[1]);
                printf(" = \"");
                ex(p->opr.op[2]);
                printf("\"\n");
            } 
            else{
                printf("\n");
            }
            break;
        case WHILE:
            //printf("sw:3\n");
            printTab();
	    printf("while ");
            ex(p->opr.op[0]);
            printf(":\n");
            numOfTab++;
            ex(p->opr.op[1]);
            numOfTab--;
            break;
        case FOR:
            //printf("sw:3\n");
            ex(p->opr.op[0]);
            printTab();
	    printf("while ");
            ex(p->opr.op[1]);
            printf(":\n");
            numOfTab++;
            ex(p->opr.op[3]);
            ex(p->opr.op[2]);
            numOfTab--;
            break;
        case VOID:
            //printf("sw:3\n");
            printTab();
            printf("def ");
            ex(p->opr.op[0]);
            printf("(");
            ex(p->opr.op[1]);
            printf("):\n");
            numOfTab++;
            ex(p->opr.op[2]);
            numOfTab--;
            break;
        case IF:
            //printf("sw:4\n");
            if (p->opr.nops > 2) {
                /* if else */
                printTab();
                printf("if ");
				ex(p->opr.op[0]);
				printf(":\n");
				numOfTab++;
				ex(p->opr.op[1]);
				numOfTab--;
				printTab();
				printf("else:\n");
				numOfTab++;
				ex(p->opr.op[2]);
				numOfTab--;
            } else {
                /* if */
                printTab();
                printf("if ");
                ex(p->opr.op[0]);
	        printf(":\n");
		numOfTab++;	
                ex(p->opr.op[1]);
		numOfTab--;
            }
            break;
        case PRINT:     
            //printf("sw:5\n");
	   		printTab();
            printf("print(");
            ex(p->opr.op[0]);
            printf(")\n");
            break;
        case INPUT:
            //printf("sw:9\n");  
	    	printTab();
            ex(p->opr.op[0]);
            printf(" = input()\n");
            break;
        case '=':     
            //printf("sw:7\n");  


                printTab();
                ex(p->opr.op[0]);
                printf(" = ");

                ex(p->opr.op[1]);

	        printf("\n");

            break;
        case '[':
        	if (p->opr.nops > 2) {
        		printTab();
        		ex(p->opr.op[0]);
        		printf("[");
        		ex(p->opr.op[1]);
        		printf("] = ");
        		ex(p->opr.op[2]);
        		printf("\n");
        	}
        	else {     
				printTab();
				printf("%s = [0] * (", p->opr.op[0]->id.s);
				ex(p->opr.op[1]);
				printf(")\n");
			}
            break;
        case ']':
            //printf("fuck\n");
	    printf("%s[", p->opr.op[0]->id.s);
	    ex(p->opr.op[1]);
            printf("]");
            break;
        case '(':
        	ex(p->opr.op[0]);
        	printf("(");
        	ex(p->opr.op[1]);
        	printf(")");
        	break;
        case ',':
            ex(p->opr.op[0]);
            printf(",");
            ex(p->opr.op[1]);
            break;
        case CHAR:     
            //printf("sw:6\n");  
            printTab();
            printf("%s = '", p->opr.op[0]->id.s);
            ex(p->opr.op[1]);
	    printf("'\n");
            break;
        case RETURN:
            printTab();
            printf("return ");
            ex(p->opr.op[0]);
            printf("\n");
            break;
        case AND:
            printf("(");
            ex(p->opr.op[0]);
            printf(" and ");
            ex(p->opr.op[1]);
            printf(")");
            break;
        case OR:
            printf("(");
            ex(p->opr.op[0]);
            printf(" or ");
            ex(p->opr.op[1]);
            printf(")");
            break;
        case ADDONE:
            //printf("sw:10\n");  
	    printTab();
            ex(p->opr.op[0]);
            printf(" += 1\n");
            break;
        case MINUONE:
            //printf("sw:10\n");  
	    printTab();
            ex(p->opr.op[0]);
            printf(" -= 1\n");
            break;
        case UMINUS:   
            //printf("sw:7\n"); 
            printf("-");
            ex(p->opr.op[0]);
            break;
        default:
            //printf("sw:8\n");
            ex(p->opr.op[0]);
            switch(p->opr.oper) {
            case '+':   printf("+"); break;
            case '-':   printf("-"); break; 
            case '*':   printf("*"); break;
            case '/':   printf("/"); break;
            case '<':   printf("<"); break;
            case '>':   printf(">"); break;
            case GE:    printf(">="); break;
            case LE:    printf("<="); break;
            case NE:    printf("!="); break;
            case EQ:    printf("=="); break;
            }
            ex(p->opr.op[1]);
        }
    }

    return 0;

}
