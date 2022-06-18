%code requires {
  #include <string.h>
}

%{


#include <string.h>
#include "../ast.h"
#include <stdio.h>
#include <stdlib.h>
extern int yylineno;
extern char *yytext;

void yyerror(const char *msg);
int yylex();

%}


%union {
	int    type_int;
	char   type_id[32];
	struct node *ptr;
};


%token INT VOID RETURN AND OR IF ELSE WHILE BREAK CONTINUE
%token <type_id> IDENT RELOP
%token <type_int> INT_CONST

// 非终结符的类型定义
%type <ptr> CompUnit FuncDef Block Stmt Number Exp UnaryExp PrimaryExp AddExp MulExp LOrExp LAndExp EqExp Decl LVal VarDecl BType Cond VarArray Array FuncFParams FuncFParam DeclList StmtList Args BlockItemList BlockItem

%left '-' '+'
%left '*' '/' '%'
%right '!'
%nonassoc LT_ELSE
%nonassoc ELSE

%%

program
  : CompUnit  {storeAstRoot($1);}
  ;

CompUnit
  : FuncDef           {$$=mknode(_COMP_FUNCDEF,$1,NULL,NULL,yylineno);}
  | Decl              {$$=mknode(_GLO_DECL,$1,NULL,NULL,yylineno);}
  | FuncDef CompUnit  {$$=mknode(_COMP_FUNCDEF_COMP,$1,$2,NULL,yylineno);strcpy($$->type_id,"compUnit");}
  | Decl CompUnit     {$$=mknode(_GLO_DECL_COMP,$1,$2,NULL,yylineno);strcpy($$->type_id,"compUnit");}
  ;

FuncDef
  : INT IDENT '(' ')' Block               {$$=mknode(_FUNCDEF,$5,NULL,NULL,yylineno);strcpy($$->type_id,$2);$$->type=INT;}
  | INT IDENT '(' FuncFParams ')' Block   {$$=mknode(_FUNCDEF_PARAMS,$4,$6,NULL,yylineno);strcpy($$->type_id,$2);$$->type=INT;}
  | VOID IDENT '(' ')' Block              {$$=mknode(_FUNCDEF,$5,NULL,NULL,yylineno);strcpy($$->type_id,$2);$$->type=VOID;}
  | VOID IDENT '(' FuncFParams ')' Block  {$$=mknode(_FUNCDEF_PARAMS,$4,$6,NULL,yylineno);strcpy($$->type_id,$2);$$->type=VOID;}
  ;

FuncFParams
  : FuncFParam                  {$$=mknode(_FUNCFPARAM,$1,NULL,NULL,yylineno);}
  | FuncFParam ',' FuncFParams  {$$=mknode(_FUNCFPARAM_COMMA,$1,$3,NULL,yylineno);strcpy($$->type_id,",");}
  ;

FuncFParam
  : BType IDENT                   {$$=mknode(_PARAM,$1,NULL,NULL,yylineno);strcpy($$->type_id,$2);}
  | BType IDENT VarArray          {$$=mknode(_PARAM_VARARR,$1,$3,NULL,yylineno);strcpy($$->type_id,$2);}
  | BType IDENT '[' ']'           {$$=mknode(_PARAM_NULL,$1,NULL,NULL,yylineno);strcpy($$->type_id,$2);}
  | BType IDENT '[' ']' VarArray  {$$=mknode(_PARAM_NULL,$1,$5,NULL,yylineno);strcpy($$->type_id,$2);}
  ;

/* FuncType
  : INT   {$$=mknode(_INT,NULL,NULL,NULL,yylineno);strcpy($$->type_id,"int");$$->type=INT;}
  | VOID  {$$=mknode(_VOID,NULL,NULL,NULL,yylineno);strcpy($$->type_id,"void");$$->type=INT;}
  ; */

