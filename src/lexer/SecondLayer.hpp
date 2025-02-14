#ifndef SECONDLAYER_HPP
#define SECONDLAYER_HPP
#include "LexerLevel.hpp"

class SecondLayer : public LexerLevel
{
  public:
    std::vector<Token> processChunk(const SourceChunk &chunk) override;
    std::vector<Token> processTokens(const std::vector<Token> &tokens) override;
};

#endif
