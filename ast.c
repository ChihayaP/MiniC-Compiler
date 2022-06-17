#include "ast.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <gvc.h>
#include <gvcext.h>
#include "parser.tab.h"
#define MAXLENGTH 1000 
#define DX 3*sizeof(int)

int agnodeNum = 0;
char agnodeChar[100] = "";
struct node *astRoot;           //ast根节点
int LEV = 0;
int func_size;



struct symboltable
{
    struct symbol sym[MAXLENGTH];
    int index;
} SymT;

struct symbol_scope_begin 
{  /*当前作用域的符号在符号表的起始位置序号,这是一个栈结构，/每到达一个复合语句，将符号表的index值进栈，离开复合语句时，取其退栈值修改符号表的index值，完成删除该复合语句中的所有变量和临时变量*/
    int TX[30];
    int top;
} SymbolScope;

struct VarTable
{
    struct symbol sym[MAXLENGTH];
    int index;
} VarT;

struct TmpTable
{
    struct symbol sym[MAXLENGTH];
    int index;
} TmpT;

int searchVarTable(char *alias) 
{
    int i;
    if(VarT.index != 0) {
        for(i=VarT.index-1;i>=0;i--)
            if (!strcmp(VarT.sym[i].alias, alias))  
                return 1;
    } else
        return 0;
    return 0;
}

void symTToVarNameT()
{
    int i = 0, j = VarT.index;
    int k;
    for(i=SymT.index-1;i>=0;i--) {
        if(searchVarTable(SymT.sym[i].alias)==1) {
            break;
        }
    }
    for(i+=1,j=VarT.index; i<SymT.index; ++i) {
        strcpy(VarT.sym[j].name,SymT.sym[i].name);
        strcpy(VarT.sym[j].alias,SymT.sym[i].alias);
        if(SymT.sym[i].flag == 'V' && SymT.sym[i].level == 0) {
            VarT.sym[j].flag = 'G';
        } else {
            VarT.sym[j].flag=SymT.sym[i].flag;
        }
        VarT.sym[j].level = SymT.sym[i].level;
        VarT.sym[j].type = SymT.sym[i].type;
        VarT.sym[j].paramnum = SymT.sym[i].paramnum;
        VarT.sym[j].isArray = SymT.sym[i].isArray;
        VarT.sym[j].arrNum = SymT.sym[i].arrNum;
        for(k = 0; k < SymT.sym[i].arrNum; k++) {
            VarT.sym[j].arr[k] = SymT.sym[i].arr[k];
        }
        j++;
    }
    VarT.index = j;
}

void changeVarNameTable(int i, int j, int paramnum)
{
    int k,l,m;
    int varNum = 0;
    char cTmp[10] = "";
    char cTmp1[10] = "%l";
    char cTmp2[10] = "%t";
    for(k=i+1; k<j; k++) {
        if(VarT.sym[k].flag=='P') {
            memset(cTmp,0,sizeof(cTmp));
            memset(cTmp1,0,sizeof(cTmp1));
            memset(cTmp2,0,sizeof(cTmp2));
            strcpy(cTmp1, "%l");
            strcpy(cTmp2, "%t");
            itoa(varNum,cTmp,10);
            strcat(cTmp2,cTmp);
            strcpy(VarT.sym[k].paramName,cTmp2);
            itoa(varNum+paramnum,cTmp,10);
            strcat(cTmp1,cTmp);
            strcpy(VarT.sym[k].varName,cTmp1);
            varNum++;
        }
    }
    varNum += paramnum;
    for(k=i+1+paramnum; k<j; k++) {
        if(VarT.sym[k].flag=='V') {
            strcpy(TmpT.sym[TmpT.index].name,VarT.sym[k].name);
            strcpy(TmpT.sym[TmpT.index].alias,VarT.sym[k].alias);
            TmpT.sym[TmpT.index].flag=VarT.sym[k].flag;
            TmpT.sym[TmpT.index].level = VarT.sym[k].level;
            TmpT.sym[TmpT.index].type = VarT.sym[k].type;
            TmpT.sym[TmpT.index].isArray = VarT.sym[k].isArray;
            if(VarT.sym[k].isArray==1) {
                TmpT.sym[TmpT.index].arrNum = VarT.sym[k].arrNum;
                for(l = 0; l < VarT.sym[k].arrNum; l++) {
                    TmpT.sym[TmpT.index].arr[l] = VarT.sym[k].arr[l];
                }
            }
            TmpT.index++;
        } 
    }
    for(k=i+1+paramnum; k<j; k++) {
        if(VarT.sym[k].flag=='T') {
            strcpy(TmpT.sym[TmpT.index].name,VarT.sym[k].name);
            strcpy(TmpT.sym[TmpT.index].alias,VarT.sym[k].alias);
            TmpT.sym[TmpT.index].flag=VarT.sym[k].flag;
            TmpT.sym[TmpT.index].level = VarT.sym[k].level;
            TmpT.sym[TmpT.index].type = VarT.sym[k].type;
            TmpT.sym[TmpT.index].isArray = VarT.sym[k].isArray;
            if(VarT.sym[k].isArray==1) {
                TmpT.sym[TmpT.index].arrNum = VarT.sym[k].arrNum;
                for(l = 0; l < VarT.sym[k].arrNum; l++) {
                    TmpT.sym[TmpT.index].arr[l] = VarT.sym[k].arr[l];
                }
            }
            TmpT.index++;
        } 
    }
    for(k=j-1; k>i+paramnum; k--,TmpT.index--) {
        strcpy(VarT.sym[k].name,TmpT.sym[TmpT.index-1].name);
        strcpy(VarT.sym[k].alias,TmpT.sym[TmpT.index-1].alias);
        VarT.sym[k].flag=TmpT.sym[TmpT.index-1].flag;
        VarT.sym[k].level = TmpT.sym[TmpT.index-1].level;
        VarT.sym[k].type = TmpT.sym[TmpT.index-1].type;
        VarT.sym[k].isArray = TmpT.sym[TmpT.index-1].isArray;
        if(VarT.sym[k].isArray==1) {
            VarT.sym[k].arrNum = TmpT.sym[TmpT.index-1].arrNum;
            for(l = 0; l < TmpT.sym[TmpT.index-1].arrNum; l++) {
                VarT.sym[k].arr[l] = TmpT.sym[TmpT.index-1].arr[l];
            }
        }
    }
    for(k=i+1+paramnum;k<j;k++) {
        memset(cTmp,0,sizeof(cTmp));
        memset(cTmp1,0,sizeof(cTmp1));
        memset(cTmp2,0,sizeof(cTmp2));
        strcpy(cTmp1, "%l");
        strcpy(cTmp2, "%t");
        if(VarT.sym[k].flag=='V') {
            itoa(varNum,cTmp,10);
            strcat(cTmp1,cTmp);
            strcpy(VarT.sym[k].varName,cTmp1);
            varNum++;
        }
        if(VarT.sym[k].flag=='T') {
            itoa(varNum,cTmp,10);
            strcat(cTmp2,cTmp);
            strcpy(VarT.sym[k].varName,cTmp2);
            varNum++;
        }
    }
}

void changeFunNameTable()
{
    int i, j;
    char cTmp[33] = "";
    for(i=0;i<VarT.index;i++) {
        switch(VarT.sym[i].flag) {
            case 'G':
                memset(cTmp,0,sizeof(cTmp));
                strcpy(cTmp,"@");
                strcpy(VarT.sym[i].varName, strcat(cTmp,VarT.sym[i].name));
                break;
            case 'F':
                memset(cTmp,0,sizeof(cTmp));
                strcpy(cTmp,"@");
                strcpy(VarT.sym[i].varName, strcat(cTmp,VarT.sym[i].name));
                for(j=i+1;j<VarT.index;j++) {
                    if(VarT.sym[j].flag=='F' || VarT.sym[j].flag=='G')
                        break;
                }
                changeVarNameTable(i,j,VarT.sym[i].paramnum);
                i=j-1;
                break;
            default:
                break;
        }
    }
}

//符号表

struct node * mknode(node_kind kind,struct node *first,struct node *second, struct node *third,int pos ) 
{
    struct node *T=(struct node *)malloc(sizeof(struct node));
    T->kind=kind;
    T->ptr[0]=first;
    T->ptr[1]=second;
    T->ptr[2]=third;
    T->pos=pos;
    return T;
}



void storeAstRoot(struct node *T)
{
    astRoot = T;
    VarT.index = 0;
    TmpT.index = 0;
}

