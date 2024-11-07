#include "Parser\Parser.hpp"
#include "AST/AST.hpp"
#include "Lexer/Token.hpp"
#include <iostream>
#include <memory>

// Helper function to determine if a token is a base type
bool Parser::isBaseType(TokenType type) const
{
    switch (type)
    {
    case TokenType::Int:
    case TokenType::Float:
    case TokenType::Double:
    case TokenType::Char:
    case TokenType::Bool:
    case TokenType::Void:
    case TokenType::Long:
    case TokenType::Short:
    case TokenType::Signed:
    case TokenType::Unsigned:
    case TokenType::WChar_T:
        return true;
    default:
        return false;
    }
}

// Helper function to determine if a token is a type
bool Parser::isType(TokenType type) const
{
    return isBaseType(type) || type == TokenType::Identifier;
}

bool Parser::isValid(TokenType type) const
{
    return type != TokenType::Invalid;
}

Parser::Parser(const std::vector<Token> &tokens) : tokens(tokens)
{
}

std::unique_ptr<Program> Parser::parse()
{
    auto program = std::make_unique<Program>();
    while (!isAtEnd())
    {
        auto stmt = parseStatement();
        if (stmt)
        {
            program->statements.emplace_back(std::move(stmt));
        }
        else
        {
            // Error recovery: skip to next token
            advanceToken();
        }
    }
    return program;
}

bool Parser::match(TokenType type)
{
    if (check(type))
    {
        advanceToken();
        return true;
    }
    return false;
}

bool Parser::check(TokenType type) const
{
    if (isAtEnd())
        return false;
    return peekToken().type == type;
}

Token Parser::advanceToken()
{
    if (!isAtEnd())
        current++;
    return previousToken();
}

Token Parser::peekToken() const
{
    return tokens[current];
}

Token Parser::previousToken() const
{
    return tokens[current - 1];
}

bool Parser::isAtEnd() const
{
    return peekToken().type == TokenType::EndOfFile;
}

void Parser::error(const std::string &message, const Token &token)
{
    std::cerr << "Error at line " << token.line << ", column " << token.column << ": " << message << "\n";
}

std::unique_ptr<Statement> Parser::parseStatement()
{
    if (match(TokenType::If))
    {
        return parseIfStatement();
    }
    if (match(TokenType::For))
    {
        return parseForStatement();
    }
    if (match(TokenType::While))
    {
        return parseWhileStatement();
    }
    if (match(TokenType::Return))
    {
        return parseReturnStatement();
    }
    if (isType(peekToken().type))
    {
        // Look ahead to determine if it's a function or variable declaration
        size_t save = current;
        Token typeToken = peekToken();
        advanceToken(); // Consume type

        if (check(TokenType::Identifier))
        {
            Token nameToken = peekToken();
            advanceToken(); // Consume identifier

            if (check(TokenType::LeftParen))
            {
                // It's a function declaration
                current = save; // Reset to before type
                return parseFunctionDeclaration();
            }
            else
            {
                // It's a variable declaration
                current = save; // Reset to before type
                return parseVariableDeclaration();
            }
        }
        else
        {
            current = save;
            return parseExpressionStatement();
        }
    }
    else
    {
        return parseExpressionStatement();
    }

    error("Unknown statement", peekToken());
    return nullptr;
}

std::unique_ptr<VariableDeclaration> Parser::parseVariableDeclaration()
{
    // Check if the current token is a type
    if (isType(peekToken().type))
    {
        Token typeToken = peekToken();
        std::string type = typeToken.lexeme;
        advanceToken(); // Consume the type token

        if (!check(TokenType::Identifier))
        {
            error("Expected variable name", peekToken());
            return nullptr;
        }

        Token nameToken = peekToken();
        std::string name = nameToken.lexeme;
        advanceToken(); // Consume the identifier

        std::unique_ptr<Expression> initializer = nullptr;
        if (match(TokenType::Equals))
        {
            initializer = parseExpression();
            if (!initializer)
            {
                error("Expected initializer expression", peekToken());
                return nullptr;
            }
        }

        if (!match(TokenType::Semicolon))
        {
            error("Expected ';' after variable declaration", peekToken());
            return nullptr;
        }

        return std::make_unique<VariableDeclaration>(type, name, std::move(initializer));
    }

    error("Expected type in variable declaration", peekToken());
    return nullptr;
}

