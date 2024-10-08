#include "Lexer/Lexer.hpp"

#include <iostream>

void test_lexer()
{
    TString input("int x = 42; if (x > 10) return x + 1;");
    Lexer lexer(input);
    lexer.add_keyword("mykeyword");
    lexer.add_operator("++");
    Token token = lexer.next_token();
    while (token.type != TokenType::EndOfFile)
    {
        puts("Token: Type = ");
        switch (token.type)
        {
        case TokenType::Identifier:
            puts("Identifier");
            break;
        case TokenType::Number:
            puts("Number");
            break;
        case TokenType::Keyword:
            puts("Keyword");
            break;
        case TokenType::Symbol:
            puts("Symbol");
            break;
        case TokenType::Operator:
            puts("Operator");
            break;
        case TokenType::StringLiteral:
            puts("StringLiteral");
            break;
        case TokenType::EndOfFile:
            puts("EndOfFile");
            break;
        }
        puts(TString(", Value = ") + token.value);
        token = lexer.next_token();
    }
}