Agnode_t *draw_tree_node(struct node *T, Agraph_t *g, Agnode_t *parent_node)
{
    char labelTmp[100] = "";
    char nodeLabel[100] = "";
    int num;
    char tmpChar[100] = {0};
    Agnode_t *child_node;
    switch (T->kind) {
        case _COMP_FUNCDEF:
        case _GLO_DECL:
        case _FUNCFPARAM:
        case _BLOCKITEM:
        case _DECL:
        case _STMT:
        case _BLOCK:
        case _EXP_SEMI:
        case _SEMI:
        case _COND:
        case _LOREXP:
        case _LANDEXP:
        case _EQEXP:
        case _RELEXP:
        case _ADDEXP:
        case _MULEXP:
        case _UNARYEXP:
        case _PRIMARYEXP:
        case _EXP:
        case _NUMBER:
        case _LVAL:
            child_node = parent_node;
            break;
        case _INT_CONST:
            memset(agnodeChar,0,sizeof(agnodeChar));
            child_node = agnode(g, itoa(agnodeNum,agnodeChar,10), 1);
            agnodeNum++;
            num = T->type_int;
            memset(tmpChar, 0, sizeof(tmpChar));
            itoa(num, tmpChar, 10);
            strcpy(nodeLabel, tmpChar);
            if(child_node != NULL) {
                agsafeset(child_node, (char *)"label", (char *)nodeLabel, (char *)nodeLabel);
                agsafeset(child_node, (char *)"shape", (char *)"record", (char *)"ellipse");
            }
            if(parent_node != NULL) {
                Agedge_t *e = agedge(g, (Agnode_t *)parent_node, (Agnode_t *)child_node, NULL, 1);
            }
            break;
        default:
            memset(agnodeChar,0,sizeof(agnodeChar));
            child_node = agnode(g, itoa(agnodeNum,agnodeChar,10), 1);
            agnodeNum++;
            strcpy(nodeLabel, T->type_id);
            if(child_node != NULL) {
                agsafeset(child_node, (char *)"label", (char *)nodeLabel, (char *)nodeLabel);
                agsafeset(child_node, (char *)"shape", (char *)"record", (char *)"ellipse");
            }
            if(parent_node != NULL) {
                Agedge_t *e = agedge(g, (Agnode_t *)parent_node, (Agnode_t *)child_node, NULL, 1);
            }          
            break;
    }
    return child_node;
}

void draw_tree(struct node *T, Agraph_t *g, Agnode_t *parent_node)
{
    Agnode_t *node = NULL;
    if(T != NULL && g != NULL) {
        node = draw_tree_node(T, g, parent_node);
        for (int i = 0; i < 3; i++) {
            if(T->ptr[i] != NULL) {
                draw_tree(T->ptr[i], g, node);
            }
        }
    }
}

void drawAst()
{
    char funcName[] = "main";
    Agraph_t *g = agopen(funcName, Agdirected, NULL);
    if(NULL == g) {
        printf("agopen() failed\n");
        return;
    }
    agsafeset(g, "dpi", "600", "");
    draw_tree(astRoot, g, NULL);
    GVC_t * gv = gvContext();
    if(gv == NULL) {
        printf("gvContext() failed\n");
        agclose(g);
        return;
    }
    gvLayout(gv, g, "dot");
    gvRenderFilename(gv, g, "png", "main.png");
    agclose(g);
    gvFreeContext(gv);
}

char *returnIRName(char *alias)
{
    int i = 0;
    for(i=0;i<VarT.index;i++) {
        if(strcmp(alias,VarT.sym[i].alias)==0){
            return VarT.sym[i].varName;
        }
    }
    return NULL;
}

int returnVarTablePos(char *alias)
{
    int i = 0;
    for(i=0;i<VarT.index;i++) {
        if(strcmp(alias,VarT.sym[i].alias)==0){
            return i;
        }
    }
    return -1;
}

