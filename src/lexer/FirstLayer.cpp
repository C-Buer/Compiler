#include "FirstLayer.hpp"

std::vector<Token> FirstLayer::processChunk(const SourceChunk &chunk)
{
    std::vector<std::string> rawTokens;
    rawTokens.reserve(chunk.content.size() / 5 + 1);
    splitIntoTokens(chunk.content, rawTokens);
    std::vector<Token> result;
    result.reserve(rawTokens.size());
    classifyTokens(rawTokens, result);
    return result;
}

void FirstLayer::splitIntoTokens(const std::string &text, std::vector<std::string> &rawTokens)
{
    size_t length = text.size();
    size_t start = 0;
    for (size_t i = 0; i <= length; i++)
    {
        bool boundary = (i == length) || (unsigned char)text[i] <= ' ';
        if (!boundary)
        {
            continue;
        }
        if (i > start)
        {
            rawTokens.push_back(text.substr(start, i - start));
        }
        start = i + 1;
    }
}

void FirstLayer::classifyTokens(const std::vector<std::string> &rawTokens, std::vector<Token> &outTokens)
{
    for (auto &sub : rawTokens)
    {
        bool allDigits = true;
        bool allAlpha = true;
        for (char c : sub)
        {
            bool isDigit = (c >= '0' && c <= '9');
            bool isAlpha = ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
            allDigits = allDigits && isDigit;
            allAlpha = allAlpha && isAlpha;
        }
        Token tk;
        tk.hash = 0;
        if (allDigits)
        {
            tk.type = TokenType::Number;
        }
        else if (allAlpha)
        {
            tk.type = TokenType::Identifier;
            tk.hash = fnv1aHash(sub);
        }
        else
        {
            tk.type = TokenType::Unknown;
        }
        tk.text = sub;
        outTokens.push_back(std::move(tk));
    }
}

std::uint32_t FirstLayer::fnv1aHash(const std::string &str)
{
    std::uint32_t hashVal = 2166136261u;
    for (char c : str)
    {
        hashVal ^= (std::uint8_t)c;
        hashVal *= 16777619u;
    }
    return hashVal;
}
