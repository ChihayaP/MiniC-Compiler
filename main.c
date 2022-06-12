#include <stdlib.h>
#include <stdio.h>
#include "ast.h"
#include "cmake-build-debug/parser.tab.h"

// 声明 lexer 的输入, 以及 parser 函数
// 为什么不引用 sysy.tab.hpp 呢? 因为首先里面没有 yyin 的定义
// 其次, 因为这个文件不是我们自己写的, 而是被 Bison 生成出来的
// 你的代码编辑器/IDE 很可能找不到这个文件, 然后会6给你报错 (虽然编译不会出错)
// 看起来会很烦人, 于是干脆采用这种看起来 dirty 但实际很有效的手段
extern FILE *yyin;
extern int yyparse();

int main(int argc, const char *argv[]) {
  // 解析命令行参数. 测试脚本/评测平台要求你的编译器能接收如下参数:
  // compiler 模式 输入文件 -o 输出文件
   if(argc < 2) {
        printf("Usage: %s filename\n", argv[0]);
        return -1;
    }

    // 若指定有参数，则作为词法分析的输入文件
    if ((yyin = fopen(argv[1], "r")) == NULL) {
        printf("Can't open file %s\n", argv[1]);
        return -1;
    }

    yyparse();
    // drawAst();
    system("pause");
    return 0;
}