void prnIR(struct codenode *head){
    int i,j,k;
    char tmpstr1[32]="", tmpstr2[32]="";
    FILE *fp = fopen("./cmake-build-debug/test_ir.txt","a");
    char opnstr1[32],opnstr2[32],resultstr[32];
    struct codenode *h=head;
    struct codenode *t;
    for(i=11;i<VarT.index;i++) {
        if(VarT.sym[i].flag=='G') {
            if(VarT.sym[i].isArray==0)
                fprintf(fp,"declare i32 %s\n",VarT.sym[i].varName);
            else {
                memset(tmpstr1,0,sizeof(tmpstr1));
                memset(tmpstr1,0,sizeof(tmpstr2));
                for(j=0;j<VarT.sym[i].arrNum;j++) {
                    strcat(tmpstr1,"[");
                    strcat(tmpstr1,itoa(VarT.sym[i].arr[j],tmpstr2,10));
                    strcat(tmpstr1,"]");
                }
                fprintf(fp,"declare i32 %s%s\n",VarT.sym[i].varName,tmpstr1);
            }
        }
    }
    do {
        if (h->opn1.kind==INT) {
            sprintf(opnstr1,"%d",h->opn1.const_int);
        } else if (h->opn1.kind==ID) {
            if(h->opn1.id[0]=='t'&&VarT.sym[returnVarTablePos(h->opn1.id)].isArray==1) {
                sprintf(opnstr1,"*%s",returnIRName(h->opn1.id));
            } else {
                sprintf(opnstr1,"%s",returnIRName(h->opn1.id));
            }
        } else if (h->opn1.kind==LABEL) {
            sprintf(opnstr1,"%s",h->opn1.id);
        }
        if (h->opn2.kind==INT) {
            sprintf(opnstr2,"%d",h->opn2.const_int);
        } else if (h->opn2.kind==ID) {
            if(h->opn2.id[0]=='t'&&VarT.sym[returnVarTablePos(h->opn2.id)].isArray==1) {
                sprintf(opnstr2,"*%s",returnIRName(h->opn2.id));
            } else {
                sprintf(opnstr2,"%s",returnIRName(h->opn2.id));
            }
        } else if (h->opn2.kind==LABEL) {
            sprintf(opnstr2,"%s",h->opn2.id);
        }
        if (h->result.kind==ID) {
              sprintf(resultstr,"%s",returnIRName(h->result.id));
        } else {
            sprintf(resultstr,"%s",h->result.id);
        }
        char c[10];
        switch (h->op) {
            case ASSIGNOP:
                if(VarT.sym[returnVarTablePos(h->result.id)].isArray==1&&VarT.sym[returnVarTablePos(h->opn1.id)].isArray==0) {
                    fprintf(fp,"    *%s = %s\n",resultstr,opnstr1);
                } else 
                    fprintf(fp, "    %s = %s\n",resultstr,opnstr1);
                break;
            case _PLUS:
                fprintf(fp, "    %s = %s %s, %s\n",resultstr,"add",opnstr1,opnstr2);
                break;
            case _MINUS:
                fprintf(fp, "    %s = %s %s, %s\n",resultstr,"sub",opnstr1,opnstr2);
                break;
            case _MUL:
                fprintf(fp, "    %s = %s %s, %s\n",resultstr,"mul",opnstr1,opnstr2);
                break;
            case _DIV:
                fprintf(fp, "    %s = %s %s, %s\n",resultstr,"div",opnstr1,opnstr2);
                break;
            case _MOD:
                fprintf(fp, "    %s = %s %s, %s\n",resultstr,"mod",opnstr1,opnstr2);
                break;
            case _NEGA:
                fprintf(fp, "    %s = %s %s\n",resultstr,"neg",opnstr1);
                break;
            case AND:   
	        case OR:   
	        case RELOP: 
                if (h->op == AND)
                strcpy(c,"&&");
                else if (h->op == OR)
                strcpy(c,"||");
                else
                strcpy(c,h->result.rtype);
                fprintf(fp, "  %s = %s %s %s\n",resultstr,opnstr1,c,opnstr2);
                break;
            case FUNCTION: 
                if(h->result.type == INT) {
                    fprintf(fp, "define i32 @%s(",h->result.id);
                } else {
                    fprintf(fp, "define void @%s(",h->result.id);
                }
                for(i=0;i<VarT.index;i++) {
                    if(strcmp(VarT.sym[i].name,h->result.id)==0) {
                        break;
                    }
                }
                if(VarT.sym[i].paramnum == 0) {
                    fprintf(fp, ") {\n");
                } else {
                    if(VarT.sym[i+1].isArray==0) {
                        fprintf(fp,"i32 %s",VarT.sym[i+1].paramName);
                    } else {
                        memset(tmpstr1,0,sizeof(tmpstr1));
                        memset(tmpstr1,0,sizeof(tmpstr2));
                        for(k=0;k<VarT.sym[i+1].arrNum;k++) {
                            strcat(tmpstr1,"[");
                            strcat(tmpstr1,itoa(VarT.sym[i+1].arr[k],tmpstr2,10));
                            strcat(tmpstr1,"]");
                        }
                        fprintf(fp,"i32 %s%s",VarT.sym[i+1].paramName,tmpstr1);
                    }
                    for(j=1;j<VarT.sym[i].paramnum;j++) {
                        if(VarT.sym[i+1+j].isArray==0)
                            fprintf(fp,", i32 %s",VarT.sym[i+1+j].paramName);
                        else {
                            memset(tmpstr1,0,sizeof(tmpstr1));
                            memset(tmpstr1,0,sizeof(tmpstr2));
                            for(k=0;k<VarT.sym[i+1+j].arrNum;k++) {
                                strcat(tmpstr1,"[");
                                strcat(tmpstr1,itoa(VarT.sym[i+1+j].arr[k],tmpstr2,10));
                                strcat(tmpstr1,"]");
                            }
                            fprintf(fp,", i32 %s%s",VarT.sym[i+1+j].paramName,tmpstr1);
                        }
                    }
                    fprintf(fp, ") {\n");
                }
                j=i;
                for(i+=1;i<VarT.index;i++) {
                    if(VarT.sym[i].flag=='V') {
                        // fprintf(fp,"  declare i32 %s\n",VarT.sym[i].varName);
                        if(VarT.sym[i].isArray==0) {
                            if(VarT.sym[i].type==INT) {
                                fprintf(fp,"    declare i32 %s\n",VarT.sym[i].varName);
                            } else {
                                fprintf(fp,"    declare i1 %s\n",VarT.sym[i].varName); 
                            }
                        }
                        else {
                            memset(tmpstr1,0,sizeof(tmpstr1));
                            memset(tmpstr1,0,sizeof(tmpstr2));
                            for(k=0;k<VarT.sym[i].arrNum;k++) {
                                strcat(tmpstr1,"[");
                                strcat(tmpstr1,itoa(VarT.sym[i].arr[k],tmpstr2,10));
                                strcat(tmpstr1,"]");
                            }
                            fprintf(fp,"    declare i32 %s%s\n",VarT.sym[i].varName,tmpstr1);
                        }
                    }
                    if(VarT.sym[i].flag=='P') {
                        // fprintf(fp,"  declare i32 %s\n",VarT.sym[i].varName);
                        if(VarT.sym[i].isArray==0) {
                            if(VarT.sym[i].type==INT) {
                                fprintf(fp,"    declare i32 %s\n",VarT.sym[i].varName);
                            } else {
                                fprintf(fp,"    declare i1 %s\n",VarT.sym[i].varName); 
                            }
                        }
                        else {
                            memset(tmpstr1,0,sizeof(tmpstr1));
                            memset(tmpstr1,0,sizeof(tmpstr2));
                            strcat(tmpstr1,"[0]");
                            for(k=1;k<VarT.sym[i].arrNum;k++) {
                                strcat(tmpstr1,"[");
                                strcat(tmpstr1,itoa(VarT.sym[i].arr[k],tmpstr2,10));
                                strcat(tmpstr1,"]");
                            }
                            fprintf(fp,"    declare i32 %s%s\n",VarT.sym[i].varName,tmpstr1);
                        }
                    }
                    if(VarT.sym[i].flag=='T') {
                        if(VarT.sym[i].isArray==0) {
                            if(VarT.sym[i].type==INT) {
                                fprintf(fp,"    declare i32 %s\n",VarT.sym[i].varName);
                            } else {
                                fprintf(fp,"    declare i1 %s\n",VarT.sym[i].varName); 
                            }
                        } else {
                            fprintf(fp,"    declare i32* %s\n",VarT.sym[i].varName);
                        }
                    }
                    if(VarT.sym[i].flag=='F' || VarT.sym[i].flag=='G')
                        break;
                }
                fprintf(fp, "    entry\n");
                i=j;
                if(VarT.sym[i].paramnum != 0) {
                    for(j=0;j<VarT.sym[i].paramnum;j++) {
                        fprintf(fp,"    %s = %s\n",VarT.sym[i+1+j].varName,VarT.sym[i+1+j].paramName);
                    }
                }
                // printf("\nFUNCTION %s :\n",h->result.id);
                break;
            // case PARAM:    
            //     fprintf(fp, "  PARAM %s\n",h->result.id);
            //     break;
            case CALL:
                if(h->opn1.type == INT) {
                    fprintf(fp, "    %s = call i32 %s(",resultstr,opnstr1);
                } else {
                    fprintf(fp, "    call void %s(",opnstr1);
                }
                i=returnVarTablePos(h->opn1.id);
                if(VarT.sym[i].paramnum==0) {
                    fprintf(fp,")\n");
                } else {
                    t=h->next;
                    if(t->op!=ARG) {
                        break;
                    }
                    if (t->result.kind==ID) {
                        sprintf(resultstr,"%s",returnIRName(t->result.id));
                    } else {
                        sprintf(resultstr,"%s",t->result.id);
                    }
                    j=returnVarTablePos(t->result.id);
                    if(VarT.sym[j].isArray==0) {
                        fprintf(fp,"i32 %s",resultstr);
                    } else {
                        fprintf(fp,"i32* %s",resultstr);
                    }
                    t=t->next;
                    while(t->op==ARG) {
                        if (t->result.kind==ID) {
                            sprintf(resultstr,"%s",returnIRName(t->result.id));
                        } else {
                            sprintf(resultstr,"%s",t->result.id);
                        }
                        j=returnVarTablePos(t->result.id);
                        if(VarT.sym[j].isArray==0) {
                            fprintf(fp,",i32 %s",resultstr);
                        } else {
                            fprintf(fp,",i32* %s",resultstr);
                        }
                        t=t->next;
                    }
                    fprintf(fp,")\n");
                }
                break;
            case ARG:
                break;
            case LABEL:    
                fprintf(fp, "%s :\n",h->result.id);
                break;
            case RC_SIGN:    
                if(h->prior->op!=RETURN) {
                    fprintf(fp, "    exit\n");
                }
                fprintf(fp, "%s",h->result.id);
                break;
            case GOTO:     
                fprintf(fp, "    br %s\n",resultstr);
                break;
            case LE:      
                fprintf(fp, "    %s = cmp le %s, %s\n",resultstr,opnstr1,opnstr2);
                break;
            case LT:      
                fprintf(fp, "    %s = cmp lt %s, %s\n",resultstr,opnstr1,opnstr2);
                break;
            case GE:      
                fprintf(fp, "    %s = cmp ge %s, %s\n",resultstr,opnstr1,opnstr2);
                break;
            case GT:      
                fprintf(fp, "    %s = cmp gt %s, %s\n",resultstr,opnstr1,opnstr2);
                break;
            case EQ:       
                fprintf(fp, "    %s = cmp eq %s, %s\n",resultstr,opnstr1,opnstr2);
                break;
            case NE:
                fprintf(fp, "    %s = cmp ne %s, %s\n",resultstr,opnstr1,opnstr2);
                break;
            case BC:
                fprintf(fp, "    bc %s, label %s, label %s\n",opnstr1,opnstr2,resultstr);
                break;
            case RETURN:   
                if (h->result.kind)
                    fprintf(fp, "    exit %s\n",resultstr);
                else
                    fprintf(fp, "    exit\n");
                break;
            default:
                break;
        }
    h=h->next;
    } while (h!=head);
    fclose(fp);
}

char *strcat0(char *s1,char *s2) {
    static char result[10];
    strcpy(result,s1);
    strcat(result,s2);
    return result;
}

char *newAlias() {
    static int no=1;
    char s[10];
    itoa(no++,s,10);
    return strcat0("v",s);
}

char *newLabel() {
    static int no=1;
    char s[10];
    itoa(no++,s,10);
    return strcat0(".L",s);
}

char *newTemp() {
    static int no=1;
    char s[10];
    itoa(no++,s,10);
    return strcat0("temp",s);
}

//生成一条TAC代码的结点组成的双向循环链表，返回头指针
struct codenode *genIR(int op,struct opn opn1,struct opn opn2,struct opn result){
    struct codenode *h=(struct codenode *)malloc(sizeof(struct codenode));
    h->op=op;
    h->opn1=opn1;
    h->opn2=opn2;
    h->result=result;
    h->next=h->prior=h;
    return h;
}

//生成一条标号语句，返回头指针
struct codenode *genLabel(char *label){
    struct codenode *h=(struct codenode *)malloc(sizeof(struct codenode));
    h->op=LABEL;
    strcpy(h->result.id,label);
    h->next=h->prior=h;
    return h;
}

//生成GOTO语句，返回头指针
struct codenode *genGoto(char *label){
    struct codenode *h=(struct codenode *)malloc(sizeof(struct codenode));
    h->op=GOTO;
    strcpy(h->result.id,label);
    h->next=h->prior=h;
    return h;
}

void semanticError(int line,char *msg1,char *msg2){
    //这里可以只收集错误信息，最后在一次显示
    printf("On%dline,%s %s\n",line,msg1,msg2);
}

//显示符号表
void prnSymbol()
{
    int i=0;
    printf( "%6s %6s %6s  %6s %4s %6s\n","name","alias","LEV","type","flag","offset");
    char ptype[10];
    for(i=11;i<SymT.index;i++)
    {
        if (SymT.sym[i].type==INT)   
        {
            strcpy(ptype,"int");
        }
        printf( "%8s %6s %6d  %6s %4c %6d\n",SymT.sym[i].name,
                SymT.sym[i].alias,SymT.sym[i].level,
                ptype,
                SymT.sym[i].flag,SymT.sym[i].offset);
        strcpy(ptype,"");
    }
    printf( "\n"); 
}

