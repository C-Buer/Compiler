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

// BasicTypeExpr Implementations
BasicTypeExpr::BasicTypeExpr(BasicType t) : type(t)
{
}

void BasicTypeExpr::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

// NamespaceExpr Implementations
NamespaceExpr::NamespaceExpr(std::unique_ptr<Expression> z, std::vector<std::unique_ptr<Expression>> &n)
    : zone(std::move(z))
{
    name.reserve(n.size());
    for (auto &tmp : n)
    {
        name.push_back(std::move(tmp));
    }
}

void NamespaceExpr::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

// MemberAccessExpr Implementations
MemberAccessExpr::MemberAccessExpr(bool p, std::unique_ptr<Expression> n, std::unique_ptr<Expression> m)
    : ptr(p), name(std::move(n)), member(std::move(m))
{
}

void MemberAccessExpr::accept(ASTVisitor *visitor)
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

// ParameterExpr Implementations
ParameterExpr::ParameterExpr(std::unique_ptr<Expression> t, std::unique_ptr<Expression> r)
    : type(std::move(t)), right(std::move(r))
{
}

void ParameterExpr::accept(ASTVisitor *visitor)
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

// UnaryExpr Implementations
UnaryExpr::UnaryExpr(const std::string &oper, std::unique_ptr<Expression> val, bool is)
    : op(oper), value(std::move(val)), isFont(is)
{
}

void UnaryExpr::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

FunctionCallExpr::FunctionCallExpr(std::unique_ptr<Expression> n, std::unique_ptr<Expression> params)
    : name(std::move(n)), parameters(std::move(params))
{
}

void FunctionCallExpr::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

SubscriptExpr::SubscriptExpr(std::unique_ptr<Expression> n, std::unique_ptr<Expression> params)
    : name(std::move(n)), parameters(std::move(params))
{
}

void SubscriptExpr::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

MultiExpr::MultiExpr(std::vector<std::unique_ptr<Expression>> &params)
{
    parameters.reserve(params.size());
    for (auto &tmp : params)
    {
        parameters.push_back(std::move(tmp));
    }
}

void MultiExpr::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

BindExpr::BindExpr(std::unique_ptr<Expression> p) : param(std::move(p))
{
}

void BindExpr::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

// VariableDefinition Implementations
VariableDefinition::VariableDefinition(std::unique_ptr<Expression> t, std::unique_ptr<Expression> init)
    : type(std::move(t)), initializer(std::move(init))
{
}

void VariableDefinition::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

// StructDefinition Implementations
StructDefinition::StructDefinition(std::unique_ptr<Expression> t, std::unique_ptr<Statement> b)
    : type(std::move(t)), body(std::move(b))
{
}

void StructDefinition::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

// FunctionDeclaration Implementations
FunctionDeclaration::FunctionDeclaration(std::unique_ptr<Expression> retType, std::unique_ptr<Expression> n,
                                         std::unique_ptr<Expression> params)
    : returnType(std::move(retType)), name(std::move(n)), parameters(std::move(params))
{
}

void FunctionDeclaration::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

// FunctionDefinition Implementations
FunctionDefinition::FunctionDefinition(std::unique_ptr<Expression> retType, std::unique_ptr<Expression> n,
                                       std::unique_ptr<Expression> params, std::unique_ptr<Statement> b)
    : returnType(std::move(retType)), name(std::move(n)), parameters(std::move(params)), body(std::move(b))
{
}

void FunctionDefinition::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

// Block Implementations
Block::Block() = default;

void Block::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

// NamespaceStatement Implementations
NamespaceStatement::NamespaceStatement(std::unique_ptr<Expression> n, std::unique_ptr<Statement> b)
    : name(std::move(n)), body(std::move(b))
{
}

void NamespaceStatement::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

// ImportStatement Implementations
ImportStatement::ImportStatement(const std::string &p, std::unique_ptr<Expression> val) : path(p), value(std::move(val))
{
}

void ImportStatement::accept(ASTVisitor *visitor)
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
IfStatement::IfStatement(std::unique_ptr<Expression> cond, std::unique_ptr<Statement> thenB,
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
                           std::unique_ptr<Expression> inc, std::unique_ptr<Statement> b)
    : initializer(std::move(init)), condition(std::move(cond)), increment(std::move(inc)), body(std::move(b))
{
}

void ForStatement::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

// WhileStatement Implementations
WhileStatement::WhileStatement(std::unique_ptr<Expression> cond, std::unique_ptr<Statement> b)
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

// LabelStatement Implementations
LabelStatement::LabelStatement(std::unique_ptr<Expression> n) : name(std::move(n))
{
}

void LabelStatement::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

/*
// CaseStatement Implementations
CaseStatement::CaseStatement(std::unique_ptr<Statement> l) : label(std::move(l))
{
}

void CaseStatement::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}
*/

// GotoStatement Implementations
GotoStatement::GotoStatement(std::unique_ptr<Expression> n) : name(std::move(n))
{
}

void GotoStatement::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

// Program Implementations
void Program::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}
