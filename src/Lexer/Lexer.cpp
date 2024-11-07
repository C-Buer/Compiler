#include "Lexer/Lexer.hpp"
#include <cctype>
#include <iostream>

Lexer::Lexer(const std::string &source) : source(source)
{
}

std::vector<Token> Lexer::tokenize()
{
    while (current < source.length())
    {
        skipWhitespace();
        if (current >= source.length())
            break;

        char c = peek();

        // Handle comments
        if (c == '/' && peekNext() == '/')
        {
            skipComment();
            continue;
        }

        // Single-character tokens
        switch (c)
        {
        case '(':
            addToken(TokenType::LeftParen, "(");
            advance();
            break;
        case ')':
            addToken(TokenType::RightParen, ")");
            advance();
            break;
        case '{':
            addToken(TokenType::LeftBrace, "{");
            advance();
            break;
        case '}':
            addToken(TokenType::RightBrace, "}");
            advance();
            break;
        case '[':
            addToken(TokenType::LeftBracket, "[");
            advance();
            break;
        case ']':
            addToken(TokenType::RightBracket, "]");
            advance();
            break;
        case ',':
            addToken(TokenType::Comma, ",");
            advance();
            break;
        case '.':
            if (peekNext() == '.')
            { // Handle ellipsis or range if needed
                addToken(TokenType::Dot, "..");
                advance();
                advance();
            }
            else
            {
                addToken(TokenType::Dot, ".");
                advance();
            }
            break;
        case ';':
            addToken(TokenType::Semicolon, ";");
            advance();
            break;
        case ':':
            if (peekNext() == ':')
            {
                addToken(TokenType::Colon, "::");
                advance();
                advance();
            }
            else
            {
                addToken(TokenType::Colon, ":");
                advance();
            }
            break;
        case '+':
            addToken(TokenType::Plus, "+");
            advance();
            break;
        case '-':
            if (peekNext() == '>')
            {
                addToken(TokenType::Arrow, "->");
                advance();
                advance();
            }
            else
            {
                addToken(TokenType::Minus, "-");
                advance();
            }
            break;
        case '*':
            addToken(TokenType::Star, "*");
            advance();
            break;
        case '/':
            addToken(TokenType::Slash, "/");
            advance();
            break;
        case '%':
            addToken(TokenType::Percent, "%");
            advance();
            break;
        case '&':
            if (peekNext() == '&')
            {
                addToken(TokenType::DoubleAmpersand, "&&");
                advance();
                advance();
            }
            else
            {
                addToken(TokenType::Ampersand, "&");
                advance();
            }
            break;
        case '|':
            if (peekNext() == '|')
            {
                addToken(TokenType::DoublePipe, "||");
                advance();
                advance();
            }
            else
            {
                addToken(TokenType::Pipe, "|");
                advance();
            }
            break;
        case '^':
            addToken(TokenType::Caret, "^");
            advance();
            break;
        case '!':
            if (peekNext() == '=')
            {
                addToken(TokenType::NotEquals, "!=");
                advance();
                advance();
            }
            else
            {
                addToken(TokenType::Exclamation, "!");
                advance();
            }
            break;
        case '~':
            addToken(TokenType::Tilde, "~");
            advance();
            break;
        case '?':
            addToken(TokenType::Question, "?");
            advance();
            break;
        case '<':
            if (peekNext() == '=')
            {
                addToken(TokenType::LessEquals, "<=");
                advance();
                advance();
            }
            else
            {
                addToken(TokenType::Less, "<");
                advance();
            }
            break;
        case '>':
            if (peekNext() == '=')
            {
                addToken(TokenType::GreaterEquals, ">=");
                advance();
                advance();
            }
            else
            {
                addToken(TokenType::Greater, ">");
                advance();
            }
            break;
        case '=':
            if (peekNext() == '=')
            {
                addToken(TokenType::DoubleEquals, "==");
                advance();
                advance();
            }
            else
            {
                addToken(TokenType::Equals, "=");
                advance();
            }
            break;
        case '"':
            tokens.push_back(string());
            break;
        case '\'':
            tokens.push_back(character());
            break;
        default:
            if (std::isalpha(c) || c == '_')
            {
                tokens.push_back(identifier());
            }
            else if (std::isdigit(c))
            {
                tokens.push_back(number());
            }
            else
            {
                // Invalid character
                std::cerr << "Unexpected character: " << c << " at line " << line << ", column " << column << "\n";
                addToken(TokenType::Invalid, std::string(1, c));
                advance();
            }
            break;
        }
    }

    tokens.emplace_back(TokenType::EndOfFile, "", line, column);
    return tokens;
}

char Lexer::peek()
{
    if (current >= source.length())
        return '\0';
    return source[current];
}

char Lexer::peekNext()
{
    if (current + 1 >= source.length())
        return '\0';
    return source[current + 1];
}

char Lexer::advance()
{
    char c = source[current++];
    if (c == '\n')
    {
        line++;
        column = 1;
    }
    else
    {
        column++;
    }
    return c;
}

