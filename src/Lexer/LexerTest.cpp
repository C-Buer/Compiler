#include "Lexer/Lexer.hpp"

void test_lexer()
{
    TString input(R"(
void test_lexer()
{
    TString input("int x = 42; if (x > 10) return x + 1;");
    Lexer lexer(input);
    lexer.add_keyword("mykeyword");
    lexer.add_operator("++");
    Token token = lexer.next_token();
    while (token.type != TokenType::EndOfFile)
    {
        std::puts("Token: Type = ");
        switch (token.type)
        {
        case TokenType::Identifier:
            std::puts("Identifier");
            break;
        case TokenType::Number:
            std::puts("Number");
            break;
        case TokenType::Keyword:
            std::puts("Keyword");
            break;
        case TokenType::Symbol:
            std::puts("Symbol");
            break;
        case TokenType::Operator:
            std::puts("Operator");
            break;
        case TokenType::StringLiteral:
            std::puts("StringLiteral");
            break;
        case TokenType::EndOfFile:
            std::puts("EndOfFile");
            break;
        }
        std::puts(TString(", Value = ") + token.value);
        token = lexer.next_token();
    }
})");
    Lexer lexer(input);
    lexer.add_keyword("mykeyword");
    lexer.add_operator("++");

    for (Token token = lexer.next_token(); token.type != TokenType::EndOfFile; token = lexer.next_token())
    {
        std::fputs("Token: Type = ", stdout);
        switch (token.type)
        {
        case TokenType::Identifier:
            std::fputs("Identifier", stdout);
            break;
        case TokenType::Number:
            std::fputs("Number", stdout);
            break;
        case TokenType::Keyword:
            std::fputs("Keyword", stdout);
            break;
        case TokenType::Symbol:
            std::fputs("Symbol", stdout);
            break;
        case TokenType::Operator:
            std::fputs("Operator", stdout);
            break;
        case TokenType::StringLiteral:
            std::fputs("StringLiteral", stdout);
            break;
        case TokenType::EndOfFile:
            std::fputs("EndOfFile", stdout);
            break;
        }
        std::fputs(", Value = "_T + token.value + "\n", stdout);
    }
}