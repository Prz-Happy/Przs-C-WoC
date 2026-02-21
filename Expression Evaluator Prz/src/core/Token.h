//
// Created by Pei15 on 2026/2/21.
//

#ifndef EXPRESSION_EVALUATOR_PRZ_TOKEN_H
#define EXPRESSION_EVALUATOR_PRZ_TOKEN_H

#endif //EXPRESSION_EVALUATOR_PRZ_TOKEN_H

#include <vector>
#include <stack>
#include <string>

using std::string;
using std::stack;
using std::vector;

class Token {
public:
    string value; // token的值，可以是数字或运算符
    stack<double> token;
    inline void readValue();


};
void Token::readValue() {
    int pos = 0;
    while ((pos = value.find('.', pos)) != string::npos) {
        value.erase(pos, 1); // 删除小数点

    }
}