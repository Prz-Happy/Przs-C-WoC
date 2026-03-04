//
// Created by Pei15 on 2026/3/2.
//

#ifndef EXPRESSION_EVALUATOR_PRZ_INTERPRETER_H
#define EXPRESSION_EVALUATOR_PRZ_INTERPRETER_H
#include "Lexer.h"
#include <string>
#include <utility>

// =========================
// Interpreter：语法分析 + 计算
// 使用递归下降解析（recursive descent parser），边解析边求值。
// 支持的运算符： + - * / % ^ ( 幂运算支持 ^ 和 ** )
// 支持一元 + 和 -，支持小数运算。
// =========================
class Interpreter {
public:
    // 构造器接收一个已初始化的 Lexer（按值接收并移动）
    explicit Interpreter(Lexer lexer) : lexer_(std::move(lexer)) {
        // 初始化时取第一个 token
        current_token_ = lexer_.getNextToken();
    }

    /*
     * parse():
     * 解析入口，解析整个表达式并返回计算结果。
     * 要求在表达式末尾遇到 END，否则报错（防止尾部垃圾输入）。
     */
    double parse();

private:
    Lexer lexer_; // 词法分析器实例（拥有）
    Token current_token_{TokenType::END, ""}; // 当前正在处理的 token

    // 语法错误处理：在实现文件中定义，统一抛出异常
    static void syntaxError(const std::string &msg);

    /*
     * eat(expected):
     * 若当前 token 类型匹配 expected，则消费它并读下一个 token；
     * 否则抛语法错误。
     */
    void eat(TokenType expected);

    // expr : term ((PLUS|MINUS) term)*
    // 处理加减（最低优先级）
    double expr();

    // term : power ((MUL|DIV|MOD) power)*
    // 处理乘除与取模（中等优先级）
    double term();

    // power : factor (POW power)?
    // 幂运算右结合：a^b^c = a^(b^c)
    double power();

    // factor : (PLUS|MINUS) factor | NUMBER | '(' expr ')'
    // 处理：一元正负号 / 数字 / 括号
    double factor();
};

#endif // EXPRESSION_EVALUATOR_PRZ_INTERPRETER_H
