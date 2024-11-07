#ifndef PARSER_HPP
#define PARSER_HPP

#include "AST/AST.hpp"
#include "Lexer/Lexer.hpp"
#include <memory>
#include <vector>

class Parser
{
  public:
    Parser(const std::vector<Token> &tokens);
    std::unique_ptr<Program> parse();

  private:
    const std::vector<Token> &tokens;
    size_t current = 0;

    // Utility functions
    bool match(TokenType type);
    bool check(TokenType type) const;
    Token advanceToken();
    Token peekToken() const;
    Token previousToken() const;
    bool isAtEnd() const;
    void error(const std::string &message, const Token &token);

    // Parsing functions
    std::unique_ptr<Statement> parseStatement();
    std::unique_ptr<VariableDeclaration> parseVariableDeclaration();
    std::unique_ptr<FunctionDeclaration> parseFunctionDeclaration();
    std::unique_ptr<ReturnStatement> parseReturnStatement();
    std::unique_ptr<IfStatement> parseIfStatement();       // Declared parseIfStatement
    std::unique_ptr<ForStatement> parseForStatement();     // Declared parseForStatement
    std::unique_ptr<WhileStatement> parseWhileStatement(); // Declared parseWhileStatement
    std::unique_ptr<Expression> parseExpression();
    std::unique_ptr<Expression> parseAssignment();
    std::unique_ptr<Expression> parseEquality();
    std::unique_ptr<Expression> parseComparison();
    std::unique_ptr<Expression> parseTerm();
    std::unique_ptr<Expression> parseFactor();
    std::unique_ptr<Expression> parseUnary();
    std::unique_ptr<Expression> parsePrimary();
    std::unique_ptr<Block> parseBlock();
    std::unique_ptr<Statement> parseExpressionStatement(); // Added parseExpressionStatement

    // Helper function to check if a token is a type
    bool isBaseType(TokenType type) const;
    bool isType(TokenType type) const;
    bool isValid(TokenType type) const;
};

#endif // PARSER_HPP
