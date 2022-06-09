## 文法产生式

G[<program>]:
<program> → { <segment> }  
<segment> → <type> <def>                      全局变量或者函数名定义或声明
<type> → 'int' | 'void'                       基本类型，int或void
<def> → ident <idtail>                        全局变量或者函数名定义
<deflist> → ','  <defdata> <deflist> | ';'    同类型多个变量名列表
<defdata> → ident <varrdef>                   数组变量或一般变量
<varrdef> → { '[' num ']' }                   数组元素纬度指定
<idtail> → <varrdef> <deflist> | '(' <para> ')' <functail>   
<functail> → <blockstat> | ';'                只有分号函数声明，含有语句块则是函数定义
<para> → <onepara> { ','  <onepara> } | ε     函数参数
<onepara> → <type> <paradata>                 函数形参定义，<type>不能为void
<paradata> → ident <paradatatail>             基本变量或数组定义变量
<paradatatail> → '[' num? ']' { '[' num ']' } | ε
<subprogram> → { <onestatement> }             多个语句
<onestatement> -> <localdef> | <statement>    局部变量定义或者语句
<localdef> → <type> <defdata> <deflist>      本地定义语句，<type>不能为void
<breakstat> → 'break' ';'                    break语句
<continuestat> → 'continue' ';'              continue语句
<returnstat> → 'return' [ <expr> ] ';'       返回语句
<assignstat> → <expr> ';'                    赋值语句或者表达式语句
<blockstat> → '{' <subprogram> '}'           语句块
<emptystat> → ';'
<whilestat> → 'while' '(' <expr> ')' <statement>  while循环语句
<ifstat> → 'if'  '(' <expr> ')' <statement> [ 'else' <statement> ]   分支语句
<statement> → <whilestat> |
    <ifstat> |
    <breakstat> |
    <continuestat> |
    <returnstat> |
    <blockstat> |
    <assignstat> |
    <emptystat>

<expr> → <assexpr>              表达式（赋值表达式或不含等号的表达式）
<lval> → ident { '[' <expr> ']' }       左值
<assexpr> → <orexpr> <asstail>  赋值表达式
<asstail> → '=' <assexpr> <asstail> | ε 
<orexpr> → <andexpr> { '||' <andexpr> }        逻辑或表达式
<andexpr> → <cmpexpr> { '&&' <cmpexpr> }       逻辑与表达式
<cmpexpr> → <aloexpr> { <cmps> <aloexpr> }     关系表达式
<cmps> → '>=' | '>' | '<' | '<=' | '==' | '!=' 关系运算符
<aloexpr> → <item> { <addsub> <item> }         加减表达式
<addsub> → '+' | '-'                           加减运算符
<item> → <factor> { <muldiv> <factor> }        乘除余表达式
<muldiv> → '*' | '/' | '%'                     乘除余运算符
<factor> → <lop> <factor> | <selfexpr> ｜ <funccall> | <elem>  一元运算，含函数调用，自增自减运算
<lop>  → '!' | '-'                             求负和逻辑非运算符
<funccall> → ident '(' <realarg> ')'           函数调用
<selfexpr> → <selfop> <lval> | <lval> <selfop> 自增自减运算
<selfop> → '++' ｜ '--'                         自增自减运算符
<elem> → ident { '[' <expr> '] } | '(' <expr> ')' | <literal>  右值：变量，数组，常量，表达式

<literal> → num                                字面量
<realarg> → <expr> {',' <expr>} | ε            实际参数列表

非终结符为<>括起来的符号
终结符是由单引号括起的串，或者是 ident 、num这样的记号
ident代表标识符，num代表整型常量
