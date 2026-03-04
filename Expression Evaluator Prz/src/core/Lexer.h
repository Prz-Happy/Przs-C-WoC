//
// Created by Pei15 on 2026/3/4.
//
#ifndef EXPRESSION_EVALUATOR_PRZ_LEXER_H
#define EXPRESSION_EVALUATOR_PRZ_LEXER_H
#include <cmath>
#include <string>
#include "Token.h"
// =========================
// Lexer：词法分析器
// 把输入字符串切分为 Token 流
// 负责识别数字、运算符、括号等基本记号
// =========================
class Lexer {
public:
    explicit Lexer(std::string text);

    /*
     * getNextToken():
     * 每次调用返回下一个 Token，并推进内部游标。
     * 规则：
     *  - 跳过空白
     *  - 识别数字（含小数点）
     *  - 识别单字符运算符和括号
     *  - 识别 "**" 为 POW（优先于 "*"）
     *  - 不能识别则抛异常
     */
    Token getNextToken();

private:
    std::string text_; // 原始输入
    std::size_t pos_; // 当前读取位置
    char current_char_; // 当前字符
    // 向前移动一个字符，并更新 current_char_
    void advance();

    // 跳过连续空白
    void skipWhitespace();

    /*
     * 读取一个数（NUMBER）：
     * - digits* ('.' digits*)?   或   '.' digits+
     * - 允许前置 '.'（例如 ".5"）
     * - 允许尾随 '.'（例如 "10."）
     * - 但不允许只有 "."（没有任何数字）
     * 返回字符串形式的字面量，后续由 Interpreter 使用 stod 转为 double
     */
    std::string readNumber();
};

#endif //EXPRESSION_EVALUATOR_PRZ_LEXER_H
