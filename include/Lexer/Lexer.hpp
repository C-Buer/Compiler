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
    Operator,
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

    void addOperator(const TString &op);

    std::vector<Token> tokenize();

  private:
    TString source_;
    size_t current_;
    int line_;
    int column_;
    std::unordered_set<TString> keywords_;
    std::vector<TString> operators_;

    inline char peek() const
    {
        if (isAtEnd())
            return '\0';
        return source_[current_];
    }

    inline char peekNext() const
    {
        return source_[current_ + 1];
    }

    inline char advance()
    {
        char c = source_[current_++];
        if (c == '\n')
        {
            line_++;
            column_ = 1;
        }
        else
        {
            column_++;
        }
        return c;
    }

    inline bool isAtEnd() const
    {
        return current_ >= source_.size();
    }

    inline void skipWhitespace()
    {
        while (!isAtEnd())
        {
            char c = peek();
            if (c == ' ' || c == '\r' || c == '\t' || c == '\n')
            {
                advance();
            }
            else
            {
                break;
            }
        }
    }

    inline Token makeToken(TokenType type, const TString &lexeme, int tokenLine, int tokenColumn)
    {
        return Token{type, lexeme, tokenLine, tokenColumn};
    }
    Token identifier();
    Token number();
    Token stringLiteral();
    Token op();

    void sortOperators();
};

#endif