#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

enum class TokenType
{
    // Single-character tokens
    LeftParen = 0,    // (
    RightParen = 1,   // )
    LeftBrace = 2,    // {
    RightBrace = 3,   // }
    LeftBracket = 4,  // [
    RightBracket = 5, // ]
    Comma = 6,        // ,
    Dot = 7,          // .
    Semicolon = 8,    // ;
    Colon = 9,        // :
    Plus = 10,        // +
    Minus = 11,       // -
    Star = 12,        // *
    Slash = 13,       // /
    Percent = 14,     // %
    Ampersand = 15,   // &
    Pipe = 16,        // |
    Caret = 17,       // ^
    Exclamation = 18, // !
    Tilde = 19,       // ~
    Question = 20,    // ?
    Less = 21,        // <
    Greater = 22,     // >
    Equals = 23,      // =

    // One or two character tokens
    DoubleEquals = 24,    // ==
    NotEquals = 25,       // !=
    LessEquals = 26,      // <=
    GreaterEquals = 27,   // >=
    DoubleAmpersand = 28, // &&
    DoublePipe = 29,      // ||
    Arrow = 30,           // ->

    // Literals
    Identifier = 31,
    IntegerLiteral = 32,
    FloatingLiteral = 33,
    StringLiteral = 34,
    CharLiteral = 35,
    BooleanLiteral = 36,

    // Keywords
    Auto = 37,
    Struct = 38,
    Class = 39,
    Union = 40,
    Enum = 41,
    If = 42,
    Else = 43,
    For = 44,
    While = 45,
    Return = 46,
    Match = 47,
    Import = 48,
    Namespace = 49,
    True = 50,
    False = 51,

    // Primitive Types
    Int32 = 52,
    Float = 53,
    Double = 54,
    Char = 55,
    Bool = 56,
    Void = 57,
    Int64 = 58,
    Int16 = 59,
    Signed = 60,
    Unsigned = 61,
    WChar_T = 62,

    // End of file
    EndOfFile = 63,

    // Invalid token
    Invalid = 64
};

struct Token
{
    TokenType type;
    std::string lexeme;
    int line;
    int column;

    Token(TokenType type = TokenType::Invalid, const std::string &lexeme = "", int line = 0, int column = 0)
        : type(type), lexeme(lexeme), line(line), column(column)
    {
    }
};

#endif // TOKEN_HPP
