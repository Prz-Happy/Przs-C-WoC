#ifndef EXPRESSION_EVALUATOR_PRZ_TOKEN_H
#define EXPRESSION_EVALUATOR_PRZ_TOKEN_H

#include <string>
#include <utility>

// =========================
// Token 定义
// 负责把词法单元（token）抽象为程序内部数据结构，
// 每一个 token 包含类型与原始字面量（lexeme）。
// 例如：NUMBER "3.14"，PLUS "+"，POW "**"
// =========================
enum class TokenType {
    NUMBER, // 支持整数与小数，如 12、3.14、.5、10.
    PLUS, // +
    MINUS, // -
    MUL, // *
    DIV, // /
    MOD, // %
    POW, // ^ 或 **，表示幂运算
    LPAREN, // (
    RPAREN, // )
    END // 输入结束标记（EOF）
};

/*
 * Token = (类型, 原始字面量)
 * 例如：NUMBER "3.14"，PLUS "+"，POW "**"
 * lexeme 保留源文本形式，便于在报错或转换时使用原始字符串。
 */
struct Token {
    TokenType type; // token 类型
    std::string lexeme; // token 的原始字面量
    Token(TokenType t, std::string s) : type(t), lexeme(std::move(s)) {
    }
};
#endif // EXPRESSION_EVALUATOR_PRZ_TOKEN_H