std::unique_ptr<FunctionDeclaration> Parser::parseFunctionDeclaration()
{
    // Assume the current token is a type
    if (!isType(peekToken().type))
    {
        error("Expected return type for function", peekToken());
        return nullptr;
    }

    Token typeToken = peekToken();
    std::string returnType = typeToken.lexeme;
    advanceToken(); // Consume return type

    if (!check(TokenType::Identifier))
    {
        error("Expected function name", peekToken());
        return nullptr;
    }

    Token nameToken = peekToken();
    std::string name = nameToken.lexeme;
    advanceToken(); // Consume function name

    if (!match(TokenType::LeftParen))
    {
        error("Expected '(' after function name", peekToken());
        return nullptr;
    }

    // Parse parameters
    std::vector<Parameter> parameters;
    if (!check(TokenType::RightParen))
    { // Non-empty parameter list
        while (true)
        {
            if (!isType(peekToken().type))
            {
                error("Expected parameter type", peekToken());
                return nullptr;
            }

            Token paramTypeToken = peekToken();
            std::string paramType = paramTypeToken.lexeme;
            advanceToken(); // Consume parameter type

            if (!check(TokenType::Identifier))
            {
                error("Expected parameter name", peekToken());
                return nullptr;
            }

            Token paramNameToken = peekToken();
            std::string paramName = paramNameToken.lexeme;
            advanceToken(); // Consume parameter name

            parameters.emplace_back(paramType, paramName);

            if (match(TokenType::Comma))
            {
                continue;
            }
            else
            {
                break;
            }
        }
    }

    if (!match(TokenType::RightParen))
    {
        error("Expected ')' after parameters", peekToken());
        return nullptr;
    }

    // Parse function body (block)
    if (!match(TokenType::LeftBrace))
    {
        error("Expected '{' to start function body", peekToken());
        return nullptr;
    }

    std::unique_ptr<Block> body = parseBlock();
    if (!body)
    {
        error("Expected function body", peekToken());
        return nullptr;
    }

    return std::make_unique<FunctionDeclaration>(returnType, name, parameters, std::move(body));
}

std::unique_ptr<Block> Parser::parseBlock()
{
    auto block = std::make_unique<Block>();

    while (!check(TokenType::RightBrace) && !isAtEnd())
    {
        auto stmt = parseStatement();
        if (stmt)
        {
            block->statements.emplace_back(std::move(stmt));
        }
        else
        {
            // Error recovery: skip to next token
            advanceToken();
        }
    }

    if (!match(TokenType::RightBrace))
    {
        error("Expected '}' after block", peekToken());
        return nullptr;
    }

    return block;
}

std::unique_ptr<Expression> Parser::parseExpression()
{
    return parseAssignment();
}

std::unique_ptr<Expression> Parser::parseAssignment()
{
    auto expr = parseEquality();
    if (match(TokenType::Equals))
    {
        Token equals = previousToken();
        auto value = parseAssignment();
        if (!value)
        {
            error("Expected value after '='", equals);
            return nullptr;
        }

        // For simplicity, handle only identifier = expression
        if (auto idExpr = dynamic_cast<IdentifierExpr *>(expr.get()))
        {
            auto asExpr = std::make_unique<AssignmentExpr>(std::move(expr), std::move(value));
            return asExpr;
        }
        else
        {
            error("Invalid assignment target", equals);
            return nullptr;
        }
    }
    return expr;
}

std::unique_ptr<Expression> Parser::parseEquality()
{
    auto expr = parseComparison();
    while (match(TokenType::DoubleEquals) || match(TokenType::NotEquals))
    {
        Token oper = previousToken();
        auto right = parseComparison();
        if (!right)
        {
            error("Expected expression after comparison operator", oper);
            return nullptr;
        }
        expr = std::make_unique<BinaryExpr>(oper.lexeme, std::move(expr), std::move(right));
    }
    return expr;
}

