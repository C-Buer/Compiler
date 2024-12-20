#include "Parser/Parser.hpp"
#include "AST/AST.hpp"
#include "Lexer/Token.hpp"
#include <cstddef>
#include <memory>
#include <utility>
#include <vector>

BasicTypeExpr::BasicType TokenToBasic(TokenType token)
{
    switch (token)
    {
    case TokenType::Float:
        return BasicTypeExpr::Float;
    case TokenType::Double:
        return BasicTypeExpr::Double;
    case TokenType::Char:
        return BasicTypeExpr::Char;
    case TokenType::Bool:
        return BasicTypeExpr::Bool;
    case TokenType::Void:
        return BasicTypeExpr::Void;
    case TokenType::Int64:
        return BasicTypeExpr::Int64;
    case TokenType::Int32:
        return BasicTypeExpr::Int32;
    case TokenType::Int16:
        return BasicTypeExpr::Int16;
    case TokenType::Int8:
        return BasicTypeExpr::Int8;
    case TokenType::UInt64:
        return BasicTypeExpr::UInt64;
    case TokenType::UInt32:
        return BasicTypeExpr::UInt32;
    case TokenType::UInt16:
        return BasicTypeExpr::UInt8;
    case TokenType::UInt8:
        return BasicTypeExpr::UInt8;
    default:
        return BasicTypeExpr::Void;
    }
}

