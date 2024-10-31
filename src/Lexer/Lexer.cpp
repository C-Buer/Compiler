#include "Lexer\Lexer.hpp"
#include <cctype>

Lexer::Lexer(const TString &source) : source_(source), current_(0), line_(1), column_(1)
{
}

void Lexer::addKeyword(const TString &keyword)
{
    keywords_.insert(keyword);
}

std::vector<Token> Lexer::tokenize()
{
    std::vector<Token> tokens;
    while (!isAtEnd())
    {
        skipWhitespace();
        if (isAtEnd())
            break;
        size_t start = current_;
        int startColumn = column_;

        char c = advance();
        if (std::isalpha(c) || c == '_')
        {
            current_--;
            column_--;
            tokens.emplace_back(identifier());
        }
        else if (std::isdigit(c))
        {
            current_--;
            column_--;
            tokens.emplace_back(number());
        }
        else if (c == '"')
        {
            tokens.emplace_back(stringLiteral());
        }
        else
        {
            TString lexeme(std::string(1, c));
            tokens.emplace_back(makeToken(TokenType::Unknown, lexeme));
        }
    }
    tokens.emplace_back(Token{TokenType::EndOfFile, TString(""), line_, column_});
    return tokens;
}

char Lexer::peek() const
{
    if (isAtEnd())
        return '\0';
    return source_[current_];
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

Token Lexer::makeToken(TokenType type, const TString &lexeme)
{
    return Token{type, lexeme, line_, column_};
}

Token Lexer::identifier()
{
    size_t start = current_ - 1;
    while (std::isalnum(peek()) || peek() == '_')
    {
        advance();
    }
    size_t end = current_;
    std::string lex = source_.substr(start, end - start);
    TString ts(lex);
    if (keywords_.find(ts) != keywords_.end())
    {
        return makeToken(TokenType::Keyword, ts);
    }
    return makeToken(TokenType::Identifier, ts);
}

Token Lexer::number()
{
    size_t start = current_ - 1;
    while (std::isdigit(peek()))
    {
        advance();
    }
    size_t end = current_;
    std::string lex = source_.substr(start, end - start);
    return makeToken(TokenType::Number, TString(lex));
}

Token Lexer::stringLiteral()
{
    size_t start = current_;
    while (peek() != '"' && !isAtEnd())
    {
        if (peek() == '\n')
        {
            line_++;
            column_ = 1;
        }
        advance();
    }

    if (isAtEnd())
    {
        return makeToken(TokenType::Unknown, TString("Unterminated string"));
    }

    advance();
    size_t end = current_ - 1;
    std::string lex = source_.substr(start, end - start);
    return makeToken(TokenType::String, TString(lex));
}