std::unique_ptr<Expression> Parser::parseComparison()
{
    auto expr = parseTerm();
    while (match(TokenType::Less) || match(TokenType::LessEquals) || match(TokenType::Greater) ||
           match(TokenType::GreaterEquals))
    {
        Token oper = previousToken();
        auto right = parseTerm();
        if (!right)
        {
            error("Expected expression after comparison operator", oper);
            return nullptr;
        }
        expr = std::make_unique<BinaryExpr>(oper.lexeme, std::move(expr), std::move(right));
    }
    return expr;
}

std::unique_ptr<Expression> Parser::parseTerm()
{
    auto expr = parseFactor();
    while (match(TokenType::Plus) || match(TokenType::Minus))
    {
        Token oper = previousToken();
        auto right = parseFactor();
        if (!right)
        {
            error("Expected expression after operator", oper);
            return nullptr;
        }
        expr = std::make_unique<BinaryExpr>(oper.lexeme, std::move(expr), std::move(right));
    }
    return expr;
}

std::unique_ptr<Expression> Parser::parseFactor()
{
    auto expr = parseUnary();
    while (match(TokenType::Star) || match(TokenType::Slash) || match(TokenType::Percent))
    {
        Token oper = previousToken();
        auto right = parseUnary();
        if (!right)
        {
            error("Expected expression after operator", oper);
            return nullptr;
        }
        expr = std::make_unique<BinaryExpr>(oper.lexeme, std::move(expr), std::move(right));
    }
    return expr;
}

std::unique_ptr<Expression> Parser::parseUnary()
{
    if (match(TokenType::Exclamation) || match(TokenType::Minus) || match(TokenType::Plus))
    {
        Token oper = previousToken();
        auto right = parseUnary();
        if (!right)
        {
            error("Expected expression after unary operator", oper);
            return nullptr;
        }
        // For simplicity, treat unary as binary with left operand as null
        return std::make_unique<BinaryExpr>(oper.lexeme, nullptr, std::move(right));
    }
    return parsePrimary();
}

std::unique_ptr<Expression> Parser::parsePrimary()
{
    if (match(TokenType::IntegerLiteral))
    {
        return std::make_unique<Literal>(previousToken().lexeme);
    }
    if (match(TokenType::FloatingLiteral))
    {
        return std::make_unique<Literal>(previousToken().lexeme);
    }
    if (match(TokenType::StringLiteral))
    {
        return std::make_unique<Literal>(previousToken().lexeme);
    }
    if (match(TokenType::CharLiteral))
    {
        return std::make_unique<Literal>(previousToken().lexeme);
    }
    if (match(TokenType::BooleanLiteral))
    {
        return std::make_unique<Literal>(previousToken().lexeme);
    }
    if (match(TokenType::Identifier))
    {
        return std::make_unique<IdentifierExpr>(previousToken().lexeme);
    }
    if (match(TokenType::LeftParen))
    {
        auto expr = parseExpression();
        if (!match(TokenType::RightParen))
        {
            error("Expected ')' after expression", peekToken());
            return nullptr;
        }
        return expr;
    }

    error("Expected expression", peekToken());
    return nullptr;
}

std::unique_ptr<ReturnStatement> Parser::parseReturnStatement()
{
    auto returnStmt = std::make_unique<ReturnStatement>();

    if (!check(TokenType::Semicolon))
    {
        returnStmt->value = parseExpression();
        if (!returnStmt->value)
        {
            error("Expected expression after 'return'", peekToken());
            return nullptr;
        }
    }

    if (!match(TokenType::Semicolon))
    {
        error("Expected ';' after return statement", peekToken());
        return nullptr;
    }

    return returnStmt;
}