void prnVarSymbol()
{
    FILE *fp = fopen("./cmake-build-debug/test.txt","a");
    int i=0;
    // printf( "%8s %6s %6s  %6s %4s %8s\n","name","alias","LEV","type","flag","varName");
    fprintf(fp, "%8s %6s %6s  %6s %4s %8s\n","name","alias","LEV","type","flag","varName");
    char ptype[10];
    for(i=11;i<VarT.index;i++)
    {
        if (VarT.sym[i].type==INT)   
        {
            strcpy(ptype,"int");
        }
        if (VarT.sym[i].type==BOOL)   
        {
            strcpy(ptype,"bool");
        }
        // printf( "%8s %6s %6d  %6s %4c %8s\n",VarT.sym[i].name,
        //         VarT.sym[i].alias,VarT.sym[i].level,
        //         ptype,
        //         VarT.sym[i].flag,VarT.sym[i].varName);
        fprintf(fp, "%8s %6s %6d  %6s %4c %8s\n",VarT.sym[i].name,
                VarT.sym[i].alias,VarT.sym[i].level,
                ptype,
                VarT.sym[i].flag,VarT.sym[i].varName);
        strcpy(ptype,"");
    }
    // printf( "\n");
    fprintf(fp, "\n");
    fclose(fp);  
}

int searchSymbolTable(char *name) 
{
    int i;
    for(i=SymT.index-1;i>=0;i--)
        if (!strcmp(SymT.sym[i].name, name))  
            return i;
    return -1;
}

int fillTemp(char *name,int level,int type,char flag,int offset) {
    strcpy(SymT.sym[SymT.index].name,"");
    strcpy(SymT.sym[SymT.index].alias,name);
    SymT.sym[SymT.index].level=level;
    SymT.sym[SymT.index].type=type;
    SymT.sym[SymT.index].flag=flag;
    SymT.sym[SymT.index].offset=offset;
    return SymT.index++; //返回的是临时变量在符号表中的位置序号
}

int fillSymbolTable(char *name, char *alias, int level, int type, char flag, int offset)
{
    int i;
    //符号查重
    for(i=SymT.index-1;SymT.sym[i].level==level||(level==0 && i>=0);i--) {
        if(level==0 && SymT.sym[i].level==1)
            continue;
        if(!strcmp(SymT.sym[i].name, name))
            return -1;
    }
    strcpy(SymT.sym[SymT.index].name, name);
    strcpy(SymT.sym[SymT.index].alias, alias);
    SymT.sym[SymT.index].level = level;
    SymT.sym[SymT.index].type = type;
    SymT.sym[SymT.index].flag = flag;
    SymT.sym[SymT.index].offset = offset;
    return SymT.index++;
}

struct codenode *merge(int num, ...)
{
    struct codenode *h1, *h2, *p, *t1, *t2;
    va_list ap;
    va_start(ap, num);
    h1 = va_arg(ap, struct codenode *);
    while(--num > 0) {
        h2 = va_arg(ap, struct codenode *);
        if (h1==NULL) 
            h1=h2;
        else if (h2){
            // if(h1->prior==NULL)
            //     return h2;
            t1=h1->prior;
            t2=h2->prior;
            t1->next=h2;
            t2->next=h1;
            h1->prior=t2;
            h2->prior=t1;
        }
    }
    va_end(ap);
    return h1;
}

int  matchParam(int i,struct node *T){
    int j,num=SymT.sym[i].paramnum;
    int type1,type2;
    if (num==0 && T==NULL) 
        return 1;
    for (j=1;j<num;j++) 
    {
        if (!T)
        {
            semanticError(T->pos,"", "Too few arguments to function call\n");
            return 0;
        }
        type1=SymT.sym[i+j].type;  //形参类型
        type2=T->ptr[0]->type;
        if (type1!=type2)
        {
            semanticError(T->pos,"", "parameter type mismatch\n");
            return 0;
        }
        T=T->ptr[1];
    }
    if (T->ptr[1]){ //num个参数已经匹配完，还有实参表达式
        semanticError(T->pos,"", "Too many arguments to function call\n");
        return 0;
    }
    return 1;
}

void extVarList(struct node *T) 
{
    int rtn, num = 1;
    int plusWidth = 1;
    int count = 0;
    struct node *tmp;
    switch(T->kind) {
        case _IDENT_ONLY_DECL:
            rtn = fillSymbolTable(T->type_id,newAlias(),LEV,T->type,'V',T->offset);
            if(rtn == -1) {
                semanticError(T->pos, T->type_id, "Variables are defined repeatedly\n");
            } else {
                T->place = rtn;
            }
            T->num = 1;
            break;
        case _IDENT_COMMA:
            rtn = fillSymbolTable(T->type_id,newAlias(),LEV,T->type,'V',T->offset);
            if(rtn == -1) {
                semanticError(T->pos, T->type_id, "Variables are defined repeatedly\n");
            } else {
                T->place = rtn;
            }
            T->ptr[0]->type = T->type;
            T->ptr[0]->offset=T->offset+T->width; //外部变量的偏移量向下传递
            T->ptr[0]->width=T->width;
            extVarList(T->ptr[0]);
            T->num = T->ptr[0]->num + 1;
            break;
        case _IDENT_VARARR_COMMA:
            rtn = fillSymbolTable(T->type_id,newAlias(),LEV,T->type,'V',T->offset*(T->ptr[0]->type_int));
            if(rtn == -1) {
                semanticError(T->pos, T->type_id, "Variables are defined repeatedly\n");
            } else {
                T->place = rtn;
            }
            if(T->ptr[0]->kind==_VARARR_ONLY) {
                T->width = 4*T->ptr[0]->type_int;
                SymT.sym[rtn].arr[0] = T->ptr[0]->type_int;
                SymT.sym[rtn].arrTmp[0] = 1;
                SymT.sym[rtn].isArray = 1;
                SymT.sym[rtn].arrNum = 1;
            } else {
                tmp = T->ptr[0];
                count = 0;
                SymT.sym[rtn].isArray = 1;
                SymT.sym[rtn].arrNum = 0;
                while(tmp->ptr[0] != NULL) {
                    SymT.sym[rtn].arr[count] = tmp->type_int;
                    tmp = tmp->ptr[0];
                    count++;
                    SymT.sym[rtn].arrNum++;
                }
                SymT.sym[rtn].arrTmp[SymT.sym[rtn].arrNum-1] = 1;
                for(int i=SymT.sym[rtn].arrNum-2; i>=0; i--) {
                    SymT.sym[rtn].arrTmp[i] = SymT.sym[rtn].arrTmp[i+1]*SymT.sym[rtn].arr[i+1];
                }
                T->width = 4*SymT.sym[rtn].arrTmp[0]*SymT.sym[rtn].arr[0];
            }
            T->ptr[1]->type = T->type;
            T->ptr[1]->offset = T->offset + T->width;
            T->ptr[1]->width = T->width;
            extVarList(T->ptr[1]);
            T->num = T->ptr[1]->num + 1;
            break;
        case _IDENT_VARARR:
            rtn = fillSymbolTable(T->type_id,newAlias(),LEV,T->type,'V',T->offset*(T->ptr[0]->type_int));
            if(rtn == -1) {
                semanticError(T->pos, T->type_id, "Variables are defined repeatedly\n");
            } else {
                T->place = rtn;
            }
            T->num = 1;
            if(T->ptr[0]->kind==_VARARR_ONLY) {
                T->width = 4*T->ptr[0]->type_int;
                SymT.sym[rtn].arr[0] = T->ptr[0]->type_int;
                SymT.sym[rtn].arrTmp[0] = 1;
                SymT.sym[rtn].isArray = 1;
                SymT.sym[rtn].arrNum = 1;
            } else {
                tmp = T->ptr[0];
                count = 0;
                SymT.sym[rtn].isArray = 1;
                SymT.sym[rtn].arrNum = 0;
                while(tmp != NULL) {
                    SymT.sym[rtn].arr[count] = tmp->type_int;
                    tmp = tmp->ptr[0];
                    count++;
                    SymT.sym[rtn].arrNum++;
                }
                SymT.sym[rtn].arrTmp[SymT.sym[rtn].arrNum-1] = 1;
                for(int i=SymT.sym[rtn].arrNum-2; i>=0; i--) {
                    SymT.sym[rtn].arrTmp[i] = SymT.sym[rtn].arrTmp[i+1]*SymT.sym[rtn].arr[i+1];
                }
                T->width = 4*SymT.sym[rtn].arrTmp[0]*SymT.sym[rtn].arr[0];
            }
            break;
    }
}

