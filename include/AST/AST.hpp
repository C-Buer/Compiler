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
struct IfStatement;
struct ForStatement;
struct WhileStatement;
struct ExpressionStatement;
struct Expression;
struct Literal;
struct IdentifierExpr;
struct AssignmentExpr;
struct BinaryExpr;
struct FnCallExpr;

// Visitor Interface
struct ASTVisitor
{
    virtual ~ASTVisitor() = default;

    virtual void visit(Program *node) = 0;
    virtual void visit(VariableDeclaration *node) = 0;
    virtual void visit(FunctionDeclaration *node) = 0;
    virtual void visit(Block *node) = 0;
    virtual void visit(ReturnStatement *node) = 0;
    virtual void visit(IfStatement *node) = 0;
    virtual void visit(ForStatement *node) = 0;
    virtual void visit(WhileStatement *node) = 0;
    virtual void visit(ExpressionStatement *node) = 0;
    virtual void visit(Literal *node) = 0;
    virtual void visit(IdentifierExpr *node) = 0;
    virtual void visit(AssignmentExpr *node) = 0;
    virtual void visit(BinaryExpr *node) = 0;
    virtual void visit(FnCallExpr *node) = 0;
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

struct AssignmentExpr : Expression
{
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;

    AssignmentExpr(std::unique_ptr<Expression> l, std::unique_ptr<Expression> r);

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

struct FnCallExpr : Expression
{
    std::string name;
    std::vector<std::unique_ptr<Expression>> parameters;

    FnCallExpr(const std::string &name, std::vector<std::unique_ptr<Expression>> &params);

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

// If Statement Node
struct IfStatement : Statement
{
    std::unique_ptr<Expression> condition;
    std::unique_ptr<Block> thenBranch;
    std::unique_ptr<Statement> elseBranch; // Can be nullptr or another IfStatement

    IfStatement(std::unique_ptr<Expression> cond, std::unique_ptr<Block> thenB,
                std::unique_ptr<Statement> elseB = nullptr);

    void accept(ASTVisitor *visitor) override;
};

// For Statement Node
struct ForStatement : Statement
{
    std::unique_ptr<Statement> initializer; // VariableDeclaration or ExpressionStatement
    std::unique_ptr<Expression> condition;  // Optional
    std::unique_ptr<Expression> increment;  // Optional
    std::unique_ptr<Block> body;

    ForStatement(std::unique_ptr<Statement> init, std::unique_ptr<Expression> cond, std::unique_ptr<Expression> inc,
                 std::unique_ptr<Block> b);

    void accept(ASTVisitor *visitor) override;
};

// While Statement Node
struct WhileStatement : Statement
{
    std::unique_ptr<Expression> condition;
    std::unique_ptr<Block> body;

    WhileStatement(std::unique_ptr<Expression> cond, std::unique_ptr<Block> b);

    void accept(ASTVisitor *visitor) override;
};

// Expression Statement Node
struct ExpressionStatement : Statement
{
    std::unique_ptr<Expression> expression;

    ExpressionStatement(std::unique_ptr<Expression> expr);

    void accept(ASTVisitor *visitor) override;
};

// Program Node
struct Program : ASTNode
{
    std::vector<std::unique_ptr<Statement>> statements;

    void accept(ASTVisitor *visitor) override;
};

#endif // AST_HPP