// Implement parseIfStatement
std::unique_ptr<IfStatement> Parser::parseIfStatement()
{
    // Parse '('
    if (!match(TokenType::LeftParen))
    {
        error("Expected '(' after 'if'", peekToken());
        return nullptr;
    }

    // Parse condition
    auto condition = parseExpression();
    if (!condition)
    {
        error("Expected condition expression in 'if' statement", peekToken());
        return nullptr;
    }

    // Parse ')'
    if (!match(TokenType::RightParen))
    {
        error("Expected ')' after condition in 'if' statement", peekToken());
        return nullptr;
    }

    // Parse thenBranch (must be a Block)
    if (!match(TokenType::LeftBrace))
    {
        error("Expected '{' to start 'then' block in 'if' statement", peekToken());
        return nullptr;
    }

    auto thenBranch = parseBlock();
    if (!thenBranch)
    {
        error("Expected 'then' block in 'if' statement", peekToken());
        return nullptr;
    }

    // Parse optional elseBranch
    std::unique_ptr<Statement> elseBranch = nullptr;
    if (match(TokenType::Else))
    {
        if (match(TokenType::If))
        {
            elseBranch = parseIfStatement();
        }
        else
        {
            if (!match(TokenType::LeftBrace))
            {
                error("Expected '{' to start 'else' block in 'if' statement", peekToken());
                return nullptr;
            }
            elseBranch = parseBlock();
            if (!elseBranch)
            {
                error("Expected 'else' block in 'if' statement", peekToken());
                return nullptr;
            }
        }
    }

    return std::make_unique<IfStatement>(std::move(condition), std::move(thenBranch), std::move(elseBranch));
}

// Implement parseForStatement
std::unique_ptr<ForStatement> Parser::parseForStatement()
{
    // Parse '('
    if (!match(TokenType::LeftParen))
    {
        error("Expected '(' after 'for'", peekToken());
        return nullptr;
    }

    // Parse initializer
    std::unique_ptr<Statement> initializer = nullptr;
    if (!match(TokenType::Semicolon))
    {
        if (isType(peekToken().type))
        {
            initializer = parseVariableDeclaration();
        }
        else
        {
            initializer = parseExpressionStatement();
        }
    }

    // Parse condition
    std::unique_ptr<Expression> condition = nullptr;
    if (!match(TokenType::Semicolon))
    {
        condition = parseExpression();
        if (!condition)
        {
            error("Expected condition expression in 'for' statement", peekToken());
            return nullptr;
        }

        if (!match(TokenType::Semicolon))
        {
            error("Expected ';' after condition in 'for' statement", peekToken());
            return nullptr;
        }
    }

    // Parse increment
    std::unique_ptr<Expression> increment = nullptr;
    if (!check(TokenType::RightParen))
    {
        increment = parseExpression();
    }

    // Parse ')'
    if (!match(TokenType::RightParen))
    {
        error("Expected ')' after for clauses", peekToken());
        return nullptr;
    }

    // Parse body (must be a Block)
    if (!match(TokenType::LeftBrace))
    {
        error("Expected '{' to start 'for' loop body", peekToken());
        return nullptr;
    }

    auto body = parseBlock();
    if (!body)
    {
        error("Expected loop body in 'for' statement", peekToken());
        return nullptr;
    }

    return std::make_unique<ForStatement>(std::move(initializer), std::move(condition), std::move(increment),
                                          std::move(body));
}

// Implement parseWhileStatement
std::unique_ptr<WhileStatement> Parser::parseWhileStatement()
{
    // Parse '('
    if (!match(TokenType::LeftParen))
    {
        error("Expected '(' after 'while'", peekToken());
        return nullptr;
    }

    // Parse condition
    auto condition = parseExpression();
    if (!condition)
    {
        error("Expected condition expression in 'while' statement", peekToken());
        return nullptr;
    }

    // Parse ')'
    if (!match(TokenType::RightParen))
    {
        error("Expected ')' after condition in 'while' statement", peekToken());
        return nullptr;
    }

    // Parse body (must be a Block)
    if (!match(TokenType::LeftBrace))
    {
        error("Expected '{' to start 'while' loop body", peekToken());
        return nullptr;
    }

    auto body = parseBlock();
    if (!body)
    {
        error("Expected loop body in 'while' statement", peekToken());
        return nullptr;
    }

    return std::make_unique<WhileStatement>(std::move(condition), std::move(body));
}

// Implement parseExpressionStatement
std::unique_ptr<Statement> Parser::parseExpressionStatement()
{
    auto expr = parseExpression();
    if (!expr)
    {
        error("Expected expression in statement", peekToken());
        return nullptr;
    }

    if (!match(TokenType::Semicolon))
    {
        error("Expected ';' after expression statement", peekToken());
        return nullptr;
    }

    // Create an ExpressionStatement node
    return std::make_unique<ExpressionStatement>(std::move(expr));
}
