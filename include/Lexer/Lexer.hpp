#ifndef LEXER_HPP
#define LEXER_HPP

#include "TString.hpp"
#include <unordered_set>

namespace std
{
template <> struct hash<TString>
{
    size_t operator()(const TString &str) const
    {
        return std::hash<std::string>()(str.c_str());
    }
};
} // namespace std

enum class TokenType
{
    Identifier,
    Number,
    Keyword,
    Symbol,
    Operator,
    StringLiteral,
    EndOfFile
};

struct Token
{
    TokenType type;
    TString value;

    Token(TokenType type, const TString &value);
};

class Lexer
{
  private:
    TString source;
    size_t position;
    std::unordered_set<TString> keywords;
    std::unordered_set<TString> operators;

    char current_char() const;
    void advance();
    void skip_whitespace();
    bool is_keyword(const TString &str) const;

  public:
    Lexer(const TString &source);
    void add_keyword(const TString &keyword);
    void add_operator(const TString &op);
    Token next_token();
};

#endif // LEXER_HPP