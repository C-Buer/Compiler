#ifndef SECONDLAYER_HPP
#define SECONDLAYER_HPP

#include "LexerLevel.hpp"
#include <string>
#include <unordered_set>


class SecondLayer : public LexerLevel
{
  private:
    std::unordered_set<std::string> keywords;

  public:
    SecondLayer();
    void addKeyword(const std::string &kw);
    std::vector<Token> processTokens(const std::vector<Token> &tokens) override;
};

#endif
