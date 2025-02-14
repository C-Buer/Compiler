#include "SecondLayer.hpp"
#include <vector>

std::vector<Token> SecondLayer::processChunk(const SourceChunk &chunk)
{
    return std::vector<Token>{};
}
std::vector<Token> SecondLayer::processTokens(const std::vector<Token> &tokens)
{
    std::vector<Token> refined;
    refined.reserve(tokens.size());
    for (const auto &tk : tokens)
    {
        Token newTk = tk;
        if (newTk.text == "if" || newTk.text == "for")
        {
            newTk.type = TokenType::Keyword;
        }
        refined.push_back(newTk);
    }
    return refined;
}
