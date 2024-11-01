#include "Lexer\Lexer.hpp"
#include <iostream>

int main()
{
    TString sourceCode =
        R"(
            if (x == 10) {
                print("x is ten");
            } else if (x != 20) {
                print("x is not twenty");
            }
            x += 5;
        )";

    Lexer lexer(sourceCode);

    lexer.addKeyword("if");
    lexer.addKeyword("else");
    lexer.addKeyword("for");
    lexer.addKeyword("while");
    lexer.addKeyword("print");

    lexer.addOperator("==");
    lexer.addOperator("!=");
    lexer.addOperator("<=");
    lexer.addOperator(">=");
    lexer.addOperator("++");
    lexer.addOperator("--");
    lexer.addOperator("+=");
    lexer.addOperator("-=");
    lexer.addOperator("*=");
    lexer.addOperator("/=");
    lexer.addOperator("+");
    lexer.addOperator("-");
    lexer.addOperator("*");
    lexer.addOperator("/");
    lexer.addOperator("=");
    lexer.addOperator("<");
    lexer.addOperator(">");
    lexer.addOperator("(");
    lexer.addOperator(")");
    lexer.addOperator("");
    lexer.addOperator("{");
    lexer.addOperator("}");
    lexer.addOperator(";");

    std::vector<Token> tokens = lexer.tokenize();

    for (const auto &token : tokens)
    {
        std::cout << token.printToken() << std::endl;
    }

    return 0;
}