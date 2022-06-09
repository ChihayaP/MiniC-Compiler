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


%token INT RETURN EQ NEQ AND OR GTE LTE
%token <type_id> IDENT
%token <type_int> INT_CONST

// 非终结符的类型定义
%type <ptr> FuncDef FuncType Block Stmt Number VarDec Exp UnaryExp PrimaryExp AddExp MulExp LOrExp LAndExp EqExp RelExp

%%

CompUnit
  : FuncDef {main_tree($1);}
  ;

FuncDef
  : FuncType VarDec '(' ')' Block {$$ = mknode(_FUNCDEF,$1,$2,$5,yylineno);strcpy($$->type_id,"funcDef");}
  ;

FuncType
  : INT {$$=mknode(_INT,NULL,NULL,NULL,yylineno);strcpy($$->type_id,"int");}
  ;

VarDec
  : IDENT {$$ = mknode(_IDENT,NULL,NULL,NULL,yylineno);strcpy($$->type_id,$1);}
  ;

Block
  : '{' Stmt '}' {$$=mknode(_STMT,$2,NULL,NULL,yylineno);strcpy($$->type_id,"stmt");}
  ;

Stmt
  : RETURN Exp ';' {$$=mknode(_RETURN,$2,NULL,NULL,yylineno);strcpy($$->type_id,"return");}
  ;

Exp
  : LOrExp {$$=mknode(_LOREXP,$1,NULL,NULL,yylineno);}
  ;

LOrExp
  : LAndExp           {$$=mknode(_LANDEXP,$1,NULL,NULL,yylineno);}
  | LOrExp OR LAndExp {$$=mknode(_OR,$1,$3,NULL,yylineno);strcpy($$->type_id,"||");}
  ;

LAndExp
  : EqExp             {$$=mknode(_EQEXP,$1,NULL,NULL,yylineno);}
  | LAndExp AND EqExp {$$=mknode(_AND,$1,$3,NULL,yylineno);strcpy($$->type_id,"&&");}
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
  ;

Number
  : INT_CONST {$$=mknode(_INT_CONST,NULL,NULL,NULL,yylineno);$$->type_int=$1,$$->type=INT;}
  ;

%%


void yyerror(const char *msg)
{
    printf("%d:  %s  at  '%s'  \n",yylineno,msg,yytext);
}