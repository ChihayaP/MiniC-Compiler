%option noyywrap
%option nounput
%option noinput

%{

#include <stdlib.h>
#include <string.h>
// 因为 Flex 会用到 Bison 中关于 token 的定义
// 所以需要 include Bison 生成的头文件
#include "parser.tab.h"
#include "ast.h"


typedef union 
{
	int type_int;
	char type_id[32];
	struct node *ptr;
} YYLVAL;
#define YYSTYPE YYLVAL

%}
%option yylineno

/* 空白符和注释 */
WhiteSpace    [ \t\n\r]*
LineComment   "//".*

/* 标识符 */
Identifier    [a-zA-Z_][a-zA-Z0-9_]*

/* 整数字面量 */
Decimal       [1-9][0-9]*
Octal         0[0-7]*
Hexadecimal   0[xX][0-9a-fA-F]+

%%

{WhiteSpace}    { /* 忽略, 不做任何操作 */ }
{LineComment}   { /* 忽略, 不做任何操作 */ }


{Decimal}       {yylval.type_int = atoi(yytext); return INT_CONST; }
{Octal}         {yylval.type_int = atoi(yytext); return INT_CONST; }
{Hexadecimal}   {yylval.type_int = atoi(yytext); return INT_CONST; }


"int"           { return INT; }
"return"        { return RETURN; }
"void"			{ return VOID; }

{Identifier}    { strcpy(yylval.type_id, yytext); return IDENT;}

"+"	|
"-"	|
"!"	|
"*"	|
"/"	|
"%"	|
"<"	|
">"	|
","	|
";"	|
"{"	|
"}"	|
"("	|
")"				{ return yytext[0]; }

"<="			{ return LTE;}
">="			{ return GTE;}
"=="			{ return EQ;}
"!="			{ return NEQ;}
"&&"			{ return AND;}
"||"			{ return OR;}


.               {return yytext[0];}

%%
