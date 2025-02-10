#ifndef FIRSTLAYER_HPP
#define FIRSTLAYER_HPP

#include "LexerLevel.hpp"

class FirstLayer : public LexerLevel
{
  public:
    std::vector<Token> processChunk(const SourceChunk &chunk) override;

  private:
    Token createToken(const std::string &sub);
};

#endif
