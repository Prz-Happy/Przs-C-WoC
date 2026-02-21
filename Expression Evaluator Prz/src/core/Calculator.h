//
// Created by Pei15 on 2026/2/21.
//

#ifndef EXPRESSION_EVALUATOR_PRZ_CALCULATOR_H
#define EXPRESSION_EVALUATOR_PRZ_CALCULATOR_H

#endif //EXPRESSION_EVALUATOR_PRZ_CALCULATOR_H

#include <vector>
#include <stack>
#include <string>

using std::string;
using std::stack;
using std::vector;

class Calculator {
public:
    // 逆波兰表达式求值
    int evalRPN(const vector<string>& tokens);
};