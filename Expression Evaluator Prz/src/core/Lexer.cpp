//
// Created by Pei15 on 2026/3/4.
//
#include "Lexer.h"
#include <stdexcept>
#include <utility>
#include <cctype>

// 构造器：保存输入并初始化当前字符
Lexer::Lexer(std::string text)
    : text_(std::move(text)), pos_(0),
      current_char_(text_.empty() ? '\0' : text_.front()) {
}

// advance: 将读取位置前移一位，并更新 current_char_
void Lexer::advance() {
    ++pos_;
    current_char_ = (pos_ >= text_.size()) ? '\0' : text_[pos_];
}

// 跳过连续的空白字符（空格、制表、换行等）
void Lexer::skipWhitespace() {
    while (current_char_ != '\0' &&
           std::isspace(static_cast<unsigned char>(current_char_))) {
        advance();
    }
}

// getNextToken: 逐字符识别并返回下一个 token
Token Lexer::getNextToken() {
    while (current_char_ != '\0') {
        if (std::isspace(current_char_)) {
            skipWhitespace();
            continue;
        }

        // 数字：支持 12、12.34、.5、10.
        if (std::isdigit(current_char_) || current_char_ == '.') {
            return Token(TokenType::NUMBER, readNumber());
        }

        // 单字符 token
        if (current_char_ == '+') {
            advance();
            return Token(TokenType::PLUS, "+");
        }
        if (current_char_ == '-') {
            advance();
            return Token(TokenType::MINUS, "-");
        }
        if (current_char_ == '/') {
            advance();
            return Token(TokenType::DIV, "/");
        }
        if (current_char_ == '%') {
            advance();
            return Token(TokenType::MOD, "%");
        }
        if (current_char_ == '(') {
            advance();
            return Token(TokenType::LPAREN, "(");
        }
        if (current_char_ == ')') {
            advance();
            return Token(TokenType::RPAREN, ")");
        }

        // 幂：支持 ^ 与 **
        if (current_char_ == '^') {
            advance();
            return Token(TokenType::POW, "^");
        }

        // '*' 可能是 MUL，也可能是 "**"（POW）
        if (current_char_ == '*') {
            advance();
            if (current_char_ == '*') {
                // 识别 **
                advance();
                return Token(TokenType::POW, "**");
            }
            return Token(TokenType::MUL, "*");
        }

        // 走到这里说明遇到未知字符
        throw std::runtime_error(std::string("Invalid character: ") + current_char_);
    }

    // 输入结束
    return Token(TokenType::END, "");
}

// readNumber: 从当前位置读取一个数字字面量，返回字符串形式
std::string Lexer::readNumber() {
    std::string result;
    bool seen_dot = false;
    bool seen_digit = false;

    while (current_char_ != '\0') {
        char uc = current_char_;

        if (std::isdigit(uc)) {
            seen_digit = true;
            result.push_back(current_char_);
            advance();
            continue;
        }

        if (current_char_ == '.') {
            if (seen_dot) break; // 第二个 '.' 结束本次数字读取
            seen_dot = true;
            result.push_back(current_char_);
            advance();
            continue;
        }

        // 其他字符结束数字读取
        break;
    }

    // "." 这种没有任何数字的不合法
    if (!seen_digit) {
        throw std::runtime_error("Invalid number format");
    }

    return result;
}
