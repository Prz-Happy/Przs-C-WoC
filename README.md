# Expression Evaluator（表达式求值器）

这是一个用 C++ 实现的简单表达式求值器（解释器），支持小数运算与常见算术运算：

- 加法（+）、减法（-）
- 乘法（*）、除法（/）
- 取模（%）
- 幂运算（^ 或 **）
- 支持一元正负号（+3, -5）
- 支持括号改变优先级，如 (1 + 2) * 3

代码组织（关键文件）

- src/core/Token.h   : Token 与 TokenType 定义（词法单元）
- src/core/Lexer.h   : 词法分析器接口
- src/core/Lexer.cpp : 词法分析器实现（识别数字、运算符、括号等）
- src/core/Interpreter.h/.cpp : 递归下降解析器与求值逻辑
- src/main.cpp       : 简单的 REPL（交互式命令行）入口

语法

```
expr   -> term ((PLUS|MINUS) term)*
term   -> power ((MUL|DIV|MOD) power)*
power  -> factor (POW power)?     // 右结合
factor -> (PLUS|MINUS) factor | NUMBER | '(' expr ')'
```

构建（在 Windows / PowerShell 下示例）

1. 使用 CMake 生成构建系统并编译：

```powershell
cd "D:\Workspaces\CandCPP\Expression Evaluator Prz"
cmake -S . -B cmake-build-debug
cmake --build cmake-build-debug --config Debug
```

2. 运行可执行文件（路径以本地构建输出为准）：

```powershell
& "./cmake-build-debug/Expression_Evaluator_Prz.exe"
```

使用示例

交互式会话示例：

```
calc> 3 + 5
8
calc> 12 - 5 + 3
10
calc> 2 * (3 + 4)
14
calc> 2 ^ 3 ^ 2   
512
calc> .5 + 1
1.5
calc> 10. / 4
2.5
```

参考文献

https://ruslanspivak.com/lsbasi-part1/

https://ruslanspivak.com/lsbasi-part2/

https://ruslanspivak.com/lsbasi-part3/

https://ruslanspivak.com/lsbasi-part4/

https://ruslanspivak.com/lsbasi-part5/

https://ruslanspivak.com/lsbasi-part6/

参照以上文献完成了递归下降解调器的具体设计。

参照以下文献初步了解了AST，但实际上该项目并未采用此方法。

https://www.youtube.com/watch?v=Wz85Hiwi5MY