void Exp(struct node *T)
{
    int rtn, num, width, count;
    struct node *T0;
    struct opn opn1, opn2, result;
    if (T) {
        switch (T->kind) {
            case _INT_CONST:
                T->type = INT;
                T->place = fillTemp(newTemp(),LEV,T->type,'T',T->offset);
                opn1.kind = INT;
                opn1.const_int = T->type_int;
                result.kind = ID;
                strcpy(result.id, SymT.sym[T->place].alias);
                result.offset = SymT.sym[T->place].offset;
                T->code = genIR(ASSIGNOP,opn1,opn2,result);
                break;
            case _IDENT_ONLY:
                rtn = searchSymbolTable(T->type_id);
                if(rtn == -1) {
                    semanticError(T->pos,T->type_id,"The variable is undefined\n");
                }
                if(SymT.sym[rtn].isArray == 1) {
                    semanticError(T->pos,T->type_id, "Array names cannot be assigned values\n");
                }
                if(SymT.sym[rtn].flag == 'F') {
                    semanticError(T->pos,T->type_id, "It's the function name, the type does not match\n");
                } else {
                    T->place = rtn;
                    T->code = NULL;
                    T->type = SymT.sym[rtn].type;
                    T->offset = SymT.sym[rtn].offset;
                    T->width = 0;
                }
                break;
            case _PLUS:
            case _MINUS:
            case _MUL:
            case _DIV:
            case _MOD:
                T->ptr[0]->offset = T->offset;
                Exp(T->ptr[0]);
                T->ptr[1]->offset = T->offset + T->ptr[0]->width;
                Exp(T->ptr[1]);
                T->type = INT, T->width = T->ptr[0]->width + T->ptr[1]->width + 2;
                T->place=fillTemp(newTemp(),LEV,T->type,'T',T->offset+T->ptr[0]->width+T->ptr[1]->width);
                opn1.kind=ID; 
                strcpy(opn1.id,SymT.sym[T->ptr[0]->place].alias);
                opn1.type=T->ptr[0]->type;
                opn1.offset=SymT.sym[T->ptr[0]->place].offset;
                opn2.kind=ID; 
                strcpy(opn2.id,SymT.sym[T->ptr[1]->place].alias);
                opn2.type=T->ptr[1]->type;
                opn2.offset=SymT.sym[T->ptr[1]->place].offset;
                result.kind=ID; 
                strcpy(result.id,SymT.sym[T->place].alias);
                result.type=T->type;
                result.offset=SymT.sym[T->place].offset;
                T->code=merge(3,T->ptr[0]->code,T->ptr[1]->code,genIR(T->kind,opn1,opn2,result));
                break;
            case _NEGA:
                Exp(T->ptr[0]);
                T->type=T->ptr[0]->type;
                T->width=T->ptr[0]->width+4;
                T->ptr[0]->offset=T->offset;
                T->place=fillTemp(newTemp(),LEV,T->type,'T',T->offset);
                opn1.kind=ID;
                result.kind=ID;
                strcpy(opn1.id,SymT.sym[T->ptr[0]->place].alias);
                strcpy(result.id,SymT.sym[T->place].alias);
                T->code=merge(2,T->ptr[0]->code,genIR(T->kind,opn1,opn2,result));
                break;
            case _NOT:
                Exp(T->ptr[0]);
                T->type = T->ptr[0]->type;
                T->width = T->ptr[0]->width;
                T->place = fillTemp(newTemp(),LEV,T->type,'T',T->offset+T->ptr[0]->width);
                opn1.kind = ID;
                strcpy(opn1.id, SymT.sym[T->ptr[0]->place].alias);
                opn1.offset = SymT.sym[T->ptr[0]->place].offset;
                result.kind = ID;
                strcpy(result.id, SymT.sym[T->ptr[0]->place].alias);
                result.offset = SymT.sym[T->ptr[0]->place].offset;
                T->code = merge(2,T->code,genIR(NOT,opn1,opn2,result));
                break;
            case _AND:
            case _OR:
            case _RELOP:
                T->type = INT;
                T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
                Exp(T->ptr[0]);
                Exp(T->ptr[1]);
                T->width = T->ptr[0]->width + T->ptr[1]->width + 2;
                T->place = fillTemp(newTemp(),LEV,T->type,'T',T->offset+T->ptr[0]->width+T->ptr[1]->width);
                opn1.kind = ID;
                strcpy(opn1.id,SymT.sym[T->ptr[0]->place].alias);
                opn1.type = T->ptr[0]->type;
                opn1.offset = SymT.sym[T->ptr[0]->place].offset;
                opn2.kind = ID;
                strcpy(opn2.id,SymT.sym[T->ptr[1]->place].alias);
                opn2.type = T->ptr[1]->type;
                opn2.offset = SymT.sym[T->ptr[1]->place].offset;
                result.kind = ID;
                strcpy(result.id, SymT.sym[T->place].alias);
                result.type = T->type;
                T->code = merge(3,T->ptr[0]->code, T->ptr[1]->code, genIR(T->kind, opn1, opn2, result));
                T->width = T->ptr[0]->width + T->ptr[1]->width + 4;
                break;
            case _LVAL_ASSIGN:
                Exp(T->ptr[0]);
                // Exp(T->ptr[1]);
                //
                T->ptr[1]->offset = T->offset;
                Exp(T->ptr[1]);
                T->type = T->ptr[0]->type;
                T->width = T->ptr[1]->width;
                T->code = merge(2,T->ptr[0]->code,T->ptr[1]->code);
                opn1.kind = ID;
                strcpy(opn1.id, SymT.sym[T->ptr[1]->place].alias);
                opn1.offset = SymT.sym[T->ptr[1]->place].offset;
                result.kind = ID;
                strcpy(result.id, SymT.sym[T->ptr[0]->place].alias);
                result.offset = SymT.sym[T->ptr[0]->place].offset;
                T->code = merge(2,T->code,genIR(ASSIGNOP,opn1,opn2,result));
                break;
            case _IDENT_ARR:
                rtn = searchSymbolTable(T->type_id);
                int a, b;
                if (rtn == -1)
                {
                    semanticError(T->pos, "", "Array variables are undefined\n");
                }
                if(SymT.sym[rtn].arrNum == 1) {
                    Exp(T->ptr[0]->ptr[0]);
                    T->code = T->ptr[0]->ptr[0]->code;
                    opn1.kind = ID;
                    strcpy(opn1.id, SymT.sym[T->ptr[0]->ptr[0]->place].alias);
                    opn2.kind = INT;
                    opn2.const_int = 4;
                    result.kind = ID;
                    a = fillTemp(newTemp(),LEV,INT,'T',4);
                    strcpy(result.id, SymT.sym[a].alias);
                    T->code = merge(2,T->code,genIR(_MUL,opn1,opn2,result));
                    opn1.kind = ID;
                    strcpy(opn1.id, SymT.sym[rtn].alias);
                    opn2.kind = ID;
                    strcpy(opn2.id, SymT.sym[a].alias);
                    a = fillTemp(newTemp(),LEV,INT,'T',4);
                    SymT.sym[a].isArray = 1;
                    result.kind = ID;
                    strcpy(result.id, SymT.sym[a].alias);
                    T->code = merge(2,T->code,genIR(_PLUS,opn1,opn2,result));
                    T->place = a;
                } else {
                    T0=T->ptr[0];
                    count = 0;
                    Exp(T0->ptr[0]);
                    T->code = T0->ptr[0]->code;
                    opn1.kind=ID;
                    strcpy(opn1.id,SymT.sym[T0->ptr[0]->place].alias);
                    opn2.kind=INT;
                    opn2.const_int=SymT.sym[rtn].arrTmp[count];
                    count++;
                    result.kind=ID;
                    a=fillTemp(newTemp(),LEV,INT,'T',4);
                    result.kind=ID;
                    strcpy(result.id,SymT.sym[a].alias);
                    T->code=merge(2,T->code,genIR(_MUL,opn1,opn2,result));
                    T0=T0->ptr[1];
                    while(T0!=NULL) {
                        Exp(T0->ptr[0]);
                        T->code=merge(2,T->code,T0->ptr[0]->code);
                        opn1.kind=ID;
                        strcpy(opn1.id,SymT.sym[T0->ptr[0]->place].alias);
                        opn2.kind=INT;
                        opn2.const_int=SymT.sym[rtn].arrTmp[count];
                        count++;
                        result.kind=ID;
                        b=fillTemp(newTemp(),LEV,INT,'T',4);
                        result.kind=ID;
                        strcpy(result.id,SymT.sym[b].alias);
                        T->code=merge(2,T->code,genIR(_MUL,opn1,opn2,result));
                        opn1.kind=ID;
                        opn2.kind=ID;
                        strcpy(opn1.id,SymT.sym[a].alias);
                        strcpy(opn2.id,SymT.sym[b].alias);
                        result.kind=ID;
                        a=fillTemp(newTemp(),LEV,INT,'T',4);
                        strcpy(result.id,SymT.sym[a].alias);
                        T->code=merge(2,T->code,genIR(_PLUS,opn1,opn2,result));
                        T0=T0->ptr[1];
                    }
                    opn1.kind = ID;
                    strcpy(opn1.id, SymT.sym[a].alias);
                    opn2.kind = INT;
                    opn2.const_int = 4;
                    result.kind = ID;
                    a = fillTemp(newTemp(),LEV,INT,'T',4);
                    strcpy(result.id, SymT.sym[a].alias);
                    T->code = merge(2,T->code,genIR(_MUL,opn1,opn2,result));
                    opn1.kind = ID;
                    strcpy(opn1.id, SymT.sym[rtn].alias);
                    opn2.kind = ID;
                    strcpy(opn2.id, SymT.sym[a].alias);
                    a = fillTemp(newTemp(),LEV,INT,'T',4);
                    SymT.sym[a].isArray = 1;
                    result.kind = ID;
                    strcpy(result.id, SymT.sym[a].alias);
                    T->code = merge(2,T->code,genIR(_PLUS,opn1,opn2,result));
                    T->place = a;
                }
                break;
            case _FUNC_CALL:
                rtn=searchSymbolTable(T->type_id);
                if(rtn==-1) {
                    semanticError(T->pos,T->type_id,"The function is undefined\n");
                    break;
                }
                if(SymT.sym[rtn].flag!='F') {
                    semanticError(T->pos,T->type_id,"Not a function\n");
                    break;
                }
                T->type=SymT.sym[rtn].type;
                width=4;
                if(T->ptr[0]!=NULL) {
                    T->ptr[0]->offset=T->offset;
                    Exp(T->ptr[0]);
                    T->width=T->ptr[0]->width+width;
                    T->code=T->ptr[0]->code;
                } else {
                    T->width=width;
                    T->code=NULL;
                }
                if(T->ptr[0]==NULL&&SymT.sym[rtn].paramnum>0) {
                    semanticError(T->pos,T->type_id,"There are too few function call parameters\n");
                } else {
                    matchParam(rtn,T->ptr[0]);
                }
                if(SymT.sym[rtn].type==INT) {
                    T->place=fillTemp(newTemp(),LEV,INT,'T',T->offset+T->width-width);
                    opn1.kind=ID;
                    opn1.type=SymT.sym[rtn].type;
                    rtn=searchSymbolTable(T->type_id);
                    strcpy(opn1.id,SymT.sym[rtn].alias);
                    result.kind=ID;
                    strcpy(result.id,SymT.sym[T->place].alias);
                    T->code=merge(2,T->code,genIR(CALL,opn1,opn2,result));
                }
                else if(SymT.sym[rtn].type==VOID) {
                    opn1.kind=ID;
                    opn1.type=SymT.sym[rtn].type;
                    rtn=searchSymbolTable(T->type_id);
                    strcpy(opn1.id,SymT.sym[rtn].alias);
                    T->code=merge(2,T->code,genIR(CALL,opn1,opn2,result));
                }
                T0=T->ptr[0];
                while(T0!=NULL) {
                    result.kind=ID;
                    strcpy(result.id,SymT.sym[T0->ptr[0]->place].alias);
                    T->code=merge(2,T->code,genIR(ARG,opn1,opn2,result));
                    T0=T0->ptr[1];
                }
                break;
            case _ARGS:
                T->ptr[0]->offset=T->offset;
                if(T->ptr[0]->kind==_IDENT_ONLY) {
                    rtn = searchSymbolTable(T->ptr[0]->type_id);
                    if(SymT.sym[rtn].isArray==0) {
                        opn1.kind=ID;
                        strcpy(opn1.id,SymT.sym[rtn].alias);
                        result.kind=ID;
                        rtn=fillTemp(newTemp(),LEV,INT,'T',T->ptr[0]->offset);
                        strcpy(result.id,SymT.sym[rtn].alias);
                        T->ptr[0]->code=genIR(ASSIGNOP,opn1,opn2,result);
                    } else {
                        opn1.kind=ID;
                        strcpy(opn1.id,SymT.sym[rtn].alias);
                        result.kind=ID;
                        rtn=fillTemp(newTemp(),LEV,INT,'T',T->ptr[0]->offset);
                        SymT.sym[rtn].isArray=1;
                        strcpy(result.id,SymT.sym[rtn].alias);
                        T->ptr[0]->code=genIR(ASSIGNOP,opn1,opn2,result);
                    }
                    T->ptr[0]->place=rtn;
                } else {
                    Exp(T->ptr[0]);
                }
                T->width=T->ptr[0]->width;
                T->code=T->ptr[0]->code;
                if(T->ptr[1]!=NULL) {
                    T->ptr[1]->offset=T->offset+T->ptr[0]->width;
                    Exp(T->ptr[1]);
                    T->width=T->ptr[1]->width;
                    T->code=merge(2,T->code,T->ptr[1]->code);
                }
                break;
            case _EXP_SEMI:
                if(T->ptr[0]->kind==_FUNC_CALL) {
                    Exp(T->ptr[0]);
                    T->code=T->ptr[0]->code;
                }
                T->code = NULL;
                break;
            
        }
    }
}

