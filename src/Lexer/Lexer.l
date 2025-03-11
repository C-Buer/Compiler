%option noyywrap
%option unicode
%{
#include <string>
#include <vector>
#include <unordered_map>
#include "Token.hpp"

static int line = 1;
static int col = 1;
static std::vector<Token> tokens;

static void addToken(TokenType type, const std::string &lexeme) {
    tokens.push_back(Token(type, lexeme, line, col));
    col += (int)lexeme.size();
}
%}

%%
[\r\n]+                { line += yyleng; col = 1; }
[ \t]+                 { col += yyleng; }
"("                    { addToken(TokenType::LeftParen, yytext); }
")"                    { addToken(TokenType::RightParen, yytext); }
"{"                    { addToken(TokenType::LeftBrace, yytext); }
"}"                    { addToken(TokenType::RightBrace, yytext); }
"["                    { addToken(TokenType::LeftBracket, yytext); }
"]"                    { addToken(TokenType::RightBracket, yytext); }
","                    { addToken(TokenType::Comma, yytext); }
"."                    { addToken(TokenType::Dot, yytext); }
";"                    { addToken(TokenType::Semicolon, yytext); }
":"                    { addToken(TokenType::Colon, yytext); }
"=="                   { addToken(TokenType::DoubleEquals, yytext); }
"!="                   { addToken(TokenType::NotEquals, yytext); }
"<="                   { addToken(TokenType::LessEquals, yytext); }
">="                   { addToken(TokenType::GreaterEquals, yytext); }
"&&"                   { addToken(TokenType::DoubleAmpersand, yytext); }
"||"                   { addToken(TokenType::DoublePipe, yytext); }
"->"                   { addToken(TokenType::Arrow, yytext); }
"::"                   { addToken(TokenType::Scope, yytext); }
"++"                   { addToken(TokenType::Increment, yytext); }
"--"                   { addToken(TokenType::Decrement, yytext); }
"<<"                   { addToken(TokenType::LShift, yytext); }
">>"                   { addToken(TokenType::RShift, yytext); }
"..."                  { addToken(TokenType::Ellipsis, yytext); }
"+"                    { addToken(TokenType::Plus, yytext); }
"-"                    { addToken(TokenType::Minus, yytext); }
"*"                    { addToken(TokenType::Star, yytext); }
"/"                    { addToken(TokenType::Slash, yytext); }
"%"                    { addToken(TokenType::Percent, yytext); }
"&"                    { addToken(TokenType::Ampersand, yytext); }
"|"                    { addToken(TokenType::Pipe, yytext); }
"^"                    { addToken(TokenType::Caret, yytext); }
"!"                    { addToken(TokenType::Exclamation, yytext); }
"~"                    { addToken(TokenType::Tilde, yytext); }
"?"                    { addToken(TokenType::Question, yytext); }
"<"                    { addToken(TokenType::Less, yytext); }
">"                    { addToken(TokenType::Greater, yytext); }
"="                    { addToken(TokenType::Equals, yytext); }
\"([^\"\\]|\\.)*\"      { addToken(TokenType::StringLiteral, yytext); }
\'([^\'\\]|\\.)*\'      { addToken(TokenType::CharLiteral, yytext); }
[0-9]+(\.[0-9]+)        { addToken(TokenType::FloatingLiteral, yytext); }
[0-9]+                  { addToken(TokenType::IntegerLiteral, yytext); }
[\p{L}_][\p{L}\p{M}\p{Nd}\p{Pc}\p{Cf}]* {
    static std::unordered_map<std::string, TokenType> keywords = {
        {"auto", TokenType::Auto},
        {"struct", TokenType::Struct},
        {"class", TokenType::Class},
        {"union", TokenType::Union},
        {"enum", TokenType::Enum},
        {"namespace", TokenType::Namespace},
        {"import", TokenType::Import},
        {"as", TokenType::As},
        {"if", TokenType::If},
        {"else", TokenType::Else},
        {"for", TokenType::For},
        {"in", TokenType::In},
        {"while", TokenType::While},
        {"return", TokenType::Return},
        {"label", TokenType::Label},
        {"goto", TokenType::Goto},
        {"case", TokenType::Case},
        {"match", TokenType::Match},
        {"true", TokenType::True},
        {"false", TokenType::False},
        {"public", TokenType::Public},
        {"private", TokenType::Private},
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
        {"uint8", TokenType::UInt8},
        {"ptr", TokenType::Ptr}
    };
    std::string text = yytext;
    auto it = keywords.find(text);
    if (it != keywords.end()) {
        addToken(it->second, text);
    } else {
        addToken(TokenType::Identifier, text);
    }
}
.                      { addToken(TokenType::Invalid, yytext); }
%%

int main() {
    yylex();
    for (auto &t : tokens) {
        std::cout << (int)t.type << " " << t.lexeme << " " << t.line << " " << t.column << std::endl;
    }
    return 0;
}
