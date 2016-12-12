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

int ex(nodeType *p, int enter) {
    
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
            ex(p->opr.op[0],3);
            numOfTab++;
            ex(p->opr.op[1],1);
            numOfTab--;
            break;
        case IF:
	    //printf("%d\n",p->opr.nops);
            //ex(p->opr.op[0],0);
            //printf("sw:4\n");
            if (p->opr.nops > 2) {
                /* if else */
                printTab();
                printf("if ");
                ex(p->opr.op[0],3);
		numOfTab++;
                ex(p->opr.op[1],1);
		numOfTab--;
		printTab();
                printf("else:\n");
		numOfTab++;
                ex(p->opr.op[2],1);
		numOfTab--;
            } else {
                /* if */
                printTab();
                printf("if ");
                ex(p->opr.op[0],3);
		numOfTab++;	
                ex(p->opr.op[1],1);
		numOfTab--;
            }
            break;
        case PRINT:     
            //printf("sw:5\n");
	    printTab();
            printf("print(");
            ex(p->opr.op[0],2);
            break;
        case '=':     
            //printf("sw:6\n");  
            printf("%c = ", p->opr.op[0]->id.i + 'a');
            ex(p->opr.op[1],1);
            break;
        case UMINUS:   
            //printf("sw:7\n"); 
            ex(p->opr.op[0],0);
            printf("UNIMUS");
            break;
        default:
            //printf("sw:8\n");
            ex(p->opr.op[0],0);
            switch(p->opr.oper) {
            case '+':   printf("+"); break;
            case '-':   printf("\tsub\n"); break; 
            case '*':   printf("\tmul\n"); break;
            case '/':   printf("\tdiv\n"); break;
            case '<':   printf("<"); break;
            case '>':   printf(">"); break;
            case GE:    printf("\tcompGE\n"); break;
            case LE:    printf("\tcompLE\n"); break;
            case NE:    printf("\tcompNE\n"); break;
            case EQ:    printf("\tcompEQ\n"); break;
            }
            ex(p->opr.op[1],0);
        }
    }
    if(enter == 1)
	printf("\n");
    else if(enter == 2)
        printf(")\n");
    else if(enter == 3)
	printf(":\n"); 

    return 0;

}
