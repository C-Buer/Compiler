#ifndef FIRSTLAYER_HPP
#define FIRSTLAYER_HPP

#include "LexerLevel.hpp"
#include <cstdint>

class FirstLayer : public LexerLevel
{
  public:
    std::vector<Token> processChunk(const SourceChunk &chunk) override;

  private:
    void splitIntoTokens(const std::string &text, std::vector<std::string> &rawTokens);
    void classifyTokens(const std::vector<std::string> &rawTokens, std::vector<Token> &outTokens);
    std::uint32_t fnv1aHash(const std::string &str);
};

#endif
