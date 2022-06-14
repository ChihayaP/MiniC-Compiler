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

struct symbol 
{  
    char name[33];     //变量或函数名
    int level;   //层号，外部变量名或函数名层号为0，形参名为1，每到1个复合语句层号加1，退出减1
    int type;           //变量类型或函数返回值类型
    int paramnum;    //形式参数个数 
    int listLength[10];  //数组长度
    char alias[10];      //别名，为解决嵌套层次使用，使得每一个数据名称唯一
    char flag;          //符号标记，函数：'F'  变量：'V'   参数：'P'  临时变量：'T'
    char offset;        //外部变量和局部变量在其静态数据区或活动记录中的偏移量
				    //或函数活动记录大小，目标代码生成时使用
    int isArray;
        //其它...
};



//符号表
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

void prnIR(struct codenode *head){
    char opnstr1[32],opnstr2[32],resultstr[32];
    struct codenode *h=head;
    do {
        if (h->opn1.kind==INT)
             sprintf(opnstr1,"#%d",h->opn1.const_int);
        if (h->opn1.kind==ID)
             sprintf(opnstr1,"%s",h->opn1.id);
        if (h->opn2.kind==INT)
             sprintf(opnstr2,"#%d",h->opn2.const_int);
        if (h->opn2.kind==ID)
             sprintf(opnstr2,"%s",h->opn2.id);
        sprintf(resultstr,"%s",h->result.id);
        char c[10];
        switch (h->op) {
            case ASSIGNOP:  
                                printf("  %s := %s\n",resultstr,opnstr1);
                            break;
            case _PLUS:
            case _MINUS:
            case _MUL:
            case _DIV: 
                      printf("  %s := %s %c %s\n",resultstr,opnstr1, \
                      h->op==_PLUS?'+':h->op==_MINUS?'-':h->op==_MUL?'*':'\\',opnstr2);
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
                      printf("  %s := %s %s %s\n",resultstr,opnstr1,c,opnstr2);
                      break;
            case FUNCTION: printf("\nFUNCTION %s :\n",h->result.id);
                           break;
            case PARAM:    printf("  PARAM %s\n",h->result.id);
                           break;
            case LABEL:    printf("LABEL %s :\n",h->result.id);
                           break;
            case GOTO:     printf("  GOTO %s\n",h->result.id);
                           break;
            case JLE:      printf("  IF %s <= %s GOTO %s\n",opnstr1,opnstr2,resultstr);
                           break;
            case JLT:      printf("  IF %s < %s GOTO %s\n",opnstr1,opnstr2,resultstr);
                           break;
            case JGE:      printf("  IF %s >= %s GOTO %s\n",opnstr1,opnstr2,resultstr);
                           break;
            case JGT:      printf("  IF %s > %s GOTO %s\n",opnstr1,opnstr2,resultstr);
                           break;
            case EQ:       printf("  IF %s == %s GOTO %s\n",opnstr1,opnstr2,resultstr);
                           break;
            case NEQ:      printf("  IF %s != %s GOTO %s\n",opnstr1,opnstr2,resultstr);
                           break;
            case RETURN:   if (h->result.kind)
                                printf("  RETURN %s\n",resultstr);
                           else
                                printf("  RETURN\n");
                           break;
        }
    h=h->next;
    } while (h!=head);
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
    return strcat0("label",s);
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
    printf("在%d行,%s %s\n",line,msg1,msg2);
}

