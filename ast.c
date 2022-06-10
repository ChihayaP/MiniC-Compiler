#include "ast.h"
#include <string.h>
#include <stdlib.h>
#include <gvc.h>
#include <gvcext.h>

int agnodeNum = 0;
char agnodeChar[100] = "";

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

Agnode_t *draw_tree_node(struct node *T, Agraph_t *g, Agnode_t *parent_node)
{
    char labelTmp[100] = "";
    char nodeLabel[100] = "";
    int num;
    char tmpChar[100] = {0};
    Agnode_t *child_node;
    switch (T->kind) {
        case _BLOCK:
        case _DECL:
        case _STMT:
        case _EXP:
        case _LOREXP:
        case _LANDEXP:
        case _EQEXP:
        case _RELEXP:
        case _ADDEXP:
        case _MULEXP:            
        case _UNARYEXP:
        case _PRIMARYEXP:
        case _NUMBER:
            child_node = parent_node;          
            break;
        case _FUNCDEF:
        case _INT:
        case _BLOCKITEMNULL:
        case _BLOCKITEM:
        case _VARDECL:
        case _IDENT_ONLY:
        case _IDENT_COMMA:
        case _LVAL:
        case _RETURN:
        case _OR:
        case _AND:
        case _EQ:
        case _NEQ:
        case _LT:
        case _GT:
        case _LTE:
        case _GTE:
        case _PLUS:
        case _MINUS:
        case _MUL:
        case _DIV:
        case _MOD:
        case _POSI:
        case _NEGA:
        case _NOT:
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
            child_node = parent_node;            
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
        /*switch (T->kind) {
            case _FUNCDEF:
                node = draw_tree_node(T, g, NULL);
                draw_tree(T->ptr[0], g, node);
                draw_tree(T->ptr[1], g, node);
                // draw_tree(T->ptr[2], g, node);
                break;
            // case _INT:
            case _IDENT:
            case _INT_CONST:
                node = draw_tree_node(T, g, parent_node);
                break;
            case _STMT:
            case _RETURN:
            case _EXP:
            case _LOREXP:
            case _LANDEXP:
            case _EQEXP:
            case _RELEXP:
            case _ADDEXP:
            case _MULEXP:
            case _UNARYEXP:
            case _PRIMARYEXP:
            case _POSI:
            case _NEGA:
            case _NOT:
            case _NUMBER:

                node = draw_tree_node(T, g, parent_node);
                draw_tree(T->ptr[0], g, node);
                break;
            case _OR:
            case _AND:
            case _EQ:
            case _NEQ:
            case _LT:
            case _GT:
            case _LTE:
            case _GTE:
            case _PLUS:
            case _MINUS:
            case _MUL:
            case _DIV:
            case _MOD:
                node = draw_tree_node(T, g, parent_node);
                draw_tree(T->ptr[0], g, node);
                draw_tree(T->ptr[1], g, node);
                break;
            default:
                break;
        }*/
    }
}

int main_tree(struct node *T)
{
    char funcName[] = "main";
    Agraph_t *g = agopen(funcName, Agdirected, NULL);
    if(NULL == g) {
        printf("agopen() failed\n");
        return -1;
    }
    // agsafeset(g, (char *)"rankdir", (char *)"LR", (char *)"LR");
    agsafeset(g, "dpi", "600", "");
    draw_tree(T, g, NULL);
    GVC_t * gv = gvContext();
    if(gv == NULL) {
        printf("gvContext() failed\n");
        agclose(g);
        return -1;
    }
    gvLayout(gv, g, "dot");
    gvRenderFilename(gv, g, "png", "main.png");
    agclose(g);
    gvFreeContext(gv);
    return 0;
}