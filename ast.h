// #include "sysy.tab.hpp"
//符号表的大小

typedef enum enum_node_kind {
    _EXT_DEF_LIST,_EXT_VAR_DEF,
    _COMP_FUNCDEF,_GLO_DECL,_COMP_FUNCDEF_COMP,_GLO_DECL_COMP,
    _FUNCDEF,_FUNCDEF_PARAMS,_FUNCFPARAM,_FUNCFPARAM_COMMA,
    _PARAM,_PARAM_VARARR,_PARAM_NULL,
    _INT,_VOID,
    _BLOCKITEM,_BLOCKITEMNULL,
    _DECLLIST,_STMTLIST,
    _DECL,_STMT,_DECL_BLOCKITEM,_STMT_BLOCKITEM,
    _VARDECL,
    _IDENT_ONLY_DECL,_IDENT_COMMA,_IDENT_VARARR,_IDENT_VARARR_COMMA,
    _VARARR_ONLY,_VARARR_WITH,
    _BLOCK,_EXP_SEMI,_SEMI,_BREAK,_CONTINUE,_RETURN,_RETURN_SEMI,_LVAL_ASSIGN,_WHILE,_IF_ELSE,_IF,
    _COND,_LOREXP,
    _RELOP,
    _LANDEXP,_OR,
    _EQEXP,_AND,
    _IDENT_ONLY,_IDENT_ARR,
    _ARR_ONLY,_ARR_WITH,
    _RELEXP,_EQ,_NEQ,
    _ADDEXP,_LT,_GT,_LTE,_GTE,
    _MULEXP,_PLUS,_MINUS,
    _UNARYEXP,_MUL,_DIV,_MOD,
    _PRIMARYEXP,_POSI,_NEGA,_NOT,
    _EXP,_NUMBER,_LVAL,
    _INT_CONST,_ARRAY,_IDENT,
    ID,LABEL,GOTO,FUNCTION,PARAM,ASSIGNOP,NOT,LT,LE,GT,GE,EQ,NE,BR,BC,BT,BF,BOOL
} node_kind;

struct opn
{
    int kind;
    int type;
    union 
    {
        int const_int;
        char id[33];
    };
    int level;
    int offset;
    char *rtype;
    
};

//tac代码结点
struct codenode
{
    int op;
    struct opn opn1, opn2, result;
    struct codenode *next, *prior;
};


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
    struct codenode *code;          //该结点中间代码链表头指针
    char op[10];
    int  type;                   //结点对应值的类型
    int pos;                      //语法单位所在位置行号
    int offset;                    //偏移量
    int width;                    //占数据字节数
    int num;                      //变量个数

};

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
    int arrNum;                   //数组维度
    int arr[20];                  //数组下标
    int arrTmp[20];                //数组调用时使用
    char varName[33];
    char paramName[10];
};


struct node *mknode(node_kind kind,struct node *first,struct node *second, struct node *third,int pos );
void storeAstRoot(struct node *T);
void drawAst();