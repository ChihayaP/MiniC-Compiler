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
extern void prnSymbol();
extern void semanticAnalysisMain();
extern void printIRMain();
extern void prnVarSymbolMain();
extern char SYMBOL_FILE[50];
extern char IR_FILE[50];
extern char PNG_FILE[50];
char TEST_FILE[50];
int filePathInput(int argc, const char *argv[]);
int ctrl[3];

int main(int argc, const char *argv[]) {
  // 解析命令行参数. 测试脚本/评测平台要求你的编译器能接收如下参数:
  // compiler 模式 输入文件 -o 输出文件
    if(filePathInput(argc,argv)==-1) {
        return -1;
    }
    // 若指定有参数，则作为词法分析的输入文件
    if ((yyin = fopen(TEST_FILE, "r")) == NULL) {
        printf("Can't open file %s\n", argv[1]);
        return -1;
    }
    yyparse();
    semanticAnalysisMain();
    // prnSymbol();
    if(ctrl[0]) {
        // drawAst();
    }
    if(ctrl[1]) {
        printIRMain();
    }
    if(ctrl[2]) {
        prnVarSymbolMain();
    }
    system("pause");
    return 0;
}

int filePathInput(int argc, const char *argv[])
{
    int i;
    memset(ctrl,0,sizeof(ctrl));
    if(argc < 2) {
        printf("Usage: %s filename\n", argv[0]);
        return -1;
    }
    if(argc == 5) {
        strcpy(TEST_FILE,argv[4]);
        if(strcmp(argv[1],"-s")==0) {
            strcpy(SYMBOL_FILE,argv[3]);
            strcpy(IR_FILE,"./test.ir");
            strcpy(PNG_FILE,"./test.png");
            ctrl[0]=0,ctrl[1]=0,ctrl[2]=1;
        } else if(strcmp(argv[1],"-i")==0) {
            strcpy(SYMBOL_FILE,"./test.txt");
            strcpy(IR_FILE,argv[3]);
            strcpy(PNG_FILE,"./test.png");
            ctrl[0]=0,ctrl[1]=1,ctrl[2]=0;
        } else if(strcmp(argv[1],"-a")==0) {
            strcpy(SYMBOL_FILE,"./test.png");
            strcpy(IR_FILE,"./test.ir");
            strcpy(PNG_FILE,argv[3]);
            ctrl[0]=1,ctrl[1]=0,ctrl[2]=0;
        } else {
            printf("param error\n");
            return -1;
        }
    } else if(argc == 9) {
        for(i=1;i<5;i++) {
            if(strcmp(argv[i],"-s")==0) {
                strcpy(SYMBOL_FILE,argv[i+4]);
                ctrl[2]=1;
            } else if(strcmp(argv[i],"-i")==0) {
                strcpy(IR_FILE,argv[i+4]);
                ctrl[1]=1;
            } else if(strcmp(argv[i],"-a")==0) {
                strcpy(PNG_FILE,argv[i+4]);
                ctrl[0]=1;
            } else if(strcmp(argv[i],"-o")==0) {
                strcpy(TEST_FILE,argv[i+4]);
            } else {
                printf("param error\n");
                return -1;
            }
        }
    }
    return 0;
}