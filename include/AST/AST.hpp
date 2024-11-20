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
struct VariableDefinition;
struct StructDefinition;
struct FunctionDeclaration;
struct FunctionDefinition;
struct Block;
struct NamespaceStatement;
struct ImportStatement;
struct IfStatement;
struct ForStatement;
struct WhileStatement;
struct ReturnStatement;
struct ExpressionStatement;
struct LabelStatement;
struct CaseStatement;
struct GotoStatement;
struct Expression;
struct Literal;
struct IdentifierExpr;
struct BasicTypeExpr;
struct NamespaceExpr;
struct MemberAccessExpr;
struct AssignmentExpr;
struct ParameterExpr;
struct BinaryExpr;
struct FunctionCallExpr;
struct SubscriptExpr;
struct MultiExpr;
struct BindExpr;

// Visitor Interface
struct ASTVisitor
{
    virtual ~ASTVisitor() = default;

    virtual void visit(Program *node) = 0;
    virtual void visit(VariableDefinition *node) = 0;
    virtual void visit(StructDefinition *node) = 0;
    virtual void visit(FunctionDeclaration *node) = 0;
    virtual void visit(FunctionDefinition *node) = 0;
    virtual void visit(Block *node) = 0;
    virtual void visit(NamespaceStatement *node) = 0;
    virtual void visit(ImportStatement *node) = 0;
    virtual void visit(ReturnStatement *node) = 0;
    virtual void visit(IfStatement *node) = 0;
    virtual void visit(ForStatement *node) = 0;
    virtual void visit(WhileStatement *node) = 0;
    virtual void visit(ExpressionStatement *node) = 0;
    virtual void visit(LabelStatement *node) = 0;
    virtual void visit(CaseStatement *node) = 0;
    virtual void visit(GotoStatement *node) = 0;
    virtual void visit(Literal *node) = 0;
    virtual void visit(IdentifierExpr *node) = 0;
    virtual void visit(BasicTypeExpr *node) = 0;
    virtual void visit(NamespaceExpr *node) = 0;
    virtual void visit(MemberAccessExpr *node) = 0;
    virtual void visit(AssignmentExpr *node) = 0;
    virtual void visit(ParameterExpr *node) = 0;
    virtual void visit(BinaryExpr *node) = 0;
    virtual void visit(FunctionCallExpr *node) = 0;
    virtual void visit(SubscriptExpr *node) = 0;
    virtual void visit(MultiExpr *node) = 0;
    virtual void visit(BindExpr *node) = 0;
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

struct BasicTypeExpr : Expression
{
    enum BasicType
    {
        Float,
        Double,
        Char,
        Bool,
        Void,
        Int64,
        Int32,
        Int16,
        Int8,
        UInt64,
        UInt32,
        UInt16,
        UInt8
    } type;

    BasicTypeExpr(BasicType t);

    void accept(ASTVisitor *visitor) override;
};

struct NamespaceExpr : Expression
{
    std::unique_ptr<Expression> zone;
    std::vector<std::unique_ptr<Expression>> name;

    NamespaceExpr(std::unique_ptr<Expression> z, std::vector<std::unique_ptr<Expression>> &n);

    void accept(ASTVisitor *visitor) override;
};

struct MemberAccessExpr : Expression
{
    bool ptr;
    std::unique_ptr<Expression> name;
    std::unique_ptr<Expression> member;

    MemberAccessExpr(bool ptr, std::unique_ptr<Expression> n, std::unique_ptr<Expression> m);

    void accept(ASTVisitor *visitor) override;
};

struct AssignmentExpr : Expression
{
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;

    AssignmentExpr(std::unique_ptr<Expression> l, std::unique_ptr<Expression> r);

    void accept(ASTVisitor *visitor) override;
};

struct ParameterExpr : Expression
{
    std::unique_ptr<Expression> type;
    std::unique_ptr<Expression> right;

    ParameterExpr(std::unique_ptr<Expression> t, std::unique_ptr<Expression> r);

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

struct FunctionCallExpr : Expression
{
    std::unique_ptr<Expression> name;
    std::unique_ptr<Expression> parameters;

    FunctionCallExpr(std::unique_ptr<Expression> n, std::unique_ptr<Expression> params);

    void accept(ASTVisitor *visitor) override;
};

struct SubscriptExpr : Expression
{
    std::unique_ptr<Expression> name;
    std::unique_ptr<Expression> parameters;

    SubscriptExpr(std::unique_ptr<Expression> n, std::unique_ptr<Expression> params);

    void accept(ASTVisitor *visitor) override;
};

struct MultiExpr : Expression
{
    std::vector<std::unique_ptr<Expression>> parameters;

    MultiExpr(std::vector<std::unique_ptr<Expression>> &params);

