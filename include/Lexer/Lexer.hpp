#ifndef LEXER_HPP
#define LEXER_HPP

#include "Token.hpp"
#include <iostream>
#include <list>
#include <locale>
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
    std::list<Token> tokens;

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
                                                           {"label", TokenType::Label},
                                                           {"case", TokenType::Case},
                                                           {"goto", TokenType::Goto},
                                                           {"match", TokenType::Match},
                                                           {"import", TokenType::Import},
                                                           {"namespace", TokenType::Namespace},
                                                           {"true", TokenType::True},
                                                           {"false", TokenType::False},
                                                           // Primitive Types
                                                           {"string", TokenType::String},
                                                           {"char", TokenType::Char},
                                                           {"bool", TokenType::Bool},
                                                           {"void", TokenType::Void},
                                                           {"float", TokenType::Float},
                                                           {"double", TokenType::Double},
                                                           {"int64", TokenType::Int64},
                                                           {"int32", TokenType::Int32},
                                                           {"int16", TokenType::Int16},
                                                           {"int8", TokenType::Int8},
                                                           {"uint64", TokenType::UInt64},
                                                           {"uint32", TokenType::UInt32},
                                                           {"uint16", TokenType::UInt16},
                                                           {"uint8", TokenType::UInt8}};

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
