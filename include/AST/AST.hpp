#ifndef AST_HPP
#define AST_HPP

#include <iostream>
#include <memory>
#include <string>
#include <vector>


// Forward declarations for Visitor
struct Program;
struct VariableDeclaration;
struct FunctionDeclaration;
struct Block;
struct ReturnStatement;
struct Expression;
struct Literal;
struct IdentifierExpr;
struct BinaryExpr;

// Visitor Interface
struct ASTVisitor
{
    virtual ~ASTVisitor() = default;

    virtual void visit(Program *node) = 0;
    virtual void visit(VariableDeclaration *node) = 0;
    virtual void visit(FunctionDeclaration *node) = 0;
    virtual void visit(Block *node) = 0;
    virtual void visit(ReturnStatement *node) = 0;
    virtual void visit(Literal *node) = 0;
    virtual void visit(IdentifierExpr *node) = 0;
    virtual void visit(BinaryExpr *node) = 0;
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
    std::string value;

    Literal(const std::string &val);

    void accept(ASTVisitor *visitor) override;
};

struct IdentifierExpr : Expression
{
    std::string name;

    IdentifierExpr(const std::string &n);

    void accept(ASTVisitor *visitor) override;
};

struct BinaryExpr : Expression
{
    std::string op;
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;

    BinaryExpr(const std::string &oper, std::unique_ptr<Expression> l, std::unique_ptr<Expression> r);

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
    std::string name;
    std::unique_ptr<Expression> initializer; // Optional

    VariableDeclaration(const std::string &t, const std::string &n, std::unique_ptr<Expression> init = nullptr);

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
    std::unique_ptr<Block> body;

    FunctionDeclaration(const std::string &retType, const std::string &n, const std::vector<Parameter> &params,
                        std::unique_ptr<Block> b);

    void accept(ASTVisitor *visitor) override;
};

// Block Node
struct Block : Statement
{
    std::vector<std::unique_ptr<Statement>> statements;

    Block();

    void accept(ASTVisitor *visitor) override;
};

// Return Statement Node
struct ReturnStatement : Statement
{
    std::unique_ptr<Expression> value; // Optional

    ReturnStatement(std::unique_ptr<Expression> val = nullptr);

    void accept(ASTVisitor *visitor) override;
};

// Program Node
struct Program : ASTNode
{
    std::vector<std::unique_ptr<Statement>> statements;

    void accept(ASTVisitor *visitor) override;
};

#endif // AST_HPP
