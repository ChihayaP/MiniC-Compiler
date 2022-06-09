// #include "sysy.tab.hpp"

typedef enum enum_node_kind {
    _FUNCDEF,_INT,_IDENT,_STMT,_RETURN,
    _LOREXP,
    _LANDEXP,_OR,
    _EQEXP,_AND,
    _RELEXP,_EQ,_NEQ,
    _ADDEXP,_LT,_GT,_LTE,_GTE,
    _MULEXP,_PLUS,_MINUS,
    _UNARYEXP,_MUL,_DIV,_MOD,
    _PRIMARYEXP,_POSI,_NEGA,_NOT,
    _EXP,_NUMBER,
    _INT_CONST
} node_kind;

struct node 
{    //以下对结点属性定义没有考虑存储效率，只是简单地列出要用到的一些属性
	node_kind kind;               //结点类型
    char type_node[32];
	union 
    {
        char type_id[33];             //由标识符生成的叶结点
	    int type_int;                 //由整常数生成的叶结点
	};
    struct node *ptr[3];                   //子树指针，由kind确定有多少棵子树
    int level;                           //层号
    int place;                //表示结点对应的变量或运算结果符号表的位置序号
    char Etrue[15],Efalse[15];      //对布尔表达式的翻译时，真假转移目标的标号
    char Snext[15];               //该结点对饮语句执行后的下一条语句位置标号
    //struct codenode *code;         //该结点中间代码链表头指针
    char op[10];
    int  type;                   //结点对应值的类型
    int pos;                      //语法单位所在位置行号
    int offset;                    //偏移量
    int width;                    //占数据字节数
    int num;                      //变量个数
};
struct node *mknode(node_kind kind,struct node *first,struct node *second, struct node *third,int pos );
int main_tree(struct node *T);