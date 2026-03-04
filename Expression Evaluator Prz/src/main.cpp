#include <iostream>
#include "core/Interpreter.h"

int main() {
    // 简单的 REPL（交互式读取-求值-打印）循环
    while (true) {
        std::cout << "calc> ";

        std::string text;
        // 使用 std::getline 来支持包含空格的行输入；Windows 下 Ctrl+Z 结束输入流
        if (!std::getline(std::cin, text)) break; // Windows 下 Ctrl+Z 结束
        if (text.empty()) continue; // 空行忽略

        try {
            // 把文本交给词法分析器，然后构造解释器进行求值
            Lexer lexer(text);
            Interpreter interpreter(std::move(lexer));
            std::cout << interpreter.parse() << "\n";
        } catch (const std::exception &ex) {
            // 统一输出词法 / 语法 / 数学错误信息
            std::cout << ex.what() << "\n";
        }
    }
    return 0;
}
