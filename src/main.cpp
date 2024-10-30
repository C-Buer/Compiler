#include "Lexer\Lexer.hpp"
#include <iostream>

int main()
{
    std::string sourceCode = R"(
        if (x == 10) {
            print("x is ten");
        }
    )";

    Lexer lexer(sourceCode);
    lexer.addKeyword(TString("if"));
    lexer.addKeyword(TString("else"));
    lexer.addKeyword(TString("for"));
    lexer.addKeyword(TString("while"));
    lexer.addKeyword(TString("print"));

    std::vector<Token> tokens = lexer.tokenize();

    for (const auto &token : tokens)
    {
        std::cout << "Type: " << static_cast<int>(token.type) << ", Lexeme: " << token.lexeme
                  << ", Line: " << token.line << ", Column: " << token.column << "\n";
    }

    return 0;
}
