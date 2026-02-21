/*#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>

enum TokenType {
    INTEGER,
    PLUS,
    EOF_TOKEN,
};

class Token {
public:
    TokenType type;
    int value;
    Token(TokenType t, int v) : type(t), value(v) {};
};

class Interpreter {
    explicit Interpreter(const std::string& text)
        : text_(text), pos_(0), current_token_(EOF_TOKEN, 0) {}
};*/
#include <iostream>
#include <string>

int main() {
    std::string str = "123.456";
    try {
        double num = std::stod(str);
        std::cout << "The double value is: " << num << std::endl;
    } catch (const std::invalid_argument& ia) {
        std::cerr << "Invalid argument: " << ia.what() << '\n';
    } catch (const std::out_of_range& oor) {
        std::cerr << "Out of Range error: " << oor.what() << '\n';
    }
    return 0;
}
