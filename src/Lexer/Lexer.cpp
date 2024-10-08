#include "Lexer/Lexer.hpp"

#include <cctype>

Token::Token(TokenType type, const TString &value) : type(type), value(value)
{
}

Lexer::Lexer(const TString &source) : source(source), position(0)
{
    // Default keywords and operators
    keywords = {"int8",   "int16", "int32", "int64", "uint8", "uint16", "uint32", "uint64", "float",
                "double", "if",    "else",  "for",   "while", "return", "void",   "class",  "struct"};
    operators = {"+", "-", "*", "/", "=", "==", "!=", "<", "<=", ">", ">="};
}

char Lexer::current_char() const
{
    if (position < source.size())
    {
        return source[position];
    }
    return '\0';
}

void Lexer::advance()
{
    if (position < source.size())
    {
        ++position;
    }
}

void Lexer::skip_whitespace()
{
    while (std::isspace(current_char()))
    {
        advance();
    }
}

bool Lexer::is_keyword(const TString &str) const
{
    return keywords.find(str) != keywords.end();
}

void Lexer::add_keyword(const TString &keyword)
{
    keywords.insert(keyword);
}

void Lexer::add_operator(const TString &op)
{
    operators.insert(op);
}

Token Lexer::next_token()
{
    skip_whitespace();

    char ch = current_char();
    if (ch == '\0')
    {
        return Token(TokenType::EndOfFile, "");
    }

    if (std::isalpha(ch) || ch == '_')
    {
        size_t start = position;
        while (std::isalnum(current_char()) || current_char() == '_')
        {
            advance();
        }
        TString identifier = source.substr(start, position - start);
        if (is_keyword(identifier))
        {
            return Token(TokenType::Keyword, identifier);
        }
        return Token(TokenType::Identifier, identifier);
    }

    if (std::isdigit(ch))
    {
        size_t start = position;
        while (std::isdigit(current_char()))
        {
            advance();
        }
        return Token(TokenType::Number, source.substr(start, position - start));
    }

    if (ch == '"')
    {
        size_t start = position;
        advance();
        while (current_char() != '"' && current_char() != '\0')
        {
            advance();
        }
        if (current_char() == '"')
        {
            advance();
        }
        return Token(TokenType::StringLiteral, source.substr(start, position - start));
    }

    if (std::ispunct(ch))
    {
        // Handle operators and symbols
        for (const auto &op : operators)
        {
            if (source.substr(position, op.size()) == op)
            {
                position += op.size();
                return Token(TokenType::Operator, op);
            }
        }
        advance();
        return Token(TokenType::Symbol, TString(ch));
    }

    advance();
    return Token(TokenType::Symbol, TString(ch));
}