Decl
  : INT VarDecl ';' {$$=mknode(_VARDECL,$2,NULL,NULL,yylineno);$$->type=INT;strcpy($$->type_id,"int");}
  ;

VarDecl
  : IDENT             {$$=mknode(_IDENT_ONLY_DECL,NULL,NULL,NULL,yylineno);strcpy($$->type_id,$1);}
  | IDENT ',' VarDecl {$$=mknode(_IDENT_COMMA,$3,NULL,NULL,yylineno);strcpy($$->type_id,$1);}
  | IDENT VarArray    {$$=mknode(_IDENT_VARARR,$2,NULL,NULL,yylineno);strcpy($$->type_id,$1);}
  | IDENT VarArray ',' VarDecl {$$=mknode(_IDENT_VARARR_COMMA,$2,$4,NULL,yylineno);strcpy($$->type_id,strcat($1,","));}
  ;

VarArray
  : '[' INT_CONST ']'           {$$=mknode(_VARARR_ONLY,NULL,NULL,NULL,yylineno);$$->type_int=$2;}
  | '[' INT_CONST ']' VarArray  {$$=mknode(_VARARR_WITH,$4,NULL,NULL,yylineno);$$->type_int=$2;}
  ;

Block
  : '{' BlockItemList '}' {$$=mknode(_BLOCKITEM,$2,NULL,NULL,yylineno);}
  | '{' '}'               {$$=mknode(_BLOCKITEMNULL,NULL,NULL,NULL,yylineno);strcpy($$->type_id,"\\{\\}");}
  ;

BlockItemList
  : {$$=NULL;}
  | BlockItem BlockItemList {$$=mknode(_BLOCKITEMLIST,$1,$2,NULL,yylineno);}
  ;

BlockItem
  : DeclList StmtList {$$=mknode(_BLOCKITEM_,$1,$2,NULL,yylineno);}
  ;

DeclList
  : {$$=NULL;}
  | Decl DeclList {$$=mknode(_DECLLIST,$1,$2,NULL,yylineno);strcpy($$->type_id,"DeclList");}
  ;

StmtList
  : {$$=NULL;}
  | Stmt StmtList {$$=mknode(_STMTLIST,$1,$2,NULL,yylineno);strcpy($$->type_id,"StmtList");}
  ;

BType
  : INT {$$=mknode(_INT,NULL,NULL,NULL,yylineno);strcpy($$->type_id,"int");$$->type=INT;}
  ;

Stmt
  : Block             {$$=$1;}
  | Exp ';'           {$$=mknode(_EXP_SEMI,$1,NULL,NULL,yylineno);}
  | ';'               {$$=NULL;}
  | BREAK ';'         {$$=mknode(_BREAK,NULL,NULL,NULL,yylineno);strcpy($$->type_id,"break");}
  | CONTINUE ';'      {$$=mknode(_CONTINUE,NULL,NULL,NULL,yylineno);strcpy($$->type_id,"continue");}
  | RETURN Exp ';'    {$$=mknode(_RETURN,$2,NULL,NULL,yylineno);strcpy($$->type_id,"return");}
  | RETURN ';'        {$$=mknode(_RETURN,NULL,NULL,NULL,yylineno);strcpy($$->type_id,"return;");}
  | LVal '=' Exp ';'  {$$=mknode(_LVAL_ASSIGN,$1,$3,NULL,yylineno);strcpy($$->type_id,"=");}
  | WHILE '(' Cond ')' Stmt            {$$=mknode(_WHILE,$3,$5,NULL,yylineno);strcpy($$->type_id,"while");}
  | IF '(' Cond ')' Stmt ELSE Stmt     {$$=mknode(_IF_ELSE,$3,$5,$7,yylineno);strcpy($$->type_id,"if");}
  | IF '(' Cond ')' Stmt %prec LT_ELSE {$$=mknode(_IF,$3,$5,NULL,yylineno);strcpy($$->type_id,"if");}
  ;

