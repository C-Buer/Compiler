#include "FirstLayer.hpp"
#include <string_view>
#include <vector>

static inline bool is_whitespace(char c)
{
    return c == ' ' || c == '\n' || c == '\t' || c == '\r';
}
std::vector<Token> FirstLayer::processChunk(const SourceChunk &chunk)
{
    std::string_view sv(chunk.content);
    std::vector<Token> tokens;
    tokens.reserve(sv.size() / 4);
    size_t i = 0;
    size_t n = sv.size();
    while (i < n)
    {
        while (i < n && is_whitespace(sv[i]))
        {
            i++;
        }
        if (i >= n)
            break;
        size_t start = i;
        while (i < n && !is_whitespace(sv[i]))
        {
            i++;
        }
        tokens.push_back(Token{TokenType::Identifier, std::string(sv.substr(start, i - start))});
    }
    return tokens;
}
std::vector<Token> FirstLayer::processTokens(const std::vector<Token> &tokens)
{
    return tokens;
}
