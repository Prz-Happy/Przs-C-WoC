//
// Created by Pei15 on 2026/3/2.
//
#include <stdexcept>
#include "Interpreter.h"

// 文件说明：
// Interpreter.cpp 实现了递归下降解析器（Recursive Descent Parser），
// 同时在解析过程中直接进行计算（边解析边求值）。
//
// 解析规则（高层描述）：
// - expr -> term ((PLUS|MINUS) term)*
// - term -> power ((MUL|DIV|MOD) power)*
// - power -> factor (POW power)?    // 右结合
// - factor -> (PLUS|MINUS) factor | NUMBER | '(' expr ')'
//
// 优先级（从高到低）：
//  1. factor（一元 +/-、数字、括号）
//  2. power（幂运算，右结合）
//  3. term（乘、除、模）
//  4. expr（加、减）
//
// 错误处理：
// - 词法错误由 Lexer 抛出（std::runtime_error）
// - 语法错误通过 static 函数 syntaxError 抛出 std::runtime_error
// - 数学错误（如除以零）直接抛出 std::runtime_error

// 增加：语法错误统一处理函数（在头文件中声明为 static）
// 将抛出 runtime_error，使上层可以捕获或让程序终止并输出错误信息。
void Interpreter::syntaxError(const std::string &msg) {
    // 抛出运行时错误，消息统一前缀以便区分
    throw std::runtime_error(std::string("Syntax error: ") + msg);
}

// parse(): 解析入口
// - 调用 expr() 完成整个表达式的解析与求值
// - 解析结束后，要求当前 token 为 END（输入已被完全消费）
//   否则报告尾部多余输入（trailing input），帮助捕获诸如 "1+2abc" 的错误
double Interpreter::parse() {
    double result = expr();
    if (current_token_.type != TokenType::END) {
        // 如果还有未消费的 token，说明有尾部垃圾或语法错误
        syntaxError("trailing input: " + current_token_.lexeme);
    }
    return result;
}

// eat(expected): 匹配并消费当前 token
// - 如果当前 token 类型等于 expected，则读取下一个 token
// - 否则通过 syntaxError 报语法错误，包含当前词素便于定位问题
void Interpreter::eat(TokenType expected) {
    if (current_token_.type == expected) {
        current_token_ = lexer_.getNextToken();
    } else {
        syntaxError("unexpected token: " + current_token_.lexeme);
    }
}

// expr: 处理加减运算（最低优先级）
// expr -> term ((PLUS|MINUS) term)*
// 实现思路：先解析一个 term 得到初始结果，然后在循环中处理后续的加/减操作
double Interpreter::expr() {
    double result = term();
    while (current_token_.type == TokenType::PLUS ||
           current_token_.type == TokenType::MINUS) {
        if (current_token_.type == TokenType::PLUS) {
            eat(TokenType::PLUS); // 消费 '+'
            result += term(); // 把下一个 term 的值加到结果上
        } else {
            eat(TokenType::MINUS); // 消费 '-'
            result -= term(); // 把下一个 term 的值从结果中减去
        }
    }
    return result;
}

// term: 处理乘除与取模（中等优先级）
// term -> power ((MUL|DIV|MOD) power)*
// 与 expr 类似，先解析一个 power，然后在循环中处理 * / % 等操作
double Interpreter::term() {
    double result = power();
    while (current_token_.type == TokenType::MUL ||
           current_token_.type == TokenType::DIV ||
           current_token_.type == TokenType::MOD) {
        if (current_token_.type == TokenType::MUL) {
            eat(TokenType::MUL);
            result *= power();
        } else if (current_token_.type == TokenType::DIV) {
            eat(TokenType::DIV);
            double rhs = power();
            // 防止除以零
            if (rhs == 0.0) throw std::runtime_error("Math error: division by zero");
            result /= rhs;
        } else {
            eat(TokenType::MOD);
            double rhs = power();
            if (rhs == 0.0) throw std::runtime_error("Math error: modulo by zero");
            // 对浮点数使用 std::fmod 以获得更合理的余数定义
            result = std::fmod(result, rhs);
        }
    }
    return result;
}

// power: 幂运算，右结合
// power -> factor (POW power)?
// 注意幂运算右结合的实现：遇到 POW 时，先 eat(POW) 然后递归调用 power()
// 例如解析 a ^ b ^ c 会形成 a ^ (b ^ c)
double Interpreter::power() {
    double left = factor();
    if (current_token_.type == TokenType::POW) {
        eat(TokenType::POW);
        double right = power();
        left = std::pow(left, right);
    }
    return left;
}

// factor: 处理一元运算、数字与括号
// factor -> (PLUS|MINUS) factor | NUMBER | '(' expr ')'
// 实现要点：
//  - 一元 +/- 直接递归调用 factor 以保证例如 - -3 正确处理
//  - NUMBER 使用当前 token 的 lexeme，并通过 std::stod 转成 double
//  - 括号表达式会在读到 RPAREN 之前递归计算内部 expr
//  - 其它情况视为语法错误
double Interpreter::factor() {
    // 一元 +（无操作，仅返回内部因子）
    if (current_token_.type == TokenType::PLUS) {
        eat(TokenType::PLUS);
        return +factor();
    }

    // 一元 -（取相反数）
    if (current_token_.type == TokenType::MINUS) {
        eat(TokenType::MINUS);
        return -factor();
    }

    // 直接数字字面量
    if (current_token_.type == TokenType::NUMBER) {
        Token token = current_token_;
        eat(TokenType::NUMBER);
        // 使用 std::stod 将字符串字面量转换为 double
        return std::stod(token.lexeme);
    }

    // 括号表达式：'(' expr ')'
    if (current_token_.type == TokenType::LPAREN) {
        eat(TokenType::LPAREN);
        double result = expr();
        eat(TokenType::RPAREN);
        return result;
    }

    // 到达此处说明无法识别为合法的因子，抛出语法错误以便上层捕获
    syntaxError("factor expected");
    return 0; // 不可达：仅为让编译器满足返回值要求
}
