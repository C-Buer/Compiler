#ifndef AST_HPP
#define AST_HPP

#include <iostream>
#include <memory>
#include <string>
#include <variant>
#include <vector>

// Forward declarations for Visitor
struct Program;
struct Statement;
struct VariableDeclaration;
struct FunctionDeclaration;
struct FunctionDefinition;
struct Block;
struct ReturnStatement;
struct IfStatement;
struct ForStatement;
struct WhileStatement;
struct ExpressionStatement;
struct Expression;
struct Literal;
struct IdentifierExpr;
struct NamespaceExpr;
struct AssignmentExpr;
struct BinaryExpr;
struct FunctionCallExpr;
struct SubscriptExpr;
struct MultiExpr;

using ExpressionPtr = std::unique_ptr<Expression>;
using StatementPtr = std::unique_ptr<Statement>;

// Visitor Interface
struct ASTVisitor
{
    virtual ~ASTVisitor() = default;

    virtual void visit(Program *node) = 0;
    virtual void visit(VariableDeclaration *node) = 0;
    virtual void visit(FunctionDeclaration *node) = 0;
    virtual void visit(FunctionDefinition *node) = 0;
    virtual void visit(Block *node) = 0;
    virtual void visit(ReturnStatement *node) = 0;
    virtual void visit(IfStatement *node) = 0;
    virtual void visit(ForStatement *node) = 0;
    virtual void visit(WhileStatement *node) = 0;
    virtual void visit(ExpressionStatement *node) = 0;
    virtual void visit(Literal *node) = 0;
    virtual void visit(IdentifierExpr *node) = 0;
    virtual void visit(NamespaceExpr *node) = 0;
    virtual void visit(AssignmentExpr *node) = 0;
    virtual void visit(BinaryExpr *node) = 0;
    virtual void visit(FunctionCallExpr *node) = 0;
    virtual void visit(SubscriptExpr *node) = 0;
    virtual void visit(MultiExpr *node) = 0;
    // Add more visit methods for additional AST nodes as needed
};

// Base class for all AST nodes
struct ASTNode
{
    virtual ~ASTNode() = default;
    virtual void accept(ASTVisitor *visitor) = 0;
};

// Expression Nodes
struct Expression : ASTNode
{
    // Base class for all expressions
};

struct Literal : Expression
{
    std::variant<int64_t, double, std::string, char, bool> value;

    Literal(const std::variant<int64_t, double, std::string, char, bool> &val);

    void accept(ASTVisitor *visitor) override;
};

struct IdentifierExpr : Expression
{
    std::string name;

    IdentifierExpr(const std::string &n);

    void accept(ASTVisitor *visitor) override;
};

struct NamespaceExpr : Expression
{
    ExpressionPtr name;
    ExpressionPtr member;

    NamespaceExpr(ExpressionPtr n, ExpressionPtr m);

    void accept(ASTVisitor *visitor) override;
};

struct AssignmentExpr : Expression
{
    ExpressionPtr left;
    ExpressionPtr right;

    AssignmentExpr(ExpressionPtr l, ExpressionPtr r);

    void accept(ASTVisitor *visitor) override;
};

struct BinaryExpr : Expression
{
    std::string op;
    ExpressionPtr left;
    ExpressionPtr right;

    BinaryExpr(const std::string &oper, ExpressionPtr l, ExpressionPtr r);

    void accept(ASTVisitor *visitor) override;
};

struct FunctionCallExpr : Expression
{
    ExpressionPtr name;
    ExpressionPtr parameters;

    FunctionCallExpr(ExpressionPtr n, ExpressionPtr params);

    void accept(ASTVisitor *visitor) override;
};

struct SubscriptExpr : Expression
{
    ExpressionPtr name;
    ExpressionPtr parameters;

    SubscriptExpr(ExpressionPtr n, ExpressionPtr params);

    void accept(ASTVisitor *visitor) override;
};

struct MultiExpr : Expression
{
    std::vector<ExpressionPtr> parameters;

    MultiExpr(std::vector<ExpressionPtr> &params);

    void accept(ASTVisitor *visitor) override;
};

// Statement Nodes
struct Statement : ASTNode
{
    // Base class for all statements
};

struct VariableDeclaration : Statement
{
    std::string type;
    ExpressionPtr initializer;

    VariableDeclaration(const std::string &t, ExpressionPtr init = nullptr);

    void accept(ASTVisitor *visitor) override;
};

// Parameter structure
struct Parameter
{
    std::string type;
    std::string name;

    Parameter(const std::string &t, const std::string &n);
};

// Function Declaration Node
struct FunctionDeclaration : Statement
{
    std::string returnType;
    std::string name;
    std::vector<Parameter> parameters;

    FunctionDeclaration(const std::string &retType, const std::string &n, const std::vector<Parameter> &params);

    void accept(ASTVisitor *visitor) override;
};

// Function Definition Node
struct FunctionDefinition : Statement
{
    std::string returnType;
    std::string name;
    std::vector<Parameter> parameters;
    std::unique_ptr<Block> body;

    FunctionDefinition(const std::string &retType, const std::string &n, const std::vector<Parameter> &params,
                       std::unique_ptr<Block> b);

    void accept(ASTVisitor *visitor) override;
};

// Block Node
struct Block : Statement
{
    std::vector<StatementPtr> statements;

    Block();

    void accept(ASTVisitor *visitor) override;
};

// Return Statement Node
struct ReturnStatement : Statement
{
    ExpressionPtr value; // Optional

    ReturnStatement(ExpressionPtr val = nullptr);

    void accept(ASTVisitor *visitor) override;
};

// If Statement Node
struct IfStatement : Statement
{
    ExpressionPtr condition;
    std::unique_ptr<Block> thenBranch;
    StatementPtr elseBranch; // Can be nullptr or another IfStatement

    IfStatement(ExpressionPtr cond, std::unique_ptr<Block> thenB, StatementPtr elseB = nullptr);

    void accept(ASTVisitor *visitor) override;
};

// For Statement Node
struct ForStatement : Statement
{
    StatementPtr initializer; // VariableDeclaration or ExpressionStatement
    ExpressionPtr condition;  // Optional
    ExpressionPtr increment;  // Optional
    std::unique_ptr<Block> body;

    ForStatement(StatementPtr init, ExpressionPtr cond, ExpressionPtr inc, std::unique_ptr<Block> b);

    void accept(ASTVisitor *visitor) override;
};

// While Statement Node
struct WhileStatement : Statement
{
    ExpressionPtr condition;
    std::unique_ptr<Block> body;

    WhileStatement(ExpressionPtr cond, std::unique_ptr<Block> b);

    void accept(ASTVisitor *visitor) override;
};

// Expression Statement Node
struct ExpressionStatement : Statement
{
    ExpressionPtr expression;

    ExpressionStatement(ExpressionPtr expr);

    void accept(ASTVisitor *visitor) override;
};

// Program Node
struct Program : ASTNode
{
    std::vector<StatementPtr> statements;

    void accept(ASTVisitor *visitor) override;
};

#endif // AST_HPP
