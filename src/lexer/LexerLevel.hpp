#ifndef LEXERLEVEL_HPP
#define LEXERLEVEL_HPP

#include <cstdint>
#include <string>
#include <vector>

enum class TokenType
{
    Identifier,
    Number,
    Keyword,
    Operator,
    Unknown
};

struct Token
{
    TokenType type;
    std::string text;
    std::uint32_t hash;
};

struct SourceChunk
{
    std::string content;
    bool isDirty;
    std::vector<Token> tokens;
};

class LexerLevel
{
  public:
    virtual ~LexerLevel() = default;
    virtual std::vector<Token> processChunk(const SourceChunk &chunk);
    virtual std::vector<Token> processTokens(const std::vector<Token> &tokens);
};

#endif
