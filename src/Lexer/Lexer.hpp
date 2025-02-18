#ifndef LEXER_HPP
#define LEXER_HPP

#include <cstddef>
#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>


enum class TokenType
{
    Identifier,
    Keyword,
    Number,
    String,
    Operator,
    Separator,
    EndOfFile,
    Unknown
};

struct Token
{
    TokenType type;
    std::string_view lexeme;
    std::size_t line;
    std::size_t column;
};

class Lexer
{
  public:
    Lexer(std::string_view input);
    std::vector<Token> tokenize();
    static std::vector<Token> tokenizeMultiThread(std::string_view input, std::size_t chunkSize);
    static std::vector<Token> incrementalTokenize(std::string_view chunk, std::size_t startLine,
                                                  std::size_t startColumn);
    static std::unordered_set<std::string> s_keywords;
    static void addKeyword(const std::string &keyword);

  private:
    std::string_view m_input;
    std::size_t m_pos;
    std::size_t m_line;
    std::size_t m_column;
    char current() const;
    void advance();
    bool isAtEnd() const;
    Token scanToken();
    Token finishToken(TokenType type, std::string_view lexeme, std::size_t startLine, std::size_t startColumn);
    std::vector<Token> tokenizeLevel1(std::string_view chunk);
    std::vector<Token> tokenizeLevel2(const std::vector<Token> &tokens);
};

#endif