Cond
  : LOrExp  {$$=$1;}
  ;

Exp
  : AddExp  {$$=$1;}
  ;

LOrExp
  : LAndExp           {$$=$1;}
  | LOrExp OR LAndExp {$$=mknode(_OR,$1,$3,NULL,yylineno);strcpy($$->type_id,"\\|\\|");}
  ;

LAndExp
  : EqExp             {$$=$1;}
  | LAndExp AND EqExp {$$=mknode(_AND,$1,$3,NULL,yylineno);strcpy($$->type_id,"&&");}
  ;

LVal
  : IDENT             {$$=mknode(_IDENT_ONLY,NULL,NULL,NULL,yylineno);strcpy($$->type_id,$1);}
  | IDENT Array       {$$=mknode(_IDENT_ARR,$2,NULL,NULL,yylineno);strcpy($$->type_id,$1);}
  ;

Array
  : '[' Exp ']'       {$$=mknode(_ARR_ONLY,$2,NULL,NULL,yylineno);strcpy($$->type_id,"[]");}
  | '[' Exp ']' Array {$$=mknode(_ARR_WITH,$2,$4,NULL,yylineno);strcpy($$->type_id,"[]");}
  ;

EqExp
  : AddExp              {$$=$1;}
  | AddExp RELOP AddExp {$$=mknode(_RELOP,$1,$3,NULL,yylineno);strcpy($$->type_id,$2);}
  ;

AddExp
  : MulExp            {$$=$1;}
  | AddExp '+' MulExp {$$=mknode(_PLUS,$1,$3,NULL,yylineno);strcpy($$->type_id,"+");}
  | AddExp '-' MulExp {$$=mknode(_MINUS,$1,$3,NULL,yylineno);strcpy($$->type_id,"-");}
  ;

MulExp
  : UnaryExp            {$$=$1;}
  | MulExp '*' UnaryExp {$$=mknode(_MUL,$1,$3,NULL,yylineno);strcpy($$->type_id,"*");}
  | MulExp '/' UnaryExp {$$=mknode(_DIV,$1,$3,NULL,yylineno);strcpy($$->type_id,"/");}
  | MulExp '%' UnaryExp {$$=mknode(_MOD,$1,$3,NULL,yylineno);strcpy($$->type_id,"%");}
  ;

UnaryExp
  : PrimaryExp    {$$=$1;}
  | '+' UnaryExp  {$$=mknode(_POSI,$2,NULL,NULL,yylineno);strcpy($$->type_id,"+");}
  | '-' UnaryExp  {$$=mknode(_NEGA,$2,NULL,NULL,yylineno);strcpy($$->type_id,"-");}
  | '!' UnaryExp  {$$=mknode(_NOT,$2,NULL,NULL,yylineno);strcpy($$->type_id,"!");}
  ;

PrimaryExp
  : '(' Exp ')' {$$=$2;}
  | Number      {$$=$1;}
  | LVal        {$$=$1;} 
  | IDENT '(' ')'       {$$=mknode(_FUNC_CALL,NULL,NULL,NULL,yylineno);strcpy($$->type_id,$1);}
  | IDENT '(' Args ')'  {$$=mknode(_FUNC_CALL,$3,NULL,NULL,yylineno);strcpy($$->type_id,$1);}  
  ;

Args
  : Exp ',' Args  {$$=mknode(_ARGS,$1,$3,NULL,yylineno);strcpy($$->type_id,"args");}
  | Exp           {$$=mknode(_ARGS,$1,NULL,NULL,yylineno);strcpy($$->type_id,"args");}
  ;

Number
  : INT_CONST {$$=mknode(_INT_CONST,NULL,NULL,NULL,yylineno);$$->type_int=$1;}
  ;

%%


void yyerror(const char *msg)
{
    printf("%d:  %s  at  '%s'  \n",yylineno,msg,yytext);
}