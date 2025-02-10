#include "SecondLayer.hpp"

std::vector<Token> SecondLayer::processTokens(const std::vector<Token> &tokens)
{
    std::vector<Token> refined;
    refined.reserve(tokens.size());
    for (auto &tk : tokens)
    {
        Token newTk = tk;
        if (newTk.type == TokenType::Identifier)
        {
            if (newTk.text == "if" || newTk.text == "for")
            {
                newTk.type = TokenType::Keyword;
            }
        }
        refined.push_back(newTk);
    }
    return refined;
}
