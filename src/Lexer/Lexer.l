%option noyywrap
%option unicode
%option c++
%option bison-locations

%{
#include <string>
#include <vector>
#include <unordered_map>
#include "Token.hpp"
%}

%class{
    std::vector<Token> tokens;
    void addToken(TokenType t, const std::string &lexeme, int ln, int col)
    {
        tokens.emplace_back(t, lexeme, ln, col);
    }
};

%%

"("             { addToken(TokenType::LeftParen, yytext, yylloc->last_line, yylloc->last_column); }
")"             { addToken(TokenType::RightParen, yytext, yylloc->last_line, yylloc->last_column); }
"{"             { addToken(TokenType::LeftBrace, yytext, yylloc->last_line, yylloc->last_column); }
"}"             { addToken(TokenType::RightBrace, yytext, yylloc->last_line, yylloc->last_column); }
"["             { addToken(TokenType::LeftBracket, yytext, yylloc->last_line, yylloc->last_column); }
"]"             { addToken(TokenType::RightBracket, yytext, yylloc->last_line, yylloc->last_column); }
","             { addToken(TokenType::Comma, yytext, yylloc->last_line, yylloc->last_column); }
"."             { addToken(TokenType::Dot, yytext, yylloc->last_line, yylloc->last_column); }
";"             { addToken(TokenType::Semicolon, yytext, yylloc->last_line, yylloc->last_column); }
":"             { addToken(TokenType::Colon, yytext, yylloc->last_line, yylloc->last_column); }
"+"             { addToken(TokenType::Plus, yytext, yylloc->last_line, yylloc->last_column); }
"-"             { addToken(TokenType::Minus, yytext, yylloc->last_line, yylloc->last_column); }
"*"             { addToken(TokenType::Star, yytext, yylloc->last_line, yylloc->last_column); }
"/"             { addToken(TokenType::Slash, yytext, yylloc->last_line, yylloc->last_column); }
"%"             { addToken(TokenType::Percent, yytext, yylloc->last_line, yylloc->last_column); }
"&"             { addToken(TokenType::Ampersand, yytext, yylloc->last_line, yylloc->last_column); }
"|"             { addToken(TokenType::Pipe, yytext, yylloc->last_line, yylloc->last_column); }
"^"             { addToken(TokenType::Caret, yytext, yylloc->last_line, yylloc->last_column); }
"!"             { addToken(TokenType::Exclamation, yytext, yylloc->last_line, yylloc->last_column); }
"~"             { addToken(TokenType::Tilde, yytext, yylloc->last_line, yylloc->last_column); }
"?"             { addToken(TokenType::Question, yytext, yylloc->last_line, yylloc->last_column); }
"<"             { addToken(TokenType::Less, yytext, yylloc->last_line, yylloc->last_column); }
">"             { addToken(TokenType::Greater, yytext, yylloc->last_line, yylloc->last_column); }
"="             { addToken(TokenType::Equals, yytext, yylloc->last_line, yylloc->last_column); }
"=="            { addToken(TokenType::DoubleEquals, yytext, yylloc->last_line, yylloc->last_column); }
"!="            { addToken(TokenType::NotEquals, yytext, yylloc->last_line, yylloc->last_column); }
"<="            { addToken(TokenType::LessEquals, yytext, yylloc->last_line, yylloc->last_column); }
">="            { addToken(TokenType::GreaterEquals, yytext, yylloc->last_line, yylloc->last_column); }
"&&"            { addToken(TokenType::DoubleAmpersand, yytext, yylloc->last_line, yylloc->last_column); }
"||"            { addToken(TokenType::DoublePipe, yytext, yylloc->last_line, yylloc->last_column); }
"->"            { addToken(TokenType::Arrow, yytext, yylloc->last_line, yylloc->last_column); }
"::"            { addToken(TokenType::Scope, yytext, yylloc->last_line, yylloc->last_column); }
"++"            { addToken(TokenType::Increment, yytext, yylloc->last_line, yylloc->last_column); }
"--"            { addToken(TokenType::Decrement, yytext, yylloc->last_line, yylloc->last_column); }
"<<"            { addToken(TokenType::LShift, yytext, yylloc->last_line, yylloc->last_column); }
">>"            { addToken(TokenType::RShift, yytext, yylloc->last_line, yylloc->last_column); }
[0-9]+          { addToken(TokenType::IntegerLiteral, yytext, yylloc->last_line, yylloc->last_column); }
[[:alpha:]_][[:alnum:]_]* {
    static std::unordered_map<std::string, TokenType> keywords = {
        {"auto",TokenType::Auto},
        {"struct",TokenType::Struct},
        {"class",TokenType::Class},
        {"union",TokenType::Union},
        {"enum",TokenType::Enum},
        {"namespace",TokenType::Namespace},
        {"import",TokenType::Import},
        {"as",TokenType::As},
        {"if",TokenType::If},
        {"else",TokenType::Else},
        {"for",TokenType::For},
        {"in",TokenType::In},
        {"while",TokenType::While},
        {"return",TokenType::Return},
        {"label",TokenType::Label},
        {"goto",TokenType::Goto},
        {"case",TokenType::Case},
        {"match",TokenType::Match},
        {"true",TokenType::True},
        {"false",TokenType::False},
        {"public",TokenType::Public},
        {"private",TokenType::Private},
        {"string",TokenType::String},
        {"char",TokenType::Char},
        {"bool",TokenType::Bool},
        {"void",TokenType::Void},
        {"float",TokenType::Float},
        {"double",TokenType::Double},
        {"int64",TokenType::Int64},
        {"int32",TokenType::Int32},
        {"int16",TokenType::Int16},
        {"int8",TokenType::Int8},
        {"uint64",TokenType::UInt64},
        {"uint32",TokenType::UInt32},
        {"uint16",TokenType::UInt16},
        {"uint8",TokenType::UInt8},
        {"ptr",TokenType::Ptr}
    };
    std::string text = yytext;
    auto it = keywords.find(text);
    if (it != keywords.end())
    {
        addToken(it->second, text, yylloc->last_line, yylloc->last_column);
    } else
    {
        addToken(TokenType::Identifier, text, yylloc->last_line, yylloc->last_column);
    }
}
. { addToken(TokenType::Invalid, yytext, yylloc->last_line, yylloc->last_column); }

%%  