void boolExp(struct node *T)
{
    struct opn opn1, opn2, result;
    int op;
    int rtn;
    if (T) {
        switch(T->kind) {
            case _NEGA:
                if(T->ptr[0]->kind==_IDENT_ONLY || T->ptr[0]->kind==_INT_CONST) {
                    Exp(T->ptr[0]);
                    T->type=T->ptr[0]->type;
                    T->width=T->ptr[0]->width+4;
                    T->ptr[0]->offset=T->offset;
                    T->place=fillTemp(newTemp(),LEV,T->type,'T',T->offset);
                    opn1.kind=ID;
                    result.kind=ID;
                    strcpy(opn1.id,SymT.sym[T->ptr[0]->place].alias);
                    strcpy(result.id,SymT.sym[T->place].alias);
                    T->code=merge(2,T->ptr[0]->code,genIR(T->kind,opn1,opn2,result));
                } else {
                    boolExp(T->ptr[0]);
                    T->code=T->ptr[0]->code;
                    T->place=T->ptr[0]->place;
                }
                break;
            case _RELOP:
                T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
                Exp(T->ptr[0]);
                T->width = T->ptr[0]->width;
                Exp(T->ptr[1]);
                if (T->width<T->ptr[1]->width) 
                    T->width=T->ptr[1]->width;
                opn1.kind=ID; 
                strcpy(opn1.id,SymT.sym[T->ptr[0]->place].alias);
                opn1.offset=SymT.sym[T->ptr[0]->place].offset;
                opn2.kind=ID; 
                strcpy(opn2.id,SymT.sym[T->ptr[1]->place].alias);
                opn2.offset=SymT.sym[T->ptr[1]->place].offset;
                rtn=fillTemp(newTemp(),LEV,BOOL,'T',T->offset);
                result.kind=ID; 
                strcpy(result.id,SymT.sym[rtn].alias);
                if(strcmp(T->type_id, "<") == 0) {
                    op = LT;
                } else if (strcmp(T->type_id, "<=") == 0) {
                    op = LE;
                } else if (strcmp(T->type_id, ">") == 0) {
                    op = GT;
                } else if (strcmp(T->type_id, ">=") == 0) {
                    op = GE;
                } else if (strcmp(T->type_id, "==") == 0) {
                    op = EQ;
                } else if (strcmp(T->type_id, "!=") == 0) {
                    op = NE;
                }
                T->code = genIR(op,opn1,opn2,result);
                op = BC;
                opn1.kind=ID;
                strcpy(opn1.id,SymT.sym[rtn].alias);
                opn1.offset=SymT.sym[rtn].offset;
                opn2.kind=LABEL; 
                strcpy(opn2.id,T->Etrue);
                result.kind=LABEL;
                strcpy(result.id,T->Efalse);
                T->code = merge(4,T->ptr[0]->code,T->ptr[1]->code,T->code,genIR(op,opn1,opn2,result));
                break;
            case _AND:
            case _OR:
                if (T->kind==_AND) {
                    strcpy(T->ptr[0]->Etrue,newLabel());
                    strcpy(T->ptr[0]->Efalse,T->Efalse);
                }
                else {
                    strcpy(T->ptr[0]->Etrue,T->Etrue);
                    strcpy(T->ptr[0]->Efalse,newLabel());
                }
                strcpy(T->ptr[1]->Etrue,T->Etrue);
                strcpy(T->ptr[1]->Efalse,T->Efalse);
                T->ptr[0]->offset=T->ptr[1]->offset=T->offset;
                boolExp(T->ptr[0]);
                T->width=T->ptr[0]->width;
                boolExp(T->ptr[1]);
                if (T->width<T->ptr[1]->width) 
                    T->width=T->ptr[1]->width;
                if(T->kind==_AND) {
                    T->code = merge(3, T->ptr[0]->code, genLabel(T->ptr[0]->Etrue), T->ptr[1]->code);
                } else {
                    T->code = merge(3, T->ptr[0]->code, genLabel(T->ptr[0]->Efalse), T->ptr[1]->code);
                }
                break;
            case _INT_CONST:
                if(T->type_int != 0) {
                    T->code = genGoto(T->Etrue);
                } else {
                    T->code = genGoto(T->Efalse);
                }
                T->width = 0;
                break;
            case _IDENT_ONLY:
                rtn = searchSymbolTable(T->type_id);
                if (rtn==-1)
                    semanticError(T->pos,T->type_id, "The variable is undefined\n");
                if (SymT.sym[rtn].flag=='F')
                    semanticError(T->pos,T->type_id, "It's the function name, the type does not match\n");
                else {
                    opn1.kind=ID; 
                    strcpy(opn1.id,SymT.sym[rtn].alias);
                    opn1.offset=SymT.sym[rtn].offset;
                    opn2.kind=INT; 
                    opn2.const_int=0;
                    rtn=fillTemp(newTemp(),LEV,BOOL,'T',T->offset);
                    result.kind=ID; 
                    strcpy(result.id,SymT.sym[rtn].alias);
                    T->code=genIR(NE,opn1,opn2,result);
                    op = BC;
                    opn1.kind=ID;
                    strcpy(opn1.id,SymT.sym[rtn].alias);
                    opn1.offset=SymT.sym[rtn].offset;
                    opn2.kind=LABEL; 
                    strcpy(opn2.id,T->Etrue);
                    result.kind=LABEL;
                    strcpy(result.id,T->Efalse);
                    T->code=merge(2,T->code,genIR(op,opn1,opn2,result));
                }
                T->width=0;
                break;
            case _NOT:
                strcpy(T->ptr[0]->Etrue,T->Efalse);
                strcpy(T->ptr[0]->Efalse,T->Etrue);
                boolExp(T->ptr[0]);
                T->code=T->ptr[0]->code;
                break;
            
        }
    }
}

