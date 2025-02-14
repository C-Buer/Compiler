#include "SecondLayer.hpp"
#include <unordered_map>

static std::unordered_map<std::uint32_t, KnownKeyword> gKeywordMap = {
    {3984772369u, KnownKeyword::IF}, {2166136257u, KnownKeyword::FOR}, {3294736446u, KnownKeyword::WHILE}};

KnownKeyword checkKeyword(std::uint32_t hash, const std::string &text)
{
    auto it = gKeywordMap.find(hash);
    if (it != gKeywordMap.end())
    {
        KnownKeyword kw = it->second;
        if (kw == KnownKeyword::IF && text == "if")
            return KnownKeyword::IF;
        if (kw == KnownKeyword::FOR && text == "for")
            return KnownKeyword::FOR;
        if (kw == KnownKeyword::WHILE && text == "while")
            return KnownKeyword::WHILE;
    }
    return KnownKeyword::NONE;
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
            KnownKeyword k = checkKeyword(newTk.hash, newTk.text);
            if (k != KnownKeyword::NONE)
            {
                newTk.type = TokenType::Keyword;
            }
        }
        refined.push_back(std::move(newTk));
    }
    return refined;
}
