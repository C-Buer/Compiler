#include "Parser/Parser.hpp"
#include "AST/AST.hpp"
#include "Lexer/Token.hpp"
#include <utility>

// Helper function to determine if a token is a base type
bool Parser::isBaseType(TokenType type) const
{
    switch (type)
    {
    case TokenType::Float:
    case TokenType::Double:
    case TokenType::Char:
    case TokenType::Bool:
    case TokenType::Void:
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
    errorMsgList.push_back(std::format("Error at line {}, column{}, token '{}', error message: {}\n", token.line,
                                       token.column, token.lexeme, message));
}

StatementPtr Parser::parseStatement()
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

StatementPtr Parser::parseVariableDeclaration()
{
    // Check if the current token is a type
    if (isType(peekToken().type))
    {
        Token typeToken = peekToken();
        std::string type = typeToken.lexeme;
        advanceToken(); // Consume the type token

        ExpressionPtr initializer = parseAssignExpr();
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

        return std::make_unique<VariableDeclaration>(type, std::move(initializer));
    }

    error("Expected type in variable declaration", peekToken());
    return nullptr;
}

StatementPtr Parser::parseFunctionDeclaration()
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
    auto parameters = parseParamExpr();

    if (!match(TokenType::RightParen))
    {
        error("Expected ')' after parameters", peekToken());
        return nullptr;
    }

    if (match(TokenType::Semicolon))
    {
        return std::make_unique<FunctionDeclaration>(returnType, name, std::move(parameters));
    }

    // Parse function body (block)
    if (!match(TokenType::LeftBrace))
    {
        error("Expected '{' to start function body", peekToken());
        return nullptr;
    }

    StatementPtr body = parseBlock();
    if (!body)
    {
        error("Expected function body", peekToken());
        return nullptr;
    }

    return std::make_unique<FunctionDefinition>(returnType, name, std::move(parameters), std::move(body));
}

StatementPtr Parser::parseBlock()
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

StatementPtr Parser::parseReturnStatement()
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
StatementPtr Parser::parseIfStatement()
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
    StatementPtr elseBranch = nullptr;
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
StatementPtr Parser::parseForStatement()
{
    // Parse '('
    if (!match(TokenType::LeftParen))
    {
        error("Expected '(' after 'for'", peekToken());
        return nullptr;
    }

    // Parse initializer
    StatementPtr initializer = nullptr;
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
    ExpressionPtr condition = nullptr;
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
    ExpressionPtr increment = nullptr;
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
StatementPtr Parser::parseWhileStatement()
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
StatementPtr Parser::parseExpressionStatement()
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

ExpressionPtr Parser::parseMultiExpr()
{
    std::vector<ExpressionPtr> parameters;
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

ExpressionPtr Parser::parseParamExpr()
{
    std::vector<ExpressionPtr> parameters;
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

ExpressionPtr Parser::parseAssignExpr()
{
    std::vector<ExpressionPtr> parameters;
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

ExpressionPtr Parser::parseExpression()
{
    return parseEquality();
}

ExpressionPtr Parser::parseParameter()
{
    // Check if the current token is a type
    if (isType(peekToken().type))
    {
        Token typeToken = peekToken();
        std::string type = typeToken.lexeme;
        advanceToken(); // Consume the type token

        ExpressionPtr initializer = parseAssignment();
        if (!initializer)
        {
            error("Expected initializer expression", peekToken());
            return nullptr;
        }

        return std::make_unique<ParameterExpr>(type, std::move(initializer));
    }

    error("Expected type in parameter declaration", peekToken());
    return nullptr;
}

ExpressionPtr Parser::parseAssignment()
{
    auto startPos = current;
    auto expr = parsePrimary();
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
            errorMsgList.pop_back();
        }
        expr = parseEquality();
    }
    return expr;
}

ExpressionPtr Parser::parseEquality()
{
    auto startPos = current;
    auto expr = parsePrimary();
    while (match(TokenType::DoubleEquals) || match(TokenType::NotEquals))
    {
        Token oper = previousToken();
        auto right = parseEquality();
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
            errorMsgList.pop_back();
        }
        expr = parseComparison();
    }
    return expr;
}

ExpressionPtr Parser::parseComparison()
{
    auto startPos = current;
    auto expr = parsePrimary();
    while (match(TokenType::Less) || match(TokenType::LessEquals) || match(TokenType::Greater) ||
           match(TokenType::GreaterEquals))
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
            errorMsgList.pop_back();
        }
        expr = parseTerm();
    }
    return expr;
}

ExpressionPtr Parser::parseTerm()
{
    auto expr = parseFactor();
    while (match(TokenType::Plus) || match(TokenType::Minus))
    {
        Token oper = previousToken();
        auto right = parseTerm();
        if (!right)
        {
            error("Expected expression after operator", oper);
            return nullptr;
        }
        expr = std::make_unique<BinaryExpr>(oper.lexeme, std::move(expr), std::move(right));
    }
    return expr;
}

ExpressionPtr Parser::parseFactor()
{
    auto expr = parseUnaryBack();
    while (match(TokenType::Star) || match(TokenType::Slash) || match(TokenType::Percent))
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

ExpressionPtr Parser::parseUnaryBack()
{
    auto expr = parseMemberAccess();
    while (match(TokenType::Increment) || match(TokenType::Decrement))
    {
        Token oper = previousToken();
        if (!expr)
        {
            error("Expected expression before unary operator", oper);
            return nullptr;
        }
        // For simplicity, treat unary as binary with left operand as null
        expr = std::make_unique<BinaryExpr>(oper.lexeme, std::move(expr), nullptr);
    }
    return expr;
}

ExpressionPtr Parser::parseMemberAccess()
{
    auto expr = parseUnaryFront();
    if (match(TokenType::Scope))
    {
        if (!expr)
        {
            error("Expected name expression before scope", previousToken());
            return nullptr;
        }
        auto member = parseMemberAccess();
        if (!member)
        {
            error("Expected member expression after scope", previousToken());
            return nullptr;
        }
        // For simplicity, treat unary as binary with left operand as null
        expr = std::make_unique<NamespaceExpr>(std::move(expr), std::move(member));
    }
    if (match(TokenType::LeftParen))
    {
        if (!expr)
        {
            error("Expected name expression before function call", previousToken());
            return nullptr;
        }
        ExpressionPtr parameters = parseMultiExpr();
        if (!match(TokenType::RightParen))
        {
            error("Expected ')' after function call", peekToken());
            return nullptr;
        }
        return std::make_unique<FunctionCallExpr>(std::move(expr), std::move(parameters));
    }
    if (match(TokenType::LeftBracket))
    {
        if (!expr)
        {
            error("Expected expression before subscript", previousToken());
            return nullptr;
        }
        ExpressionPtr parameters = parseMultiExpr();
        if (!match(TokenType::RightBracket))
        {
            error("Expected ']' after subscript", peekToken());
            return nullptr;
        }
        return std::make_unique<SubscriptExpr>(std::move(expr), std::move(parameters));
    }
    return expr;
}

ExpressionPtr Parser::parseUnaryFront()
{
    if (match(TokenType::Exclamation) || match(TokenType::Decrement) || match(TokenType::Increment))
    {
        Token oper = previousToken();
        auto right = parseUnaryFront();
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

ExpressionPtr Parser::parsePrimary()
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
