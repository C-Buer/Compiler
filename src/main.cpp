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

    lexer.addKeyword("if"_T);
    lexer.addKeyword("else"_T);
    lexer.addKeyword("for"_T);
    lexer.addKeyword("while"_T);
    lexer.addKeyword("print"_T);

    lexer.addOperator("=="_T);
    lexer.addOperator("!="_T);
    lexer.addOperator("<="_T);
    lexer.addOperator(">="_T);
    lexer.addOperator("++"_T);
    lexer.addOperator("--"_T);
    lexer.addOperator("+="_T);
    lexer.addOperator("-="_T);
    lexer.addOperator("*="_T);
    lexer.addOperator("/="_T);
    lexer.addOperator("+"_T);
    lexer.addOperator("-"_T);
    lexer.addOperator("*"_T);
    lexer.addOperator("/"_T);
    lexer.addOperator("="_T);
    lexer.addOperator("<"_T);
    lexer.addOperator(">"_T);
    lexer.addOperator("("_T);
    lexer.addOperator(")"_T);
    lexer.addOperator("_T"_T);
    lexer.addOperator("{"_T);
    lexer.addOperator("}"_T);
    lexer.addOperator(";"_T);

    std::vector<Token> tokens = lexer.tokenize();

    for (const auto &token : tokens)
    {
        std::cout << "Type: ";
        switch (token.type)
        {
        case TokenType::Identifier:
            std::cout << "Identifier";
            break;
        case TokenType::Keyword:
            std::cout << "Keyword";
            break;
        case TokenType::Number:
            std::cout << "Number";
            break;
        case TokenType::String:
            std::cout << "String";
            break;
        case TokenType::Operator:
            std::cout << "Operator";
            break;
        case TokenType::EndOfFile:
            std::cout << "EndOfFile";
            break;
        case TokenType::Unknown:
            std::cout << "Unknown";
            break;
        }
        std::cout << ", Lexeme: \"" << token.lexeme << "\""
                  << ", Line: " << token.line << ", Column: " << token.column << "\n";
    }

    return 0;
}