//语法分析，生成符号表
void semanticAnalysis(struct node *T)
{
    int rtn, width, num, count;
    struct node *T0, *tmp;
    struct opn opn1, opn2, result;
    if(T) {
        switch(T->kind) {
            case _COMP_FUNCDEF:
            case _GLO_DECL:
                if(!T->ptr[0])
                    break;
                T->ptr[0]->offset = T->offset;
                semanticAnalysis(T->ptr[0]);
                T->code = T->ptr[0]->code;
                break;
            case _COMP_FUNCDEF_COMP:
            case _GLO_DECL_COMP:
                if(!T->ptr[0])
                    break;
                T->ptr[0]->offset = T->offset;
                semanticAnalysis(T->ptr[0]);
                T->code = T->ptr[0]->code;
                T->ptr[1]->offset = T->ptr[0]->offset + T->ptr[0]->width;
                semanticAnalysis(T->ptr[1]);
                T->code = merge(2,T->code,T->ptr[1]->code);
                break;
            case _VARDECL:
                T->ptr[0]->type = T->type;
                T->ptr[0]->offset = T->offset;
                T->ptr[0]->width = 4;
                extVarList(T->ptr[0]);
                T->width = 4*T->ptr[0]->num;
                T->code = NULL;
                break;
            case _FUNCDEF:
                T->width = 0;
                T->offset = DX;
                rtn = fillSymbolTable(T->type_id,newAlias(),LEV,T->type,'F',0);
                if(rtn == -1) {
                    semanticError(T->pos,T->type_id,"The function is defined repeatedly\n");
                    break;
                } else
                    T->place = rtn;
                result.kind = ID;
                strcpy(result.id,T->type_id);
                result.offset = rtn;
                result.type = T->type;
                T->code = genIR(FUNCTION,opn1,opn2,result);
                SymT.sym[rtn].paramnum = 0;
                T->ptr[0]->offset = T->offset;
                strcpy(T->ptr[0]->Snext, "}\n");
                semanticAnalysis(T->ptr[0]);
                SymT.sym[T->place].offset = T->offset + T->ptr[0]->width;
                strcpy(result.id,T->ptr[0]->Snext);
                result.kind=ID;
                T->code = merge(3,T->code,T->ptr[0]->code,genIR(RC_SIGN,opn1,opn2,result));
                // T->code = merge(2,T->code,T->ptr[0]->code);
                break;
            case _FUNCDEF_PARAMS:
                T->width = 0;
                T->offset = DX;
                rtn = fillSymbolTable(T->type_id,newAlias(),LEV,T->type,'F',0);
                if(rtn == -1) {
                    semanticError(T->pos,T->type_id,"The function is defined repeatedly\n");
                    break;
                } else
                    T->place = rtn;
                result.kind = ID;
                strcpy(result.id,T->type_id);
                result.offset = rtn;
                result.type = T->type;
                T->code = genIR(FUNCTION,opn1,opn2,result);
                T->ptr[0]->offset = T->offset;
                semanticAnalysis(T->ptr[0]);
                SymT.sym[rtn].paramnum = T->ptr[0]->num;
                T->width += T->ptr[0]->width;
                T->ptr[1]->offset = T->offset;
                // strcpy(T->ptr[1]->Snext, newLabel());
                strcpy(T->ptr[0]->Snext, "}\n");
                semanticAnalysis(T->ptr[1]);
                if(T->ptr[0]->ptr[0] != NULL) {
                    SymT.sym[T->place].offset = T->offset + T->ptr[1]->width;
                    strcpy(result.id,T->ptr[0]->Snext);
                    result.kind=ID;
                    T->code = merge(3,T->code,T->ptr[1]->code,genIR(RC_SIGN,opn1,opn2,result));
                    // T->code = merge(3,T->code,T->ptr[1]->code,genLabel(T->ptr[1]->Snext));
                    // T->code = merge(2,T->code,T->ptr[0]->code);
                } else {
                    SymT.sym[T->place].offset = T->offset + 0;
                }
                break;
            case _FUNCFPARAM:
            case _FUNCFPARAM_COMMA:
                T->ptr[0]->offset = T->offset;
                semanticAnalysis(T->ptr[0]);
                if(T->ptr[1]) {
                    T->ptr[1]->offset = T->offset + T->ptr[0]->width;
                    semanticAnalysis(T->ptr[1]);
                    T->num = T->ptr[0]->num + T->ptr[1]->num;
                    T->width = T->ptr[0]->width + T->ptr[1]->width;
                    T->code = merge(2,T->ptr[0]->code,T->ptr[1]->code);
                } else {
                    T->num = T->ptr[0]->num;
                    T->width = T->ptr[0]->width;
                    T->code = T->ptr[0]->code;
                }
                break;
            case _PARAM:
                rtn = fillSymbolTable(T->type_id,newAlias(),1,T->ptr[0]->type,'P',T->offset);
                if(rtn == -1) {
                    semanticError(T->pos,T->type_id,"Parameter names are defined repeatedly\n");
                } else
                T->place = rtn;
                T->num = 1;
                T->width = 4;
                T->code = NULL;
                // result.kind = ID;
                // strcpy(result.id, SymT.sym[rtn].alias);
                // result.offset = T->offset;
                // T->code=genIR(PARAM,opn1,opn2,result);
                break;
            case _PARAM_VARARR:
                rtn = fillSymbolTable(T->type_id,newAlias(),1,T->ptr[0]->type,'P',T->offset);
                if(rtn == -1) {
                    semanticError(T->pos,T->type_id,"Parameter names are defined repeatedly\n");
                } else
                    T->place = rtn;
                T->num = 1;
                if(T->ptr[1]->kind==_VARARR_ONLY) {
                    T->width = 4*T->ptr[1]->type_int;
                    SymT.sym[rtn].arr[0] = T->ptr[1]->type_int;
                    SymT.sym[rtn].isArray = 1;
                    SymT.sym[rtn].arrNum = 1;
                } else {
                    tmp = T->ptr[1];
                    count = 0;
                    SymT.sym[rtn].isArray = 1;
                    SymT.sym[rtn].arrNum = 0;
                    while(tmp != NULL) {
                        SymT.sym[rtn].arr[count] = tmp->type_int;
                        tmp = tmp->ptr[0];
                        count++;
                        SymT.sym[rtn].arrNum++;
                    }
                    T->width = 4;
                }
                T->code = NULL;
                break;
            case _PARAM_NULL:
                rtn = fillSymbolTable(T->type_id,newAlias(),1,T->ptr[0]->type,'P',T->offset);
                if(rtn == -1) {
                    semanticError(T->pos,T->type_id,"Parameter names are defined repeatedly\n");
                } else
                    T->place = rtn;
                T->num = 1;
                if (T->ptr[1]==NULL) {
                    SymT.sym[rtn].arr[0]=0;
                    SymT.sym[rtn].isArray=1;
                    SymT.sym[rtn].arrNum=1;
                } else {
                    if(T->ptr[1]->kind==_VARARR_ONLY) {
                        T->width = 4*T->ptr[1]->type_int;
                        SymT.sym[rtn].arr[0] = 0;
                        SymT.sym[rtn].arr[1] = T->ptr[1]->type_int;
                        SymT.sym[rtn].isArray = 1;
                        SymT.sym[rtn].arrNum = 2;
                    } else {
                        tmp = T->ptr[1];
                        count = 1;
                        SymT.sym[rtn].isArray = 1;
                        SymT.sym[rtn].arr[0] = 0;
                        SymT.sym[rtn].arrNum = 1;
                        while(tmp != NULL) {
                            SymT.sym[rtn].arr[count] = tmp->type_int;
                            tmp = tmp->ptr[0];
                            count++;
                            SymT.sym[rtn].arrNum++;
                        }
                        T->width = 4;
                    }
                }
                T->code = NULL;
                break;
            case _BLOCKITEM:
            case _BLOCKITEMNULL:
                LEV++;
                SymbolScope.TX[SymbolScope.top++] = SymT.index;
                T->width = 0;
                T->code =  NULL;
                // if(T->ptr[0]) {
                //     T->ptr[0]->offset = T->offset;
                //     semanticAnalysis(T->ptr[0]);
                //     T->width += T->ptr[0]->width;
                //     T->code = T->ptr[0]->code;
                // }
                // if(T->ptr[1]) {
                //     T->ptr[1]->offset = T->offset + T->width;
                //     strcpy(T->ptr[1]->Snext,T->Snext);
                //     semanticAnalysis(T->ptr[1]);
                //     T->width += T->ptr[1]->width;
                //     T->code = merge(2,T->code,T->ptr[1]->code);
                // }
                if(T->ptr[0]) {
                    T->ptr[0]->offset = T->offset + T->width;
                    strcpy(T->ptr[0]->Snext,T->Snext);
                    semanticAnalysis(T->ptr[0]);
                    T->width += T->ptr[0]->width;
                    T->code = merge(2,T->code,T->ptr[0]->code);
                }
                prnSymbol();
                symTToVarNameT();
                LEV--;
                SymT.index = SymbolScope.TX[--SymbolScope.top];
                break;
            case _BLOCKITEMLIST:
                strcpy(T->ptr[0]->Snext,T->Snext);
                semanticAnalysis(T->ptr[0]);
                T->code = T->ptr[0]->code;
                T->width = T->ptr[0]->width;
                if(T->ptr[1]) {
                    strcpy(T->ptr[1]->Snext, T->Snext);
                    T->ptr[1]->offset = T->offset;
                    semanticAnalysis(T->ptr[1]);
                    T->code=merge(2,T->code,T->ptr[1]->code);
                    if(T->ptr[1]->width > T->width)
                        T->width = T->ptr[1]->width;
                }
                break;
            case _BLOCKITEM_:
                T->width = 0;
                T->code =  NULL;
                if(T->ptr[0]) {
                    T->ptr[0]->offset = T->offset;
                    semanticAnalysis(T->ptr[0]);
                    T->width += T->ptr[0]->width;
                    T->code = T->ptr[0]->code;
                }
                if(T->ptr[1]) {
                    T->ptr[1]->offset = T->offset + T->width;
                    strcpy(T->ptr[1]->Snext,T->Snext);
                    semanticAnalysis(T->ptr[1]);
                    T->width += T->ptr[1]->width;
                    T->code = merge(2,T->code,T->ptr[1]->code);
                }
                break;
            case _DECLLIST:
                T->code = NULL;
                if(T->ptr[0]) {
                    T->ptr[0]->offset = T->offset;
                    semanticAnalysis(T->ptr[0]);
                    T->code = T->ptr[0]->code;
                    T->width = T->ptr[0]->width;
                }
                if(T->ptr[1]) {
                    T->ptr[1]->offset = T->offset + T->ptr[0]->width;
                    semanticAnalysis(T->ptr[1]);
                    T->code = merge(2, T->code, T->ptr[1]->code);
                    T->width += T->ptr[1]->width;
                }
                break;
            case _STMTLIST:
                if(T->ptr[0] == NULL) {
                    T->code = NULL;
                    T->width = 0;
                    break;
                }
                if(T->ptr[1]) 
                    strcpy(T->ptr[0]->Snext, newLabel());
                else
                    strcpy(T->ptr[0]->Snext, T->Snext);
                T->ptr[0]->offset = T->offset;
                semanticAnalysis(T->ptr[0]);
                T->code = T->ptr[0]->code;
                T->width = T->ptr[0]->width;
                if(T->ptr[1]) {
                    strcpy(T->ptr[1]->Snext, T->Snext);
                    T->ptr[1]->offset = T->offset;
                    semanticAnalysis(T->ptr[1]);
                    if(T->ptr[0]->kind==_WHILE || T->ptr[0]->kind==_IF_ELSE || T->ptr[0]->kind==_IF) {
                        T->code = merge(3,T->code,genLabel(T->ptr[0]->Snext),T->ptr[1]->code);
                    } else {
                        T->code=merge(2,T->code,T->ptr[1]->code);
                    }
                    if(T->ptr[1]->width > T->width)
                        T->width = T->ptr[1]->width;
                }
                break;
            case _IF:
                strcpy(T->ptr[0]->Etrue,newLabel());
                strcpy(T->ptr[0]->Efalse,T->Snext);
                T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
                boolExp(T->ptr[0]);
                T->width = T->ptr[0]->width;
                strcpy(T->ptr[1]->Snext, T->Snext);
                semanticAnalysis(T->ptr[1]);
                if(T->width < T->ptr[1]->width)
                    T->width = T->ptr[1]->width;
                T->code = merge(3, T->ptr[0]->code, genLabel(T->ptr[0]->Etrue), T->ptr[1]->code);
                break;
            case _IF_ELSE:
                strcpy(T->ptr[0]->Etrue,newLabel());
                strcpy(T->ptr[0]->Efalse,newLabel());
                T->ptr[0]->offset=T->ptr[1]->offset=T->ptr[2]->offset=T->offset;
                boolExp(T->ptr[0]);
                T->width = T->ptr[0]->width;
                strcpy(T->ptr[1]->Snext, T->Snext);
                semanticAnalysis(T->ptr[1]);
                if(T->width < T->ptr[1]->width)
                    T->width = T->ptr[1]->width;
                strcpy(T->ptr[2]->Snext, T->Snext);
                semanticAnalysis(T->ptr[2]);
                if(T->width < T->ptr[1]->width)
                    T->width = T->ptr[1]->width;
                T->code = merge(6,T->ptr[0]->code,genLabel(T->ptr[0]->Etrue),T->ptr[1]->code,
                                genGoto(T->Snext),genLabel(T->ptr[0]->Efalse),T->ptr[2]->code);
                break;
            case _WHILE:
                strcpy(T->ptr[0]->Etrue,newLabel());
                strcpy(T->ptr[0]->Efalse,T->Snext);
                T->ptr[0]->offset = T->ptr[1]->offset = T->offset;
                boolExp(T->ptr[0]);
                T->width = T->ptr[0]->width;
                strcpy(T->ptr[1]->Snext,newLabel());
                semanticAnalysis(T->ptr[1]);
                if(T->width < T->ptr[1]->width)
                    T->width = T->ptr[1]->width;
                T->code = merge(5,genLabel(T->ptr[1]->Snext),T->ptr[0]->code,genLabel(T->ptr[0]->Etrue),T->ptr[1]->code,genGoto(T->ptr[1]->Snext));
                break;
            case _RETURN:
                if(T->ptr[0]) {
                    T->ptr[0]->offset = T->offset;
                    Exp(T->ptr[0]);
                    num = SymT.index;
                    do {
                        num--;
                    }
                    while(SymT.sym[num].flag != 'F');
                    T->width = T->ptr[0]->width;
                    result.kind = ID;
                    strcpy(result.id, SymT.sym[T->ptr[0]->place].alias);
                    result.offset = SymT.sym[T->ptr[0]->place].offset;
                    T->code = merge(2, T->ptr[0]->code, genIR(RETURN,opn1,opn2,result));
                } else {
                    T->width = 0;
                    result.kind =- 0;
                    T->code = genIR(RETURN,opn1,opn2,result);
                }
                break;
            case _BREAK:
            case _CONTINUE:
            case _POSI:
            case _NEGA:
                break;

            case _NOT:
            case _EXP_SEMI:
            case _IDENT_ONLY:
            case _IDENT_ARR:
            case _INT_CONST:
            case _OR:
            case _AND:
            case _RELOP:
            case _PLUS:
            case _MINUS:
            case _MUL:
            case _DIV:
            case _MOD:
            case _LVAL_ASSIGN:
            case _FUNC_CALL:
            case _ARGS:
                Exp(T);
                break;

        }
    }
}

