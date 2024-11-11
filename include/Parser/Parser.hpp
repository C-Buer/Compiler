#ifndef PARSER_HPP
#define PARSER_HPP

#include "AST/AST.hpp"
#include "Lexer/Lexer.hpp"
#include <format>
#include <iostream>
#include <list>
#include <memory>
#include <vector>

class Parser
{
  public:
    Parser(const std::vector<Token> &tokens);
    std::unique_ptr<Program> parse();
    bool printErrorMsg();

  private:
    const std::vector<Token> &tokens;
    size_t current = 0;

    std::list<std::string> errorMsgList;

    // Utility functions
    bool match(TokenType type);
    bool check(TokenType type) const;
    Token advanceToken();
    Token peekToken() const;
    Token previousToken() const;
    bool isAtEnd() const;
    void error(const std::string &message, const Token &token);

    // Parsing functions
    StatementPtr parseStatement();
    StatementPtr parseVariableDeclaration();
    StatementPtr parseFunctionDeclaration();
    StatementPtr parseReturnStatement();
    StatementPtr parseIfStatement();
    StatementPtr parseForStatement();
    StatementPtr parseWhileStatement();
    StatementPtr parseExpressionStatement();
    ExpressionPtr parseMultiExpr();
    ExpressionPtr parseParamExpr();
    ExpressionPtr parseExpression();
    ExpressionPtr parseParameter();
    ExpressionPtr parseAssignment();
    ExpressionPtr parseEquality();
    ExpressionPtr parseComparison();
    ExpressionPtr parseTerm();
    ExpressionPtr parseFactor();
    ExpressionPtr parseUnaryBack();
    ExpressionPtr parseMemberAccess();
    ExpressionPtr parseUnaryFront();
    ExpressionPtr parsePrimary();
    std::unique_ptr<Block> parseBlock();

    // Helper function to check if a token is a type
    bool isBaseType(TokenType type) const;
    bool isType(TokenType type) const;
};

#endif // PARSER_HPP
