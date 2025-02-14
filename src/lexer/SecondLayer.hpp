#ifndef SECONDLAYER_HPP
#define SECONDLAYER_HPP

#include "LexerLevel.hpp"

enum class KnownKeyword
{
    IF,
    FOR,
    WHILE,
    NONE
};

KnownKeyword checkKeyword(std::uint32_t hash, const std::string &text);

class SecondLayer : public LexerLevel
{
  public:
    std::vector<Token> processTokens(const std::vector<Token> &tokens) override;
};

#endif