void semanticAnalysisMain()
{
    int rtn;
    FILE *fp = fopen("./cmake-build-debug/test.txt","w");
    if(fp != NULL)
    {
        fclose(fp);
    }
    fp = fopen("./cmake-build-debug/test_ir.txt","w");
    if(fp != NULL)
    {
        fclose(fp);
    }
    SymT.index=0;
    rtn=fillSymbolTable("getint",newAlias(),0,INT,'F',4);
    SymT.sym[rtn].paramnum=0;
    rtn=fillSymbolTable("getch",newAlias(),0,INT,'F',4);
    SymT.sym[rtn].paramnum=0;
    rtn=fillSymbolTable("getarray",newAlias(),0,INT,'F',4);
    SymT.sym[rtn].paramnum=1;
    rtn=fillSymbolTable("a",newAlias(),1,INT,'P',4);
    SymT.sym[rtn].isArray=1;
    rtn=fillSymbolTable("putint",newAlias(),0,VOID,'F',4);
    SymT.sym[rtn].paramnum=1;
    rtn=fillSymbolTable("a",newAlias(),1,INT,'P',4);
    rtn=fillSymbolTable("putch",newAlias(),0,VOID,'F',4);
    SymT.sym[rtn].paramnum=1;
    rtn=fillSymbolTable("a",newAlias(),1,INT,'P',4);
    rtn=fillSymbolTable("putarray",newAlias(),0,VOID,'F',4);
    SymT.sym[rtn].paramnum=2;
    rtn=fillSymbolTable("n",newAlias(),1,INT,'P',4);
    rtn=fillSymbolTable("a",newAlias(),1,INT,'P',4);
    SymT.sym[rtn].isArray=1;
    SymbolScope.TX[0] = 0;
    SymbolScope.top = 1;
    astRoot->offset = 0;
    semanticAnalysis(astRoot);
    // prnVarSymbol();
    changeFunNameTable();
    prnVarSymbol();
}

void printIRMain()
{
    prnIR(astRoot->code);
}
