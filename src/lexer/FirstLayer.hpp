#ifndef FIRSTLAYER_HPP
#define FIRSTLAYER_HPP
#include "LexerLevel.hpp"

class FirstLayer : public LexerLevel
{
  public:
    std::vector<Token> processChunk(const SourceChunk &chunk) override;
    std::vector<Token> processTokens(const std::vector<Token> &tokens) override;
};

#endif
