#include "Lexer.hpp"
#include <algorithm>
#include <cctype>
#include <future>


std::unordered_set<std::string> Lexer::s_keywords;

Lexer::Lexer(std::string_view input) : m_input(input), m_pos(0), m_line(1), m_column(1)
{
}

void Lexer::addKeyword(const std::string &keyword)
{
    s_keywords.insert(keyword);
}

char Lexer::current() const
{
    return m_input[m_pos];
}

void Lexer::advance()
{
    if (current() == '\n')
    {
        m_line++;
        m_column = 1;
    }
    else
    {
        m_column++;
    }
    m_pos++;
}

bool Lexer::isAtEnd() const
{
    return m_pos >= m_input.size();
}

Token Lexer::finishToken(TokenType type, std::string_view lexeme, std::size_t startLine, std::size_t startColumn)
{
    return {type, lexeme, startLine, startColumn};
}

Token Lexer::scanToken()
{
    while (!isAtEnd() && std::isspace(current()))
    {
        advance();
    }
    if (isAtEnd())
    {
        return finishToken(TokenType::EndOfFile, m_input.substr(m_pos), m_line, m_column);
    }
    std::size_t startPos = m_pos;
    std::size_t startLine = m_line;
    std::size_t startColumn = m_column;
    char ch = current();
    if (std::isalpha(ch) || ch == '_')
    {
        while (!isAtEnd() && (std::isalnum(current()) || current() == '_'))
        {
            advance();
        }
        return finishToken(TokenType::Identifier, m_input.substr(startPos, m_pos - startPos), startLine, startColumn);
    }
    if (std::isdigit(ch))
    {
        while (!isAtEnd() && std::isdigit(current()))
        {
            advance();
        }
        return finishToken(TokenType::Number, m_input.substr(startPos, m_pos - startPos), startLine, startColumn);
    }
    if (ch == '"')
    {
        advance();
        while (!isAtEnd() && current() != '"')
        {
            advance();
        }
        if (!isAtEnd())
        {
            advance();
        }
        return finishToken(TokenType::String, m_input.substr(startPos, m_pos - startPos), startLine, startColumn);
    }
    advance();
    return finishToken(TokenType::Operator, m_input.substr(startPos, m_pos - startPos), startLine, startColumn);
}

std::vector<Token> Lexer::tokenizeLevel1(std::string_view chunk)
{
    std::vector<Token> tokens;
    Lexer lexer(chunk);
    while (!lexer.isAtEnd())
    {
        tokens.push_back(lexer.scanToken());
    }
    return tokens;
}

std::vector<Token> Lexer::tokenizeLevel2(const std::vector<Token> &tokens)
{
    std::vector<Token> refined = tokens;
    for (auto &token : refined)
    {
        if (token.type == TokenType::Identifier)
        {
            if (s_keywords.find(std::string(token.lexeme)) != s_keywords.end())
            {
                token.type = TokenType::Keyword;
            }
        }
    }
    return refined;
}

std::vector<Token> Lexer::tokenize()
{
    std::vector<Token> tokens;
    while (!isAtEnd())
    {
        tokens.push_back(scanToken());
    }
    return tokenizeLevel2(tokens);
}

std::vector<Token> Lexer::tokenizeMultiThread(std::string_view input, std::size_t chunkSize)
{
    std::vector<Token> tokens;
    std::vector<std::future<std::vector<Token>>> futures;
    std::size_t length = input.size();
    std::size_t start = 0;
    while (start < length)
    {
        std::size_t size = std::min(chunkSize, length - start);
        std::string_view chunk = input.substr(start, size);
        futures.push_back(std::async(std::launch::async, [chunk]() {
            Lexer lexer(chunk);
            std::vector<Token> t;
            while (!lexer.isAtEnd())
            {
                t.push_back(lexer.scanToken());
            }
            return lexer.tokenizeLevel2(t);
        }));
        start += size;
    }
    for (auto &f : futures)
    {
        auto part = f.get();
        tokens.insert(tokens.end(), part.begin(), part.end());
    }
    std::sort(tokens.begin(), tokens.end(), [](const Token &a, const Token &b) {
        if (a.line == b.line)
        {
            return a.column < b.column;
        }
        return a.line < b.line;
    });
    return tokens;
}

std::vector<Token> Lexer::incrementalTokenize(std::string_view chunk, std::size_t startLine, std::size_t startColumn)
{
    Lexer lexer(chunk);
    auto tokens = lexer.tokenizeLevel1(chunk);
    for (auto &token : tokens)
    {
        token.line += (startLine - 1);
        if (token.line == startLine)
        {
            token.column += (startColumn - 1);
        }
    }
    return lexer.tokenizeLevel2(tokens);
}
