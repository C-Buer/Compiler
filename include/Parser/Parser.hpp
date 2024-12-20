#ifndef PARSER_HPP
#define PARSER_HPP

#include "AST/AST.hpp"
#include "Lexer/Lexer.hpp"
#include "Lexer/Token.hpp"
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
    bool disableError = false;
    bool extraError = false;

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
    std::unique_ptr<Statement> parseVariableStatement();
    std::unique_ptr<Statement> parseStructStatement();
    std::unique_ptr<Statement> parseFunctionStatement();
    std::unique_ptr<Statement> parseBlock();
    std::unique_ptr<Statement> parseNamespaceStatement();
    std::unique_ptr<Statement> parseImportStatement();
    std::unique_ptr<Statement> parseReturnStatement();
    std::unique_ptr<Statement> parseIfStatement();
    std::unique_ptr<Statement> parseForStatement();
    std::unique_ptr<Statement> parseWhileStatement();
    std::unique_ptr<Statement> parseExpressionStatement();
    std::unique_ptr<Statement> parseLabelStatement();
    std::unique_ptr<Statement> parseGotoStatement();
    std::unique_ptr<Expression> parseMultiExpr();
    std::unique_ptr<Expression> parseParamExpr();
    std::unique_ptr<Expression> parseAssignExpr();
    std::unique_ptr<Expression> parseExpression();
    std::unique_ptr<Expression> parseParameter();
    std::unique_ptr<Expression> parseAssignment();
    std::unique_ptr<Expression> parseEquality();
    std::unique_ptr<Expression> parseComparison();
    std::unique_ptr<Expression> parseTerm();
    std::unique_ptr<Expression> parseFactor();
    std::unique_ptr<Expression> parseUnaryBack();
    std::unique_ptr<Expression> parseUnaryFront();
    std::unique_ptr<Expression> parseSubsript();
    std::unique_ptr<Expression> parseFunctionCall();
    std::unique_ptr<Expression> parseMemberAccess();
    std::unique_ptr<Expression> parsePrimary();
    std::unique_ptr<Expression> parsePrimaryType();
    std::unique_ptr<Expression> parseNamesapce();
    std::unique_ptr<Expression> parseConstant();

    // Helper function to check if a token is a type
    bool isBaseType(TokenType type) const;
    bool isType(TokenType type) const;
};

BasicTypeExpr::BasicType TokenToBasic(TokenType token);

#endif // PARSER_HPP
