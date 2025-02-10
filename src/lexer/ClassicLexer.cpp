#include "ClassicLexer.hpp"
#include <cctype>

std::vector<Token> ClassicLexer::processFullSource(const std::string &source)
{
    std::vector<Token> tokens;
    size_t start = 0;
    size_t pos = 0;
    while (pos <= source.size())
    {
        if (pos == source.size() || std::isspace((unsigned char)source[pos]))
        {
            if (pos > start)
            {
                std::string sub = source.substr(start, pos - start);
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
                TokenType t = TokenType::Unknown;
                if (allDigits)
                {
                    t = TokenType::Number;
                }
                else if (allAlpha)
                {
                    t = TokenType::Identifier;
                }
                tokens.push_back({t, sub});
            }
            start = pos + 1;
        }
        pos++;
    }
    for (auto &tk : tokens)
    {
        if (tk.type == TokenType::Identifier)
        {
            if (tk.text == "if" || tk.text == "for")
            {
                tk.type = TokenType::Keyword;
            }
        }
    }
    return tokens;
}
