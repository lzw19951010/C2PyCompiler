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
        printf("%c", p->id.i + 'a');
        break;
    case typeOpr:
        switch(p->opr.oper) {
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
            printf("\n");
            printTab();
	    printf("while ");
            ex(p->opr.op[1]);
            printf(":\n");
            numOfTab++;
            ex(p->opr.op[3]);
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
                printf("\n");
		numOfTab--;
		printTab();
                printf("else:\n");
		numOfTab++;
                ex(p->opr.op[2]);
                printf("\n");
		numOfTab--;
            } else {
                /* if */
                printTab();
                printf("if ");
                ex(p->opr.op[0]);
	        printf(":\n");
		numOfTab++;	
                ex(p->opr.op[1]);
                printf("\n");
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
            //printf("sw:6\n");  
            printTab();
            printf("%c = ", p->opr.op[0]->id.i + 'a');
            ex(p->opr.op[1]);
	    printf("\n");
            break;
        case CHAR:     
            //printf("sw:6\n");  
            printTab();
            printf("%c = '", p->opr.op[0]->id.i + 'a');
            ex(p->opr.op[1]);
	    printf("'\n");
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
            ex(p->opr.op[0]);
            printf("UNIMUS");
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
