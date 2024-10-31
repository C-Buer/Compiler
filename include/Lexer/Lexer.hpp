#ifndef LEXER_HPP
#define LEXER_HPP
#include "TString.hpp"
#include <unordered_set>
#include <vector>

enum class TokenType
{
    Identifier,
    Keyword,
    Number,
    String,
    EndOfFile,
    Unknown
};

struct Token
{
    TokenType type;
    TString lexeme;
    int line;
    int column;
};

class Lexer
{
  public:
    Lexer(const TString &source);

    void addKeyword(const TString &keyword);

    std::vector<Token> tokenize();

  private:
    std::string source_;
    size_t current_;
    int line_;
    int column_;
    std::unordered_set<TString> keywords_;

    char peek() const;
    char advance();
    bool isAtEnd() const;
    void skipWhitespace();
    Token makeToken(TokenType type, const TString &lexeme);
    Token identifier();
    Token number();
    Token stringLiteral();
};

#endif