// Helper function to determine if a token is a base type
bool Parser::isBaseType(TokenType type) const
{
    switch (type)
    {
    case TokenType::String:
    case TokenType::Char:
    case TokenType::Bool:
    case TokenType::Void:
    case TokenType::Float:
    case TokenType::Double:
    case TokenType::Int64:
    case TokenType::Int32:
    case TokenType::Int16:
    case TokenType::Int8:
    case TokenType::UInt64:
    case TokenType::UInt32:
    case TokenType::UInt16:
    case TokenType::UInt8:
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

bool Parser::printErrorMsg()
{
    if (errorMsgList.empty())
    {
        return false;
    }
    for (auto &msg : errorMsgList)
    {
        std::cerr << msg;
    }
    return true;
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
    if (disableError)
    {
        return;
    }
    errorMsgList.push_back(std::format("Error at line {}, column{}, token '{}', error message: {}\n", token.line,
                                       token.column, token.lexeme, message));
}

std::unique_ptr<Statement> Parser::parseStatement()
{
    size_t save = current;
    std::unique_ptr<Expression> type;
    switch (peekToken().type)
    {
    case TokenType::Namespace:
        advanceToken();
        return parseNamespaceStatement();
    case TokenType::Import:
        advanceToken();
        return parseImportStatement();
    case TokenType::If:
        advanceToken();
        return parseIfStatement();
    case TokenType::For:
        advanceToken();
        return parseForStatement();
    case TokenType::While:
        advanceToken();
        return parseWhileStatement();
    case TokenType::Return:
        advanceToken();
        return parseReturnStatement();
    case TokenType::Struct:
        advanceToken();
        return parseStructStatement();
    case TokenType::LeftBrace:
        advanceToken();
        return parseBlock();
    case TokenType::Label:
        advanceToken();
        return parseLabelStatement();
    case TokenType::Case:
        advanceToken();
        return nullptr;
    case TokenType::Goto:
        advanceToken();
        return parseGotoStatement();
    case TokenType::Identifier:
    case TokenType::String:
    case TokenType::Char:
    case TokenType::Bool:
    case TokenType::Void:
    case TokenType::Float:
    case TokenType::Double:
    case TokenType::Int64:
    case TokenType::Int32:
    case TokenType::Int16:
    case TokenType::Int8:
    case TokenType::UInt64:
    case TokenType::UInt32:
    case TokenType::UInt16:
    case TokenType::UInt8:
        // Look ahead to determine if it's a function or variable declaration
        disableError = true;
        type = parsePrimaryType();
        disableError = false;

        if (check(TokenType::Identifier))
        {
            advanceToken(); // Consume identifier

            if (check(TokenType::LeftParen))
            {
                // It's a function declaration
                current = save; // Reset to before type
                return parseFunctionStatement();
            }
            else
            {
                // It's a variable declaration
                current = save; // Reset to before type
                return parseVariableStatement();
            }
        }
        current = save;
        return parseExpressionStatement();
    default:
        return parseExpressionStatement();
    }
}

std::unique_ptr<Statement> Parser::parseVariableStatement()
{
    // Check if the current token is a type
    auto type = parsePrimaryType();
    if (!type)
    {
        error("Expected type in variable declaration", peekToken());
        return nullptr;
    }

    auto initializer = parseAssignExpr();
    if (!initializer)
    {
        error("Expected initializer expression", peekToken());
        return nullptr;
    }
    if (!match(TokenType::Semicolon))
    {
        error("Expected ';' after variable declaration", peekToken());
        return nullptr;
    }
    return std::make_unique<VariableDefinition>(std::move(type), std::move(initializer));
}

std::unique_ptr<Statement> Parser::parseStructStatement()
{
    auto type = parsePrimaryType();
    if (!type)
    {
        error("Expected type name in struct declaration", peekToken());
        return nullptr;
    }

    if (!match(TokenType::LeftBrace))
    {
        error("Expected '{' to start struct body", peekToken());
        return nullptr;
    }

    std::unique_ptr<Statement> body = parseBlock();

    if (!body)
    {
        error("Expected body after struct declare", peekToken());
        return nullptr;
    }

    return std::make_unique<StructDefinition>(std::move(type), std::move(body));
}

std::unique_ptr<Statement> Parser::parseFunctionStatement()
{
    // Assume the current token is a type
    auto returnType = parsePrimaryType();
    if (!returnType)
    {
        error("Expected return type for function", peekToken());
        return nullptr;
    }

    if (!check(TokenType::Identifier))
    {
        error("Expected function name", peekToken());
        return nullptr;
    }

    auto name = parseNamesapce();
    advanceToken(); // Consume function name

    if (!match(TokenType::LeftParen))
    {
        error("Expected '(' after function name", peekToken());
        return nullptr;
    }

    // Parse parameters
    auto parameters = parseParamExpr();

    if (!match(TokenType::RightParen))
    {
        error("Expected ')' after parameters", peekToken());
        return nullptr;
    }

    if (match(TokenType::Semicolon))
    {
        return std::make_unique<FunctionDeclaration>(std::move(returnType), std::move(name), std::move(parameters));
    }

    // Parse function body (block)
    if (!match(TokenType::LeftBrace))
    {
        error("Expected '{' to start function body", peekToken());
        return nullptr;
    }

    std::unique_ptr<Statement> body = parseBlock();
    if (!body)
    {
        error("Expected function body", peekToken());
        return nullptr;
    }

    return std::make_unique<FunctionDefinition>(std::move(returnType), std::move(name), std::move(parameters),
                                                std::move(body));
}

std::unique_ptr<Statement> Parser::parseBlock()
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

std::unique_ptr<Statement> Parser::parseNamespaceStatement()
{
    auto name = parsePrimaryType();
    if (!name)
    {
        error("Expected name expression after 'namespace'", peekToken());
        return nullptr;
    }
    if (!match(TokenType::LeftBrace))
    {
        error("Expected '{' to start namespace body", peekToken());
        return nullptr;
    }
    auto body = parseBlock();
    if (!body)
    {
        error("Expected namespace body", peekToken());
        return nullptr;
    }
    return std::make_unique<NamespaceStatement>(std::move(name), std::move(body));
}

std::unique_ptr<Statement> Parser::parseImportStatement()
{
    if (!match(TokenType::StringLiteral))
    {
        error("Expected a file path to import", peekToken());
        return nullptr;
    }
    auto path = previousToken().lexeme;
    if (match(TokenType::Semicolon))
    {
        return std::make_unique<ImportStatement>(path);
    }
    if (!match(TokenType::As))
    {
        error("Expected ';' after import statement", peekToken());
        return nullptr;
    }

    auto value = parsePrimaryType();
    if (!value)
    {
        error("Expected namespace expression after 'as'", peekToken());
        return nullptr;
    }
    if (!match(TokenType::Semicolon))
    {
        error("Expected ';' after import statement", peekToken());
        return nullptr;
    }
    return std::make_unique<ImportStatement>(path, std::move(value));
}

std::unique_ptr<Statement> Parser::parseReturnStatement()
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
std::unique_ptr<Statement> Parser::parseIfStatement()
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
std::unique_ptr<Statement> Parser::parseForStatement()
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
            initializer = parseVariableStatement();
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
        increment = parseMultiExpr();
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
std::unique_ptr<Statement> Parser::parseWhileStatement()
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
    auto expr = parseAssignExpr();
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

// Implement parseLabelStatement
std::unique_ptr<Statement> Parser::parseLabelStatement()
{
    if (!check(TokenType::Identifier))
    {
        error("Expected identifier after lable statement", peekToken());
        return nullptr;
    }
    auto name = std::make_unique<IdentifierExpr>(advanceToken().lexeme);
    if (!match(TokenType::Semicolon))
    {
        error("Expected ';' after lable statement", peekToken());
        return nullptr;
    }
    return std::make_unique<LabelStatement>(std::move(name));
}

// Implement parseGotoStatement
std::unique_ptr<Statement> Parser::parseGotoStatement()
{
    if (!check(TokenType::Identifier))
    {
        error("Expected identifier after goto statement", peekToken());
        return nullptr;
    }
    auto name = std::make_unique<IdentifierExpr>(advanceToken().lexeme);
    if (!match(TokenType::Semicolon))
    {
        error("Expected ';' after goto statement", peekToken());
        return nullptr;
    }
    return std::make_unique<GotoStatement>(std::move(name));
}

std::unique_ptr<Expression> Parser::parseMultiExpr()
{
    std::vector<std::unique_ptr<Expression>> parameters;
    for (bool isBegin = true; !check(TokenType::RightParen) && !check(TokenType::RightBracket) &&
                              !check(TokenType::RightBrace) && !check(TokenType::Semicolon);
         isBegin = false)
    {
        if (!match(TokenType::Comma) && !isBegin)
        {
            error("Expected comma after experssion", peekToken());
            return nullptr;
        }
        auto expr = parseExpression();
        if (!expr)
        {
            error("Expected expression after comma", peekToken());
            return nullptr;
        }
        parameters.push_back(std::move(expr));
    }
    return std::make_unique<MultiExpr>(parameters);
}

std::unique_ptr<Expression> Parser::parseParamExpr()
{
    std::vector<std::unique_ptr<Expression>> parameters;
    for (bool isBegin = true; !check(TokenType::RightParen) && !check(TokenType::RightBracket) &&
                              !check(TokenType::RightBrace) && !check(TokenType::Semicolon);
         isBegin = false)
    {
        if (!match(TokenType::Comma) && !isBegin)
        {
            error("Expected comma after experssion", peekToken());
            return nullptr;
        }
        auto expr = parseParameter();
        if (!expr)
        {
            error("Expected expression after comma", peekToken());
            return nullptr;
        }
        parameters.push_back(std::move(expr));
    }
    return std::make_unique<MultiExpr>(parameters);
}

std::unique_ptr<Expression> Parser::parseAssignExpr()
{
    std::vector<std::unique_ptr<Expression>> parameters;
    for (bool isBegin = true; !check(TokenType::RightParen) && !check(TokenType::RightBracket) &&
                              !check(TokenType::RightBrace) && !check(TokenType::Semicolon);
         isBegin = false)
    {
        if (!match(TokenType::Comma) && !isBegin)
        {
            error("Expected comma after experssion", peekToken());
            return nullptr;
        }
        auto expr = parseAssignment();
        if (!expr)
        {
            error("Expected expression after comma", peekToken());
            return nullptr;
        }
        parameters.push_back(std::move(expr));
    }
    return std::make_unique<MultiExpr>(parameters);
}

std::unique_ptr<Expression> Parser::parseExpression()
{
    return parseEquality();
}

std::unique_ptr<Expression> Parser::parseParameter()
{
    // Check if the current token is a type
    if (isType(peekToken().type))
    {
        auto type = parsePrimaryType();

        std::unique_ptr<Expression> initializer = parseAssignment();
        if (!initializer)
        {
            error("Expected initializer expression", peekToken());
            return nullptr;
        }

        return std::make_unique<ParameterExpr>(std::move(type), std::move(initializer));
    }

    error("Expected type in parameter declaration", peekToken());
    return nullptr;
}

std::unique_ptr<Expression> Parser::parseAssignment()
{
    auto startPos = current;
    disableError = true;
    auto expr = parseMemberAccess();
    disableError = false;

    if (match(TokenType::Equals))
    {
        Token equals = previousToken();
        auto value = parseEquality();
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

    if (!check(TokenType::RightParen) && !check(TokenType::RightBracket) && !check(TokenType::RightBrace) &&
        !check(TokenType::Semicolon))
    {
        current = startPos;
        if (!expr)
        {
            // errorMsgList.pop_back();
        }
        expr = parseEquality();
    }
    return expr;
}

std::unique_ptr<Expression> Parser::parseEquality()
{
    auto startPos = current;
    disableError = true;
    auto expr = parseMemberAccess();
    disableError = false;

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

    if (!check(TokenType::RightParen) && !check(TokenType::RightBracket) && !check(TokenType::RightBrace) &&
        !check(TokenType::Semicolon))
    {
        current = startPos;
        if (!expr)
        {
            // errorMsgList.pop_back();
        }
        expr = parseComparison();
    }
    return expr;
}

std::unique_ptr<Expression> Parser::parseComparison()
{
    auto startPos = current;
    disableError = true;
    auto expr = parseMemberAccess();
    disableError = false;

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

    if (!check(TokenType::RightParen) && !check(TokenType::RightBracket) && !check(TokenType::RightBrace) &&
        !check(TokenType::Semicolon))
    {
        current = startPos;
        if (!expr)
        {
            // errorMsgList.pop_back();
        }
        expr = parseTerm();
    }
    return expr;
}

std::unique_ptr<Expression> Parser::parseTerm()
{
    auto startPos = current;
    disableError = true;
    auto expr = parsePrimary();
    disableError = false;

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

    if (!check(TokenType::RightParen) && !check(TokenType::RightBracket) && !check(TokenType::RightBrace) &&
        !check(TokenType::Semicolon))
    {
        current = startPos;
        if (!expr)
        {
            // errorMsgList.pop_back();
        }
        expr = parseFactor();
    }
    return expr;
}

std::unique_ptr<Expression> Parser::parseFactor()
{
    auto startPos = current;
    disableError = true;
    auto expr = parsePrimary();
    disableError = false;

    while (match(TokenType::Star) || match(TokenType::Slash) || match(TokenType::Percent))
    {
        Token oper = previousToken();
        auto right = parseUnaryBack();
        if (!right)
        {
            error("Expected expression after operator", oper);
            return nullptr;
        }
        expr = std::make_unique<BinaryExpr>(oper.lexeme, std::move(expr), std::move(right));
    }

    if (!check(TokenType::RightParen) && !check(TokenType::RightBracket) && !check(TokenType::RightBrace) &&
        !check(TokenType::Semicolon))
    {
        current = startPos;
        if (!expr)
        {
            // errorMsgList.pop_back();
        }
        expr = parseUnaryBack();
    }
    return expr;
}

std::unique_ptr<Expression> Parser::parseUnaryBack()
{
    auto expr = parseUnaryFront();
    while (match(TokenType::Increment) || match(TokenType::Decrement))
    {
        Token oper = previousToken();
        if (!expr)
        {
            error("Expected expression before unary operator", oper);
            return nullptr;
        }

        expr = std::make_unique<UnaryExpr>(oper.lexeme, std::move(expr));
    }
    return expr;
}

std::unique_ptr<Expression> Parser::parseUnaryFront()
{
    while (match(TokenType::Exclamation) || match(TokenType::Decrement) || match(TokenType::Increment))
    {
        Token oper = previousToken();
        auto right = parseUnaryFront();
        if (!right)
        {
            error("Expected expression after unary operator", oper);
            return nullptr;
        }

        return std::make_unique<UnaryExpr>(oper.lexeme, std::move(right), true);
    }
    return parseMemberAccess();
}

std::unique_ptr<Expression> Parser::parseMemberAccess()
{
    auto expr = parseSubsript();

    while (match(TokenType::Dot) || match(TokenType::Arrow))
    {
        auto isPtr = previousToken().type == TokenType::Arrow;
        if (!expr)
        {
            error("Expected name expression before dot or arrow member access", previousToken());
            return nullptr;
        }
        auto member = parseSubsript();
        if (!member)
        {
            error("Expected member expression after dot or arrow member access", previousToken());
            return nullptr;
        }

        expr = std::make_unique<MemberAccessExpr>(isPtr, std::move(expr), std::move(member));
    }
    return expr;
}

std::unique_ptr<Expression> Parser::parseSubsript()
{
    auto expr = parseFunctionCall();
    while (match(TokenType::LeftBracket))
    {
        if (!expr)
        {
            error("Expected expression before subscript", previousToken());
            return nullptr;
        }
        std::unique_ptr<Expression> parameters = parseMultiExpr();
        if (!match(TokenType::RightBracket))
        {
            error("Expected ']' after subscript", peekToken());
            return nullptr;
        }
        expr = std::make_unique<SubscriptExpr>(std::move(expr), std::move(parameters));
    }
    return expr;
}

std::unique_ptr<Expression> Parser::parseFunctionCall()
{
    auto expr = parsePrimary();
    if (match(TokenType::LeftParen))
    {
        if (!expr)
        {
            error("Expected name expression before function call", previousToken());
            return nullptr;
        }
        std::unique_ptr<Expression> parameters = parseMultiExpr();
        if (!match(TokenType::RightParen))
        {
            error("Expected ')' after function call", peekToken());
            return nullptr;
        }
        return std::make_unique<FunctionCallExpr>(std::move(expr), std::move(parameters));
    }
    return expr;
}

std::unique_ptr<Expression> Parser::parsePrimary()
{
    if (isType(peekToken().type))
    {
        return parsePrimaryType();
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
    if (match(TokenType::LeftBrace))
    {
        auto expr = parseMultiExpr();
        if (!match(TokenType::RightBrace))
        {
            error("Expected '}' after expression", peekToken());
            return nullptr;
        }
        return std::make_unique<BindExpr>(std::move(expr));
    }
    return parseConstant();
}

std::unique_ptr<Expression> Parser::parsePrimaryType()
{
    if (match(TokenType::Identifier))
    {
        if (!check(TokenType::Scope))
        {
            return std::make_unique<IdentifierExpr>(previousToken().lexeme);
        }
        return parseNamesapce();
    }
    return std::make_unique<BasicTypeExpr>(TokenToBasic(advanceToken().type));
}

std::unique_ptr<Expression> Parser::parseNamesapce()
{
    std::unique_ptr<Expression> zone = std::make_unique<IdentifierExpr>(previousToken().lexeme);
    std::vector<std::unique_ptr<Expression>> name;
    while (match(TokenType::Scope))
    {
        if (!match(TokenType::Identifier))
        {
            error("Expected member expression after scope", previousToken());
            return nullptr;
        }
        name.push_back(std::make_unique<IdentifierExpr>(previousToken().lexeme));
    }
    return std::make_unique<NamespaceExpr>(std::move(zone), name);
}

std::unique_ptr<Expression> Parser::parseConstant()
{
    if (match(TokenType::IntegerLiteral))
    {
        auto number = previousToken().lexeme;
        if (number[0] != '0' || number.size() == 1)
        {
            return std::make_unique<Literal>(std::stoll(number));
        }
        auto head = number[1];
        if (std::isdigit(head))
        {
            return std::make_unique<Literal>(std::stoll(number.substr(1), nullptr, 8));
        }
        number = number.substr(2);
        if (head == 'B' || head == 'b')
        {
            return std::make_unique<Literal>(std::stoll(number, nullptr, 2));
        }
        if (head == 'X' || head == 'x')
        {
            return std::make_unique<Literal>(std::stoll(number, nullptr, 16));
        }
    }
    if (match(TokenType::FloatingLiteral))
    {
        return std::make_unique<Literal>(std::stod(previousToken().lexeme));
    }
    if (match(TokenType::StringLiteral))
    {
        return std::make_unique<Literal>(previousToken().lexeme);
    }
    if (match(TokenType::CharLiteral))
    {
        return std::make_unique<Literal>(previousToken().lexeme[0]);
    }
    if (match(TokenType::BooleanLiteral))
    {
        return std::make_unique<Literal>(previousToken().lexeme == "true");
    }
    error("Expected constant", peekToken());
    return nullptr;
}
