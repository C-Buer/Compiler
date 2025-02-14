#ifndef TOKEN_HPP
#define TOKEN_HPP
#include <string>

enum class TokenType
{
    Identifier,
    Number,
    Keyword,
    Operator,
    Unknown
};
struct Token
{
    TokenType type;
    std::string text;
};

#endif
