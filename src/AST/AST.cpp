#include "AST\AST.hpp"

// Literal Implementations
Literal::Literal(const std::string &val) : value(val)
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

// BinaryExpr Implementations
BinaryExpr::BinaryExpr(const std::string &oper, std::unique_ptr<Expression> l, std::unique_ptr<Expression> r)
    : op(oper), left(std::move(l)), right(std::move(r))
{
}

void BinaryExpr::accept(ASTVisitor *visitor)
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

// Program Implementations
void Program::accept(ASTVisitor *visitor)
{
    visitor->visit(this);
}