bool Lexer::match(char expected)
{
    if (peek() == expected)
    {
        advance();
        return true;
    }
    return false;
}

void Lexer::addToken(TokenType type, const std::string &lexeme)
{
    tokens.emplace_back(type, lexeme, line, column);
}

void Lexer::skipWhitespace()
{
    while (current < source.length())
    {
        char c = peek();
        if (c == ' ' || c == '\r' || c == '\t' || c == '\n')
        {
            advance();
        }
        else
        {
            break;
        }
    }
}

void Lexer::skipComment()
{
    while (peek() != '\n' && peek() != '\0')
    {
        advance();
    }
}

Token Lexer::identifier()
{
    size_t start = current;
    while (std::isalnum(peek()) || peek() == '_')
        advance();
    std::string lexeme = source.substr(start, current - start);
    auto it = keywords.find(lexeme);
    if (it != keywords.end())
    {
        if (it->second == TokenType::True || it->second == TokenType::False)
        {
            return Token(TokenType::BooleanLiteral, lexeme, line, column);
        }
        return Token(it->second, lexeme, line, column);
    }
    return Token(TokenType::Identifier, lexeme, line, column);
}

Token Lexer::number()
{
    size_t start = current;
    while (std::isdigit(peek()))
        advance();

    // Check for floating point
    if (peek() == '.' && std::isdigit(peekNext()))
    {
        advance(); // consume '.'
        while (std::isdigit(peek()))
            advance();
        // Optional exponent
        if (peek() == 'e' || peek() == 'E')
        {
            advance();
            if (peek() == '+' || peek() == '-')
                advance();
            while (std::isdigit(peek()))
                advance();
        }
        return Token(TokenType::FloatingLiteral, source.substr(start, current - start), line, column);
    }

    // Handle different number bases (hex, octal, binary)
    if (source[start] == '0')
    {
        if (peek() == 'x' || peek() == 'X')
        {              // Hex
            advance(); // consume 'x'
            while (std::isxdigit(peek()))
                advance();
            return Token(TokenType::IntegerLiteral, source.substr(start, current - start), line, column);
        }
        else if (peek() == 'b' || peek() == 'B')
        {              // Binary
            advance(); // consume 'b'
            while (peek() == '0' || peek() == '1')
                advance();
            return Token(TokenType::IntegerLiteral, source.substr(start, current - start), line, column);
        }
        else
        { // Octal
            while (peek() >= '0' && peek() <= '7')
                advance();
            return Token(TokenType::IntegerLiteral, source.substr(start, current - start), line, column);
        }
    }

    return Token(TokenType::IntegerLiteral, source.substr(start, current - start), line, column);
}

Token Lexer::string()
{
    size_t startLine = line;
    size_t startColumn = column;
    std::string value;
    advance(); // consume opening "

    while (peek() != '"' && peek() != '\0')
    {
        if (peek() == '\\')
        {              // Handle escape sequences
            advance(); // consume '\\'
            char esc = peek();
            switch (esc)
            {
            case 'n':
                value += '\n';
                break;
            case 't':
                value += '\t';
                break;
            case '\\':
                value += '\\';
                break;
            case '"':
                value += '"';
                break;
            case '\'':
                value += '\'';
                break;
            case 'r':
                value += '\r';
                break;
            case '0':
                value += '\0';
                break;
            default:
                value += esc;
                break;
            }
            advance();
        }
        else
        {
            value += peek();
            advance();
        }
    }

    if (peek() == '"')
    {
        advance(); // consume closing "
        return Token(TokenType::StringLiteral, value, startLine, startColumn);
    }
    else
    {
        // Unterminated string
        std::cerr << "Unterminated string at line " << startLine << ", column " << startColumn << "\n";
        return Token(TokenType::Invalid, value, startLine, startColumn);
    }
}

Token Lexer::character()
{
    size_t startLine = line;
    size_t startColumn = column;
    std::string value;
    advance(); // consume opening '

    if (peek() == '\\')
    {              // Escape sequence
        advance(); // consume '\\'
        char esc = peek();
        switch (esc)
        {
        case 'n':
            value += '\n';
            break;
        case 't':
            value += '\t';
            break;
        case '\\':
            value += '\\';
            break;
        case '"':
            value += '"';
            break;
        case '\'':
            value += '\'';
            break;
        case 'r':
            value += '\r';
            break;
        case '0':
            value += '\0';
            break;
        default:
            value += esc;
            break;
        }
        advance();
    }
    else
    {
        value += peek();
        advance();
    }

    if (peek() == '\'')
    {
        advance(); // consume closing '
        return Token(TokenType::CharLiteral, value, startLine, startColumn);
    }
    else
    {
        // Unterminated character literal
        std::cerr << "Unterminated character literal at line " << startLine << ", column " << startColumn << "\n";
        return Token(TokenType::Invalid, value, startLine, startColumn);
    }
}