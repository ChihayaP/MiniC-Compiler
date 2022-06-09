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
%type <ptr> FuncDef FuncType Block Stmt Number VarDec

%%

CompUnit
  : FuncDef {
    main_tree($1);
    printf("at compunit\n");
  }
  ;


FuncDef
  : FuncType VarDec '(' ')' Block {
    $$ = mknode(_FUNCDEF,$1,$2,$5,yylineno);
    strcpy($$->type_node,"funcdef");
    printf("at funcdef\n");
  }
  ;

FuncType
  : INT {
    $$ = mknode(_FUNCTYPE,NULL,NULL,NULL,yylineno);
    strcpy($$->type_node,"functype");
    printf("at functype\n");
  }
  ;

VarDec
  : IDENT {
    $$ = mknode(_IDENT,NULL,NULL,NULL,yylineno);
    strcpy($$->type_id,$1);
    strcpy($$->type_node,"ident");
    printf("at vardec\n");
  }
  ;

Block
  : '{' Stmt '}' {
    $$ = mknode(_BLOCK,$2,NULL,NULL,yylineno);
    strcpy($$->type_node,"block");
    printf("at block\n");
  }
  ;

Stmt
  : RETURN Number ';' {
    $$ = mknode(_STMT,$2,NULL,NULL,yylineno);
    strcpy($$->type_node,"stmt");
    printf("at stmt\n");
  }
  ;

Number
  : INT_CONST {
    $$ = mknode(_INT_CONST,NULL,NULL,NULL,yylineno);
    $$->type_int = $1, $$->type=INT;
    strcpy($$->type_node,"int_const");
    printf("at number\n");
  }
  ;

%%


void yyerror(const char *msg)
{
    printf("%d:  %s  at  '%s'  \n",yylineno,msg,yytext);
}