#include "AST/AST.hpp"
#include <utility>

// Literal Implementations
Literal::Literal(const std::variant<int64_t, double, std::string, char, bool> &val) : value(val)
{
}

void Literal::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

// IdentifierExpr Implementations
IdentifierExpr::IdentifierExpr(const std::string &n) : name(n)
{
}

void IdentifierExpr::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

// AssignmentExpr Implementations
AssignmentExpr::AssignmentExpr(std::unique_ptr<Expression> l, std::unique_ptr<Expression> r)
    : left(std::move(l)), right(std::move(r))
{
}

void AssignmentExpr::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

// BinaryExpr Implementations
BinaryExpr::BinaryExpr(const std::string &oper, std::unique_ptr<Expression> l, std::unique_ptr<Expression> r)
    : op(oper), left(std::move(l)), right(std::move(r))
{
}

void BinaryExpr::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

FunctionCallExpr::FunctionCallExpr(const std::string &n, std::vector<std::unique_ptr<Expression>> &params) : name(n)
{
    parameters.reserve(params.size());
    for (auto &tmp : params)
    {
        parameters.push_back(std::move(tmp));
    }
}

void FunctionCallExpr::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

// VariableDeclaration Implementations
VariableDeclaration::VariableDeclaration(const std::string &t, const std::string &n, std::unique_ptr<Expression> init)
    : type(t), name(n), initializer(std::move(init))
{
}

void VariableDeclaration::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

// Parameter Implementations
Parameter::Parameter(const std::string &t, const std::string &n) : type(t), name(n)
{
}

// FunctionDeclaration Implementations
FunctionDeclaration::FunctionDeclaration(const std::string &retType, const std::string &n,
                                         const std::vector<Parameter> &params, std::unique_ptr<Block> b)
    : returnType(retType), name(n), parameters(params), body(std::move(b))
{
}

void FunctionDeclaration::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

// Block Implementations
Block::Block() = default;

void Block::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

// ReturnStatement Implementations
ReturnStatement::ReturnStatement(std::unique_ptr<Expression> val) : value(std::move(val))
{
}

void ReturnStatement::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

// IfStatement Implementations
IfStatement::IfStatement(std::unique_ptr<Expression> cond, std::unique_ptr<Block> thenB,
                         std::unique_ptr<Statement> elseB)
    : condition(std::move(cond)), thenBranch(std::move(thenB)), elseBranch(std::move(elseB))
{
}

void IfStatement::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

// ForStatement Implementations
ForStatement::ForStatement(std::unique_ptr<Statement> init, std::unique_ptr<Expression> cond,
                           std::unique_ptr<Expression> inc, std::unique_ptr<Block> b)
    : initializer(std::move(init)), condition(std::move(cond)), increment(std::move(inc)), body(std::move(b))
{
}

void ForStatement::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

// WhileStatement Implementations
WhileStatement::WhileStatement(std::unique_ptr<Expression> cond, std::unique_ptr<Block> b)
    : condition(std::move(cond)), body(std::move(b))
{
}

void WhileStatement::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

// ExpressionStatement Implementations
ExpressionStatement::ExpressionStatement(std::unique_ptr<Expression> expr) : expression(std::move(expr))
{
}

void ExpressionStatement::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

// Program Implementations
void Program::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}
