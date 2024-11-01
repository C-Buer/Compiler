#ifndef LEXER_HPP
#define LEXER_HPP

#include <TString.hpp>

#include <algorithm>
#include <unordered_map>
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
    inline TString printToken() const;
};

class Lexer
{
  public:
    inline Lexer(const TString &source);

    inline void addKeyword(const TString &keyword);

    inline void addOperator(const TString &op);

    std::vector<Token> tokenize();

  private:
    TString source_;
    size_t current_;
    int line_;
    int column_;
    std::unordered_set<TString> keywords_;
    std::vector<TString> operators_;

    inline char peek() const;
    inline char peekNext() const;
    inline char advance();
    inline bool isAtEnd() const;
    inline void skipWhitespace();
    inline Token makeToken(TokenType type, const TString &lexeme, int tokenLine, int tokenColumn);
    Token identifier();
    Token number();
    Token stringLiteral();
    Token op();

    inline void sortOperators();
};

TString Token::printToken() const
{
    static std::unordered_map<TokenType, TString> tokenTypeMap = {
        {TokenType::Identifier, "Identifier"}, {TokenType::Keyword, "Keyword"},   {TokenType::Number, "Number"},
        {TokenType::String, "String"},         {TokenType::Operator, "Operator"}, {TokenType::EndOfFile, "EndOfFile"},
        {TokenType::Unknown, "Unknown"}};

    return std::format("Type: {}, Lexeme: \"{}\", Line: {}, Column: {}\n", tokenTypeMap[type], lexeme, line, column);
}

Lexer::Lexer(const TString &source) : source_(source), current_(0), line_(1), column_(1)
{
}

void Lexer::addKeyword(const TString &keyword)
{
    keywords_.insert(keyword);
}

void Lexer::addOperator(const TString &op)
{
    operators_.push_back(op);
}

void Lexer::sortOperators()
{
    std::ranges::sort(operators_, std::ranges::greater());
}

char Lexer::peek() const
{
    if (isAtEnd())
        return '\0';
    return source_[current_];
}

char Lexer::peekNext() const
{
    return source_[current_ + 1];
}

char Lexer::advance()
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

bool Lexer::isAtEnd() const
{
    return current_ >= source_.size();
}

void Lexer::skipWhitespace()
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

Token Lexer::makeToken(TokenType type, const TString &lexeme, int tokenLine, int tokenColumn)
{
    return Token{type, lexeme, tokenLine, tokenColumn};
}
#endif