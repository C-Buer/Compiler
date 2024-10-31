#include "Lexer\Lexer.hpp"
#include <algorithm>
#include <cctype>

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

std::vector<Token> Lexer::tokenize()
{
    std::vector<Token> tokens;
    sortOperators();
    tokens.reserve(source_.size() / 2);

    while (!isAtEnd())
    {
        skipWhitespace();
        if (isAtEnd())
            break;

        size_t start = current_;
        int startColumn = column_;

        bool matchedOperator = false;
        for (const auto &op : operators_)
        {
            size_t opLen = op.size();
            if (current_ + opLen <= source_.size() && source_.substr(current_, opLen) == op)
            {
                for (size_t i = 0; i < opLen; ++i)
                    advance();
                tokens.emplace_back(Token{TokenType::Operator, op, line_, startColumn});
                matchedOperator = true;
                break;
            }
        }
        if (matchedOperator)
        {
            continue;
        }

        char c = peek();
        if (std::isalpha(c) || c == '_')
        {
            tokens.emplace_back(identifier());
        }
        else if (std::isdigit(c))
        {
            tokens.emplace_back(number());
        }
        else if (c == '"')
        {
            tokens.emplace_back(stringLiteral());
        }
        else
        {
            advance();
            TString lexeme(c);
            tokens.emplace_back(makeToken(TokenType::Unknown, lexeme, line_, column_ - 1));
        }
    }
    tokens.emplace_back(Token{TokenType::EndOfFile, TString(""), line_, column_});
    return tokens;
}

Token Lexer::identifier()
{
    size_t start = current_;
    int tokenLine = line_;
    int tokenColumn = column_;

    while (std::isalnum(peek()) || peek() == '_')
    {
        advance();
    }
    size_t end = current_;
    TString lex = source_.substr(start, end - start);
    TString ts(lex);
    if (keywords_.find(ts) != keywords_.end())
    {
        return makeToken(TokenType::Keyword, ts, tokenLine, tokenColumn);
    }
    return makeToken(TokenType::Identifier, ts, tokenLine, tokenColumn);
}

Token Lexer::number()
{
    size_t start = current_;
    int tokenLine = line_;
    int tokenColumn = column_;

    while (std::isdigit(peek()))
    {
        advance();
    }

    if (peek() == '.' && std::isdigit(peekNext()))
    {
        advance();
        while (std::isdigit(peek()))
        {
            advance();
        }
    }
    size_t end = current_;
    TString lex = source_.substr(start, end - start);
    return makeToken(TokenType::Number, lex, tokenLine, tokenColumn);
}

Token Lexer::stringLiteral()
{
    int tokenLine = line_;
    int tokenColumn = column_;
    advance();

    size_t start = current_;
    std::string value;
    while (peek() != '"' && !isAtEnd())
    {
        if (peek() == '\\')
        {
            advance();
            char escaped = peek();
            switch (escaped)
            {
            case 'n':
                value += '\n';
                break;
            case 't':
                value += '\t';
                break;
            case '"':
                value += '"';
                break;
            case '\\':
                value += '\\';
                break;
            default:
                value += escaped;
                break;
            }
            advance();
        }
        else
        {
            if (peek() == '\n')
            {
                line_++;
                column_ = 1;
            }
            value += peek();
            advance();
        }
    }

    if (isAtEnd())
    {
        return makeToken(TokenType::Unknown, TString("Unterminated string"), tokenLine, tokenColumn);
    }

    advance();
    return makeToken(TokenType::String, TString(value), tokenLine, tokenColumn);
}