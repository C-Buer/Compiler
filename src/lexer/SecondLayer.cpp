#include "SecondLayer.hpp"

SecondLayer::SecondLayer()
{
    keywords.insert("if");
    keywords.insert("for");
}

void SecondLayer::addKeyword(const std::string &kw)
{
    keywords.insert(kw);
}

std::vector<Token> SecondLayer::processTokens(const std::vector<Token> &tokens)
{
    std::vector<Token> refined;
    refined.reserve(tokens.size());
    for (auto &tk : tokens)
    {
        Token newTk = tk;
        if (newTk.type == TokenType::Identifier)
        {
            if (keywords.find(newTk.text) != keywords.end())
            {
                newTk.type = TokenType::Keyword;
            }
        }
        refined.push_back(std::move(newTk));
    }
    return refined;
}
