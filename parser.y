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


%token INT RETURN
%token <type_id> IDENT
%token <type_int> INT_CONST

// 非终结符的类型定义
%type <ptr> FuncDef FuncType Block Stmt Number VarDec Exp UnaryExp PrimaryExp AddExp MulExp

%%

CompUnit
  : FuncDef {main_tree($1);}
  ;

FuncDef
  : FuncType VarDec '(' ')' Block {$$ = mknode(_FUNCDEF,$1,$2,$5,yylineno);strcpy($$->type_node,"funcDef");strcpy($$->type_id,"funcDef");}
  ;

FuncType
  : INT {$$=mknode(_INT,NULL,NULL,NULL,yylineno);strcpy($$->type_node,"funcType_int");strcpy($$->type_id,"int");}
  ;

VarDec
  : IDENT {$$ = mknode(_IDENT,NULL,NULL,NULL,yylineno);strcpy($$->type_node,"ident");strcpy($$->type_id,$1);}
  ;

Block
  : '{' Stmt '}' {$$=mknode(_STMT,$2,NULL,NULL,yylineno);strcpy($$->type_node,"stmt");strcpy($$->type_id,"stmt");}
  ;

Stmt
  : RETURN Exp ';' {$$=mknode(_RETURN,$2,NULL,NULL,yylineno);strcpy($$->type_node,"return");strcpy($$->type_id,"return");}
  ;

Exp
  : AddExp {$$=mknode(_ADDEXP,$1,NULL,NULL,yylineno);strcpy($$->type_node,"addExp");}
  ;

AddExp
  : MulExp            {$$=mknode(_MULEXP,$1,NULL,NULL,yylineno);strcpy($$->type_node,"mulExp");}
  | AddExp '+' MulExp {$$=mknode(_PLUS,$1,$3,NULL,yylineno);strcpy($$->type_node,"plus");strcpy($$->type_id,"+");}
  | AddExp '-' MulExp {$$=mknode(_MINUS,$1,$3,NULL,yylineno);strcpy($$->type_node,"minus");strcpy($$->type_id,"-");}
  ;

MulExp
  : UnaryExp            {$$=mknode(_UNARYEXP,$1,NULL,NULL,yylineno);strcpy($$->type_node,"unaryExp");}
  | MulExp '*' UnaryExp {$$=mknode(_MUL,$1,$3,NULL,yylineno);strcpy($$->type_node,"mul");strcpy($$->type_id,"*");}
  | MulExp '/' UnaryExp {$$=mknode(_DIV,$1,$3,NULL,yylineno);strcpy($$->type_node,"div");strcpy($$->type_id,"/");}
  | MulExp '%' UnaryExp {$$=mknode(_MOD,$1,$3,NULL,yylineno);strcpy($$->type_node,"mod");strcpy($$->type_id,"%");}
  ;

UnaryExp
  : PrimaryExp    {$$=mknode(_PRIMARYEXP,$1,NULL,NULL,yylineno);strcpy($$->type_node,"primaryExp");}
  | '+' UnaryExp  {$$=mknode(_POSI,$2,NULL,NULL,yylineno);strcpy($$->type_node,"posi");strcpy($$->type_id,"+");}
  | '-' UnaryExp  {$$=mknode(_NEGA,$2,NULL,NULL,yylineno);strcpy($$->type_node,"nega");strcpy($$->type_id,"-");}
  | '!' UnaryExp  {$$=mknode(_NOT,$2,NULL,NULL,yylineno);strcpy($$->type_node,"not");strcpy($$->type_id,"!");}
  ;

PrimaryExp
  : '(' Exp ')' {$$=mknode(_EXP,$2,NULL,NULL,yylineno);strcpy($$->type_node,"exp");}
  | Number      {$$=mknode(_NUMBER,$1,NULL,NULL,yylineno);strcpy($$->type_node,"number");}
  ;

Number
  : INT_CONST {$$=mknode(_INT_CONST,NULL,NULL,NULL,yylineno);strcpy($$->type_node,"int_const");$$->type_int=$1,$$->type=INT;}
  ;

%%


void yyerror(const char *msg)
{
    printf("%d:  %s  at  '%s'  \n",yylineno,msg,yytext);
}