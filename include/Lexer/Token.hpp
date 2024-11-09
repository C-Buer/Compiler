#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

enum class TokenType
{
    // Single-character tokens
    LeftParen,    // (
    RightParen,   // )
    LeftBrace,    // {
    RightBrace,   // }
    LeftBracket,  // [
    RightBracket, // ]
    Comma,        // ,
    Dot,          // .
    Semicolon,    // ;
    Colon,        // :
    Plus,         // +
    Minus,        // -
    Star,         // *
    Slash,        // /
    Percent,      // %
    Ampersand,    // &
    Pipe,         // |
    Caret,        // ^
    Exclamation,  // !
    Tilde,        // ~
    Question,     // ?
    Less,         // <
    Greater,      // >
    Equals,       // =

    // Double-character tokens
    DoubleEquals,    // ==
    NotEquals,       // !=
    LessEquals,      // <=
    GreaterEquals,   // >=
    DoubleAmpersand, // &&
    DoublePipe,      // ||
    Arrow,           // ->
    Scope,           // ::
    Increment,       // ++
    Decrement,       // --
    LShift,          // <<
    RShift,          // >>

    // Triple-character tokens
    Ellipsis, // ...

    // Literals
    Identifier,
    IntegerLiteral,
    FloatingLiteral,
    StringLiteral,
    CharLiteral,
    BooleanLiteral,

    // Keywords
    Auto,
    Struct,
    Class,
    Union,
    Enum,
    If,
    Else,
    For,
    While,
    Return,
    Match,
    Import,
    Namespace,
    True,
    False,

    // Primitive Types
    Int32,
    Float,
    Double,
    Char,
    Bool,
    Void,
    Int64,
    Int16,
    Signed,
    Unsigned,
    WChar_T,

    // End of file
    EndOfFile,

    // Invalid token
    Invalid
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
