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


%token INT VOID RETURN EQ NEQ AND OR GTE LTE IF ELSE WHILE BREAK CONTINUE
%token <type_id> IDENT
%token <type_int> INT_CONST

// 非终结符的类型定义
%type <ptr> CompUnit FuncDef FuncType Block Stmt Number Exp UnaryExp PrimaryExp AddExp MulExp LOrExp LAndExp EqExp RelExp Decl BlockItem LVal VarDecl BType Cond VarArray Array FuncFParams FuncFParam

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
  : FuncType IDENT '(' ')' Block {$$=mknode(_FUNCDEF,$1,$5,NULL,yylineno);strcpy($$->type_id,$2);}
  | FuncType IDENT '(' FuncFParams ')' Block {$$=mknode(_FUNCDEF,$1,$4,$6,yylineno);strcpy($$->type_id,$2);}
  ;

FuncFParams
  : FuncFParam                  {$$=mknode(_FUNCFPARAM,$1,NULL,NULL,yylineno);}
  | FuncFParam ',' FuncFParams  {$$=mknode(_FUNCFPARAM_COMMA,$1,NULL,NULL,yylineno);strcpy($$->type_id,",");}
  ;

FuncFParam
  : BType IDENT                   {$$=mknode(_PARAM,$1,NULL,NULL,yylineno);strcpy($$->type_id,$2);}
  | BType IDENT VarArray          {$$=mknode(_PARAM_VARARR,$1,$3,NULL,yylineno);strcpy($$->type_id,$2);}
  | BType IDENT '[' ']' VarArray  {$$=mknode(_PARAM_NULL,$1,$5,NULL,yylineno);strcpy($$->type_id,$2);}
  ;

FuncType
  : INT   {$$=mknode(_INT,NULL,NULL,NULL,yylineno);strcpy($$->type_id,"int");}
  | VOID  {$$=mknode(_VOID,NULL,NULL,NULL,yylineno);strcpy($$->type_id,"void");}
  ;

Block
  : '{' BlockItem '}' {$$=mknode(_BLOCKITEM,$2,NULL,NULL,yylineno);}
  | '{' '}'           {$$=mknode(_BLOCKITEMNULL,NULL,NULL,NULL,yylineno);strcpy($$->type_id,"\\{\\}");}
  ;

BlockItem
  : Decl              {$$=mknode(_DECL,$1,NULL,NULL,yylineno);} 
  | Stmt              {$$=mknode(_STMT,$1,NULL,NULL,yylineno);}
  | Decl BlockItem    {$$=mknode(_DECL_BLOCKITEM,$1,$2,NULL,yylineno);strcpy($$->type_id,"blockItem");}
  | Stmt BlockItem    {$$=mknode(_STMT_BLOCKITEM,$1,$2,NULL,yylineno);strcpy($$->type_id,"blockItem");}
  ;

Decl
  : BType VarDecl ';' {$$=mknode(_VARDECL,$1,$2,NULL,yylineno);strcpy($$->type_id,"varDecl");}
  ;

VarDecl
  : IDENT             {$$=mknode(_IDENT_ONLY_DECL,NULL,NULL,NULL,yylineno);strcpy($$->type_id,$1);}
  | IDENT ',' VarDecl {$$=mknode(_IDENT_COMMA,$3,NULL,NULL,yylineno);strcpy($$->type_id,strcat($1,","));}
  | IDENT VarArray    {$$=mknode(_IDENT_VARARR,$2,NULL,NULL,yylineno);strcpy($$->type_id,$1);}
  | IDENT VarArray ',' VarDecl {$$=mknode(_IDENT_VARARR_COMMA,$2,$4,NULL,yylineno);strcpy($$->type_id,strcat($1,","));}
  ;

VarArray
  : '[' INT_CONST ']'           {$$=mknode(_VARARR_ONLY,NULL,NULL,NULL,yylineno);$$->type_int,$2;}
  | '[' INT_CONST ']' VarArray  {$$=mknode(_VARARR_WITH,$4,NULL,NULL,yylineno);$$->type_int,$2;}
  ;

BType
  : INT {$$=mknode(_INT,NULL,NULL,NULL,yylineno);strcpy($$->type_id,"int");}
  ;

