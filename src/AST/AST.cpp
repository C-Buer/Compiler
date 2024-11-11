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

// NamespaceExpr Implementations
NamespaceExpr::NamespaceExpr(ExpressionPtr n, ExpressionPtr m) : name(std::move(n)), member(std::move(m))
{
}

void NamespaceExpr::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

// AssignmentExpr Implementations
AssignmentExpr::AssignmentExpr(ExpressionPtr l, ExpressionPtr r) : left(std::move(l)), right(std::move(r))
{
}

void AssignmentExpr::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

// ParameterExpr Implementations
ParameterExpr::ParameterExpr(const std::string &t, ExpressionPtr r) : type(t), right(std::move(r))
{
}

void ParameterExpr::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

// BinaryExpr Implementations
BinaryExpr::BinaryExpr(const std::string &oper, ExpressionPtr l, ExpressionPtr r)
    : op(oper), left(std::move(l)), right(std::move(r))
{
}

void BinaryExpr::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

FunctionCallExpr::FunctionCallExpr(ExpressionPtr n, ExpressionPtr params)
    : name(std::move(n)), parameters(std::move(params))
{
}

void FunctionCallExpr::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

SubscriptExpr::SubscriptExpr(ExpressionPtr n, ExpressionPtr params) : name(std::move(n)), parameters(std::move(params))
{
}

void SubscriptExpr::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

MultiExpr::MultiExpr(std::vector<ExpressionPtr> &params)
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

// VariableDeclaration Implementations
VariableDeclaration::VariableDeclaration(const std::string &t, ExpressionPtr init)
    : type(t), initializer(std::move(init))
{
}

void VariableDeclaration::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

// StructDeclaration Implementations
StructDeclaration::StructDeclaration(const std::string &t, ExpressionPtr b) : type(t), body(std::move(b))
{
}

void StructDeclaration::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

// FunctionDeclaration Implementations
FunctionDeclaration::FunctionDeclaration(const std::string &retType, const std::string &n, ExpressionPtr params)
    : returnType(retType), name(n), parameters(std::move(params))
{
}

void FunctionDeclaration::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

// FunctionDefinition Implementations
FunctionDefinition::FunctionDefinition(const std::string &retType, const std::string &n, ExpressionPtr params,
                                       StatementPtr b)
    : returnType(retType), name(n), parameters(std::move(params)), body(std::move(b))
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

// ReturnStatement Implementations
ReturnStatement::ReturnStatement(ExpressionPtr val) : value(std::move(val))
{
}

void ReturnStatement::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

// IfStatement Implementations
IfStatement::IfStatement(ExpressionPtr cond, StatementPtr thenB, std::unique_ptr<Statement> elseB)
    : condition(std::move(cond)), thenBranch(std::move(thenB)), elseBranch(std::move(elseB))
{
}

void IfStatement::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

// ForStatement Implementations
ForStatement::ForStatement(std::unique_ptr<Statement> init, ExpressionPtr cond, ExpressionPtr inc, StatementPtr b)
    : initializer(std::move(init)), condition(std::move(cond)), increment(std::move(inc)), body(std::move(b))
{
}

void ForStatement::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

// WhileStatement Implementations
WhileStatement::WhileStatement(ExpressionPtr cond, StatementPtr b) : condition(std::move(cond)), body(std::move(b))
{
}

void WhileStatement::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}

// ExpressionStatement Implementations
ExpressionStatement::ExpressionStatement(ExpressionPtr expr) : expression(std::move(expr))
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