    void accept(ASTVisitor *visitor) override;
};

struct BindExpr : Expression
{
    std::unique_ptr<Expression> param;

    BindExpr(std::unique_ptr<Expression> p);

    void accept(ASTVisitor *visitor) override;
};

// Statement Nodes
struct Statement : ASTNode
{
    // Base class for all statements
};

// Variable Declaration Node
struct VariableDefinition : Statement
{
    std::unique_ptr<Expression> type;
    std::unique_ptr<Expression> initializer;

    VariableDefinition(std::unique_ptr<Expression> t, std::unique_ptr<Expression> init = nullptr);

    void accept(ASTVisitor *visitor) override;
};

// Struct Declaration Node
struct StructDefinition : Statement
{
    std::unique_ptr<Expression> type;
    std::unique_ptr<Statement> body;

    StructDefinition(std::unique_ptr<Expression>, std::unique_ptr<Statement> b = nullptr);

    void accept(ASTVisitor *visitor) override;
};

// Function Declaration Node
struct FunctionDeclaration : Statement
{
    std::unique_ptr<Expression> returnType;
    std::string name;
    std::unique_ptr<Expression> parameters;

    FunctionDeclaration(std::unique_ptr<Expression> retType, const std::string &n, std::unique_ptr<Expression> params);

    void accept(ASTVisitor *visitor) override;
};

// Function Definition Node
struct FunctionDefinition : Statement
{
    std::unique_ptr<Expression> returnType;
    std::string name;
    std::unique_ptr<Expression> parameters;
    std::unique_ptr<Statement> body;

    FunctionDefinition(std::unique_ptr<Expression> retType, const std::string &n, std::unique_ptr<Expression> params,
                       std::unique_ptr<Statement> b);

    void accept(ASTVisitor *visitor) override;
};

// Block Node
struct Block : Statement
{
    std::vector<std::unique_ptr<Statement>> statements;

    Block();

    void accept(ASTVisitor *visitor) override;
};

// Namespace Statement Node
struct NamespaceStatement : Statement
{
    std::unique_ptr<Expression> name;
    std::unique_ptr<Statement> body;

    NamespaceStatement(std::unique_ptr<Expression> n, std::unique_ptr<Statement> b);

    void accept(ASTVisitor *visitor) override;
};

// Import Statement Node
struct ImportStatement : Statement
{
    std::string path;
    std::unique_ptr<Expression> value; // Optional

    ImportStatement(const std::string &p, std::unique_ptr<Expression> val = nullptr);

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
    std::unique_ptr<Statement> thenBranch;
    std::unique_ptr<Statement> elseBranch; // Can be nullptr or another IfStatement

    IfStatement(std::unique_ptr<Expression> cond, std::unique_ptr<Statement> thenB,
                std::unique_ptr<Statement> elseB = nullptr);

    void accept(ASTVisitor *visitor) override;
};

// For Statement Node
struct ForStatement : Statement
{
    std::unique_ptr<Statement> initializer; // VariableDefinition or ExpressionStatement
    std::unique_ptr<Expression> condition;  // Optional
    std::unique_ptr<Expression> increment;  // Optional
    std::unique_ptr<Statement> body;

    ForStatement(std::unique_ptr<Statement> init, std::unique_ptr<Expression> cond, std::unique_ptr<Expression> inc,
                 std::unique_ptr<Statement> b);

    void accept(ASTVisitor *visitor) override;
};

// While Statement Node
struct WhileStatement : Statement
{
    std::unique_ptr<Expression> condition;
    std::unique_ptr<Statement> body;

    WhileStatement(std::unique_ptr<Expression> cond, std::unique_ptr<Statement> b);

    void accept(ASTVisitor *visitor) override;
};

// Expression Statement Node
struct ExpressionStatement : Statement
{
    std::unique_ptr<Expression> expression;

    ExpressionStatement(std::unique_ptr<Expression> expr);

    void accept(ASTVisitor *visitor) override;
};

// Label Statement Node
struct LabelStatement : Statement
{
    std::unique_ptr<Expression> name;

    LabelStatement(std::unique_ptr<Expression> n);

    void accept(ASTVisitor *visitor) override;
};

// LabelCase Statement Node
struct CaseStatement : Statement
{
    std::unique_ptr<Statement> label;

    CaseStatement(std::unique_ptr<Statement> l);

    void accept(ASTVisitor *visitor) override;
};

// Goto Statement Node
struct GotoStatement : Statement
{
    std::unique_ptr<Expression> name;

    GotoStatement(std::unique_ptr<Expression> n);

    void accept(ASTVisitor *visitor) override;
};

// Program Node
struct Program : ASTNode
{
    std::vector<std::unique_ptr<Statement>> statements;

    void accept(ASTVisitor *visitor) override;
};

#endif // AST_HPP
