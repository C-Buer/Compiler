#include "Lexer\Lexer.hpp"
#include <iostream>

int main()
{
    TString sourceCode = R"(
        if (x == 10) {
            print("x is ten");
        }
    )";

    Lexer lexer(sourceCode);
    lexer.addKeyword("if"_T);
    lexer.addKeyword("else"_T);
    lexer.addKeyword("for"_T);
    lexer.addKeyword("while"_T);
    lexer.addKeyword("print"_T);

    std::vector<Token> tokens = lexer.tokenize();

    for (const auto &token : tokens)
    {
        std::cout << "Type: " << static_cast<int>(token.type) << ", Lexeme: " << token.lexeme
                  << ", Line: " << token.line << ", Column: " << token.column << "\n";
    }

    return 0;
}
