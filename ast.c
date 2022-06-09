#include "ast.h"
#include <string.h>
#include <stdlib.h>
#include <gvc.h>
#include <gvcext.h>

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
    Agnode_t *child_node = agnode(g, T->type_node, 1);
    switch (T->kind) {
        case _FUNCDEF:            
        case _BLOCK:           
            break;
        
        case _FUNCTYPE:            
            strcpy(labelTmp, " \\ | int");
            break;
        case _IDENT:            
            strcpy(labelTmp, " \\ | ");
            strcat(labelTmp, T->type_id);
            break;
        case _STMT:            
            strcpy(labelTmp, " \\ | return");
            break;
        case _INT_CONST:
            strcpy(labelTmp, " \\ | ");
            num = T->type_int;
            memset(tmpChar, 0, sizeof(tmpChar));
            itoa(num, tmpChar, 10);
            strcat(labelTmp, tmpChar);
            break;
        default:            
            break;
    }
    strcpy(nodeLabel, T->type_node);
    strcat(nodeLabel, labelTmp);
    if(child_node != NULL) {
        agsafeset(child_node, (char *)"label", (char *)nodeLabel, (char *)nodeLabel);
        agsafeset(child_node, (char *)"shape", (char *)"record", (char *)"ellipse");
    }
    if(parent_node != NULL) {
        // char edge_name[100] = "edge ";

        Agedge_t *e = agedge(g, (Agnode_t *)parent_node, (Agnode_t *)child_node, NULL, 1);
    }
    return child_node;
}

void draw_tree(struct node *T, Agraph_t *g, Agnode_t *parent_node)
{
    Agnode_t *node = NULL;
    if(T != NULL && g != NULL) {
        switch (T->kind) {
            case _FUNCDEF:
                node = draw_tree_node(T, g, NULL);
                draw_tree(T->ptr[0], g, node);
                draw_tree(T->ptr[1], g, node);
                draw_tree(T->ptr[2], g, node);
                break;
            case _FUNCTYPE:
            case _IDENT:
            case _INT_CONST:
                node = draw_tree_node(T, g, parent_node);
                break;
            case _BLOCK:
            case _STMT:
                node = draw_tree_node(T, g, parent_node);
                draw_tree(T->ptr[0], g, node);
                break;
            default:
                break;
        }
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
    agsafeset(g, (char *)"rankdir", (char *)"LR", (char *)"LR");
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