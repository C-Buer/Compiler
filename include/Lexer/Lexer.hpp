#ifndef LEXER_HPP
#define LEXER_HPP

#include "Token.hpp"
#include <string>
#include <unordered_map>
#include <vector>

class Lexer
{
  public:
    Lexer(const std::string &source);
    std::vector<Token> tokenize();

  private:
    std::string source;
    size_t current = 0;
    int line = 1;
    int column = 1;
    std::vector<Token> tokens;

    std::unordered_map<std::string, TokenType> keywords = {{"auto", TokenType::Auto},
                                                           {"struct", TokenType::Struct},
                                                           {"class", TokenType::Class},
                                                           {"union", TokenType::Union},
                                                           {"enum", TokenType::Enum},
                                                           {"if", TokenType::If},
                                                           {"else", TokenType::Else},
                                                           {"for", TokenType::For},
                                                           {"while", TokenType::While},
                                                           {"return", TokenType::Return},
                                                           {"match", TokenType::Match},
                                                           {"import", TokenType::Import},
                                                           {"namespace", TokenType::Namespace},
                                                           {"true", TokenType::True},
                                                           {"false", TokenType::False},
                                                           // Primitive Types
                                                           {"int", TokenType::Int},
                                                           {"float", TokenType::Float},
                                                           {"double", TokenType::Double},
                                                           {"char", TokenType::Char},
                                                           {"bool", TokenType::Bool},
                                                           {"void", TokenType::Void},
                                                           {"long", TokenType::Long},
                                                           {"short", TokenType::Short},
                                                           {"signed", TokenType::Signed},
                                                           {"unsigned", TokenType::Unsigned}};

    char peek();
    char peekNext();
    char advance();
    bool match(char expected);
    void addToken(TokenType type, const std::string &lexeme);
    void skipWhitespace();
    void skipComment();
    Token identifier();
    Token number();
    Token string();
    Token character();
    Token boolean();
};

#endif // LEXER_HPP
