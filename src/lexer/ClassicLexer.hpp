#ifndef CLASSICLEXER_HPP
#define CLASSICLEXER_HPP

#include "LexerLevel.hpp"
#include <string>
#include <vector>


class ClassicLexer
{
  public:
    std::vector<Token> processFullSource(const std::string &source);
};

#endif