//显示符号表
void prnSymbol()
{
    int i=0;
    printf("%6s %6s %6s  %6s %4s %6s\n","name","alias","LEV","type","flag","offset");
    char ptype[10];
    for(i=0;i<SymT.index;i++)
    {
        if (SymT.sym[i].type==INT)   
        {
            strcpy(ptype,"int");
        }
        printf("%6s %6s %6d  %6s %4c %6d\n",SymT.sym[i].name,
                SymT.sym[i].alias,SymT.sym[i].level,
                ptype,
                SymT.sym[i].flag,SymT.sym[i].offset);
        strcpy(ptype,"");
    }  
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

void extVarList(struct node *T) 
{
    int rtn, num = 1;
    switch(T->kind) {
        case _IDENT_ONLY_DECL:
            rtn = fillSymbolTable(T->type_id,newAlias(),LEV,T->type,'V',T->offset);
            if(rtn == -1) {
                semanticError(T->pos, T->type_id, "变量重复定义\n");
            } else {
                T->place = rtn;
            }
            T->num = 1;
            break;
        case _IDENT_COMMA:
            rtn = fillSymbolTable(T->type_id,newAlias(),LEV,T->type,'V',T->offset);
            if(rtn == -1) {
                semanticError(T->pos, T->type_id, "变量重复定义\n");
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
                semanticError(T->pos, T->type_id, "变量重复定义\n");
            } else {
                T->place = rtn;
            }
            T->ptr[0]->type = T->type;
            T->ptr[0]->offset = T->offset + T->width;
            T->ptr[0]->width = T->width;
            extVarList(T->ptr[0]);
            T->num = T->ptr[0]->num + 1;
            break;
        case _IDENT_VARARR:
            rtn = fillSymbolTable(T->type_id,newAlias(),LEV,T->type,'V',T->offset*(T->ptr[0]->type_int));
            if(rtn == -1) {
                semanticError(T->pos, T->type_id, "变量重复定义\n");
            } else {
                T->place = rtn;
            }
            T->num = 1;
            break;
    }
}

void Exp(struct node *T)
{
    int rtn, num, width;
    struct node *T0;
    struct opn opn1, opn2, result;
    if (T) {
        switch (T->kind) {
            case _INT_CONST:
                T->place = fillTemp(newTemp(),LEV,T->type,'T',T->offset);
                T->type = INT;
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
                    semanticError(T->pos,T->type_id,"变量未定义");
                }
                if(SymT.sym[rtn].isArray == 1) {
                    semanticError(T->pos,T->type_id, "不能对数组名赋值");
                }
                if(SymT.sym[rtn].flag == 'F') {
                    semanticError(T->pos,T->type_id, "是函数名，类型不匹配");
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
                result.kind=ID; 
                strcpy(result.id,T->Etrue);
                if(strcmp(T->type_id, "<") == 0) {
                    op = JLT;
                } else if (strcmp(T->type_id, "<=") == 0) {
                    op = JLE;
                } else if (strcmp(T->type_id, ">") == 0) {
                    op = JGT;
                } else if (strcmp(T->type_id, ">=") == 0) {
                    op = JGE;
                } else if (strcmp(T->type_id, "==") == 0) {
                    op = EQ;
                } else if (strcmp(T->type_id, "!=") == 0) {
                    op = NEQ;
                }
                T->code = genIR(op,opn1,opn2,result);
                T->code = merge(4,T->ptr[0]->code,T->ptr[1]->code,T->code,genGoto(T->Efalse));
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
                    semanticError(T->pos,T->type_id, "变量未定义");
                if (SymT.sym[rtn].flag=='F')
                    semanticError(T->pos,T->type_id, "是函数名，类型不匹配");
                else {
                    opn1.kind=ID; 
                    strcpy(opn1.id,SymT.sym[rtn].alias);
                    opn1.offset=SymT.sym[rtn].offset;
                    opn2.kind=INT; 
                    opn2.const_int=0;
                    result.kind=ID; 
                    strcpy(result.id,T->Etrue);
                    T->code=genIR(NEQ,opn1,opn2,result);
                    T->code=merge(2,T->code,genGoto(T->Efalse));
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
    int rtn, width, num;
    struct node *T0;
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
                    semanticError(T->pos,T->type_id,"函数重复定义");
                    break;
                } else
                    T->place = rtn;
                result.kind = ID;
                strcpy(result.id,T->type_id);
                result.offset = rtn;
                T->code = genIR(FUNCTION,opn1,opn2,result);
                SymT.sym[rtn].paramnum = 0;
                T->ptr[0]->offset = T->offset;
                strcpy(T->ptr[0]->Snext, newLabel());
                semanticAnalysis(T->ptr[0]);
                SymT.sym[T->place].offset = T->offset + T->ptr[0]->width;
                T->code = merge(3,T->code,T->ptr[0]->code,genLabel(T->ptr[0]->Snext));
                break;
            case _FUNCDEF_PARAMS:
                T->width = 0;
                T->offset = DX;
                rtn = fillSymbolTable(T->type_id,newAlias(),LEV,T->type,'F',0);
                if(rtn == -1) {
                    semanticError(T->pos,T->type_id,"函数重复定义");
                    break;
                } else
                    T->place = rtn;
                result.kind = ID;
                strcpy(result.id,T->type_id);
                result.offset = rtn;
                T->code = genIR(FUNCTION,opn1,opn2,result);
                T->ptr[0]->offset = T->offset;
                semanticAnalysis(T->ptr[0]);
                T->offset += T->ptr[0]->width;
                T->ptr[1]->offset = T->offset;
                strcpy(T->ptr[1]->Snext, newLabel());
                semanticAnalysis(T->ptr[1]);
                if(T->ptr[1]->ptr[0] != NULL) {
                    SymT.sym[T->place].offset = T->offset + T->ptr[1]->width;
                    T->code = merge(3,T->code,T->ptr[1]->code,genLabel(T->ptr[1]->Snext));
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
                    semanticError(T->pos,T->type_id,"参数名重复定义");
                } else
                T->place = rtn;
                T->num = 1;
                T->width = 4;
                result.kind = ID;
                strcpy(result.id, SymT.sym[rtn].alias);
                result.offset = T->offset;
                T->code=genIR(PARAM,opn1,opn2,result);
                break;
            case _BLOCKITEM:
            case _BLOCKITEMNULL:
                if(T->ptr[0] == NULL) {
                    T->width = 0;
                    T->code = NULL;
                } else {
                    LEV++;
                    SymbolScope.TX[SymbolScope.top++] = SymT.index;
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
                    prnSymbol();
                    LEV--;
                    SymT.index = SymbolScope.TX[--SymbolScope.top];
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
            case _NOT:
                break;

            case _EXP_SEMI:
            case _IDENT_ONLY:
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
                Exp(T);
                break;

        }
    }
}

void semanticAnalysisMain()
{
    SymbolScope.TX[0] = 0;
    SymbolScope.top = 1;
    astRoot->offset = 0;
    semanticAnalysis(astRoot);
}

void printIRMain()
{
    prnIR(astRoot->code);
}