Stmt
  : Block             {$$=mknode(_BLOCK,$1,NULL,NULL,yylineno);}
  | Exp ';'           {$$=mknode(_EXP_SEMI,$1,NULL,NULL,yylineno);}
  | ';'               {$$=mknode(_SEMI,NULL,NULL,NULL,yylineno);}
  | BREAK ';'         {$$=mknode(_BREAK,NULL,NULL,NULL,yylineno);strcpy($$->type_id,"break");}
  | CONTINUE ';'      {$$=mknode(_CONTINUE,NULL,NULL,NULL,yylineno);strcpy($$->type_id,"continue");}
  | RETURN Exp ';'    {$$=mknode(_RETURN,$2,NULL,NULL,yylineno);strcpy($$->type_id,"return");}
  | RETURN ';'        {$$=mknode(_RETURN_SEMI,NULL,NULL,NULL,yylineno);strcpy($$->type_id,"return;");}
  | LVal '=' Exp ';'  {$$=mknode(_LVAL_ASSIGN,$1,$3,NULL,yylineno);strcpy($$->type_id,"=");}
  | WHILE '(' Cond ')' Stmt            {$$=mknode(_WHILE,$3,$5,NULL,yylineno);strcpy($$->type_id,"while");}
  | IF '(' Cond ')' Stmt ELSE Stmt     {$$=mknode(_IF_ELSE,$3,$5,$7,yylineno);strcpy($$->type_id,"if");}
  | IF '(' Cond ')' Stmt %prec LT_ELSE {$$=mknode(_IF,$3,$5,NULL,yylineno);strcpy($$->type_id,"if");}
  ;

Cond
  : LOrExp  {$$=mknode(_COND,$1,NULL,NULL,yylineno);}
  ;

Exp
  : LOrExp  {$$=mknode(_LOREXP,$1,NULL,NULL,yylineno);}
  ;

LOrExp
  : LAndExp           {$$=mknode(_LANDEXP,$1,NULL,NULL,yylineno);}
  | LOrExp OR LAndExp {$$=mknode(_OR,$1,$3,NULL,yylineno);strcpy($$->type_id,"||");}
  ;

LAndExp
  : EqExp             {$$=mknode(_EQEXP,$1,NULL,NULL,yylineno);}
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
  : RelExp            {$$=mknode(_RELEXP,$1,NULL,NULL,yylineno);}
  | EqExp EQ RelExp   {$$=mknode(_EQ,$1,$3,NULL,yylineno);strcpy($$->type_id,"==");}
  | EqExp NEQ RelExp  {$$=mknode(_NEQ,$1,$3,NULL,yylineno);strcpy($$->type_id,"!=");}
  ;

RelExp
  : AddExp            {$$=mknode(_ADDEXP,$1,NULL,NULL,yylineno);}
  | RelExp '<' AddExp {$$=mknode(_LT,$1,$3,NULL,yylineno);strcpy($$->type_id,"\\<");}
  | RelExp '>' AddExp {$$=mknode(_GT,$1,$3,NULL,yylineno);strcpy($$->type_id,"\\>");}
  | RelExp LTE AddExp {$$=mknode(_LTE,$1,$3,NULL,yylineno);strcpy($$->type_id,"\\<=");}
  | RelExp GTE AddExp {$$=mknode(_GTE,$1,$3,NULL,yylineno);strcpy($$->type_id,"\\>=");}
  ;

AddExp
  : MulExp            {$$=mknode(_MULEXP,$1,NULL,NULL,yylineno);}
  | AddExp '+' MulExp {$$=mknode(_PLUS,$1,$3,NULL,yylineno);strcpy($$->type_id,"+");}
  | AddExp '-' MulExp {$$=mknode(_MINUS,$1,$3,NULL,yylineno);strcpy($$->type_id,"-");}
  ;

MulExp
  : UnaryExp            {$$=mknode(_UNARYEXP,$1,NULL,NULL,yylineno);}
  | MulExp '*' UnaryExp {$$=mknode(_MUL,$1,$3,NULL,yylineno);strcpy($$->type_id,"*");}
  | MulExp '/' UnaryExp {$$=mknode(_DIV,$1,$3,NULL,yylineno);strcpy($$->type_id,"/");}
  | MulExp '%' UnaryExp {$$=mknode(_MOD,$1,$3,NULL,yylineno);strcpy($$->type_id,"%");}
  ;

UnaryExp
  : PrimaryExp    {$$=mknode(_PRIMARYEXP,$1,NULL,NULL,yylineno);}
  | '+' UnaryExp  {$$=mknode(_POSI,$2,NULL,NULL,yylineno);strcpy($$->type_id,"+");}
  | '-' UnaryExp  {$$=mknode(_NEGA,$2,NULL,NULL,yylineno);strcpy($$->type_id,"-");}
  | '!' UnaryExp  {$$=mknode(_NOT,$2,NULL,NULL,yylineno);strcpy($$->type_id,"!");}
  ;

PrimaryExp
  : '(' Exp ')' {$$=mknode(_EXP,$2,NULL,NULL,yylineno);}
  | Number      {$$=mknode(_NUMBER,$1,NULL,NULL,yylineno);}
  | LVal        {$$=mknode(_LVAL,$1,NULL,NULL,yylineno);}
  ;

Number
  : INT_CONST {$$=mknode(_INT_CONST,NULL,NULL,NULL,yylineno);$$->type_int=$1;}
  ;

%%


void yyerror(const char *msg)
{
    printf("%d:  %s  at  '%s'  \n",yylineno,msg,yytext);
}