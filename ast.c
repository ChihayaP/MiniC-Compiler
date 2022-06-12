#include "ast.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <gvc.h>
#include <gvcext.h>

#define MAXLENGTH 1000 

int agnodeNum = 0;
char agnodeChar[100] = "";
struct node *astRoot;           //ast根节点

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
        if(h1 == NULL) {
            t1 = h1->prior;
            t2 = h2->prior;
            t1->next = h2;
            t2->next = h1;
            h1->prior = t2;
            h2->prior = t1;
        }
    }
    va_end(ap);
    return h1;
}

void extVarList(struct node *T) 
{
    int returnNum, num = 1;
    swith(T) {
        case _IDENT_COMMA:
        case _IDENT_VARARR_COMMA:
            T->ptr[0]
    }
}

//语法分析，生成符号表
void semanticAnalysis(struct node *T)
{
    int returnNum, width, num;
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
                T->type = T->ptr[1]->type = T->ptr[0]->type;
                T->ptr[1]->offset = T->offset;
                T->ptr[1]->width = 4;
                
        }
    }
}

void semanticAnalysisMain()
{
    SymbolScope.TX[0] = 0;
    SymbolScope.top = 1;
    astRoot->offset = 0;
    semanticAnalysisMain(astRoot);
}

