#include "FirstLayer.hpp"
#include <cctype>

std::vector<Token> FirstLayer::processChunk(const SourceChunk &chunk)
{
    std::vector<Token> tokens;
    const std::string &text = chunk.content;
    size_t start = 0;
    size_t pos = 0;
    while (pos <= text.size())
    {
        if (pos == text.size() || std::isspace((unsigned char)text[pos]))
        {
            if (pos > start)
            {
                std::string sub = text.substr(start, pos - start);
                tokens.push_back(createToken(sub));
            }
            start = pos + 1;
        }
        pos++;
    }
    return tokens;
}

Token FirstLayer::createToken(const std::string &sub)
{
    bool allDigits = true;
    bool allAlpha = true;
    for (char c : sub)
    {
        if (!std::isdigit((unsigned char)c))
        {
            allDigits = false;
        }
        if (!std::isalpha((unsigned char)c))
        {
            allAlpha = false;
        }
    }
    if (allDigits)
    {
        return {TokenType::Number, sub};
    }
    if (allAlpha)
    {
        return {TokenType::Identifier, sub};
    }
    return {TokenType::Unknown, sub};
}
