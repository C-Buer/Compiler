#ifndef LEXERLEVEL_HPP
#define LEXERLEVEL_HPP
#include "SourceChunk.hpp"
#include "Token.hpp"
#include <vector>

class LexerLevel
{
  public:
    virtual ~LexerLevel() = default;
    virtual std::vector<Token> processChunk(const SourceChunk &chunk) = 0;
    virtual std::vector<Token> processTokens(const std::vector<Token> &tokens) = 0;
};

#endif
