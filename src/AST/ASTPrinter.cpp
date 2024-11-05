#include "AST\ASTPrinter.hpp"

// Program Node
void ASTPrinter::visit(Program *node)
{
    std::cout << "Program:\n";
    for (const auto &stmt : node->statements)
    {
        stmt->accept(this);
    }
}

// VariableDeclaration Node
void ASTPrinter::visit(VariableDeclaration *node)
{
    std::cout << "  VariableDeclaration: " << node->type << " " << node->name;
    if (node->initializer)
    {
        std::cout << " = ";
        node->initializer->accept(this);
    }
    std::cout << ";\n";
}

// FunctionDeclaration Node
void ASTPrinter::visit(FunctionDeclaration *node)
{
    std::cout << "  FunctionDeclaration: " << node->returnType << " " << node->name << "(";
    for (size_t i = 0; i < node->parameters.size(); ++i)
    {
        std::cout << node->parameters[i].type << " " << node->parameters[i].name;
        if (i < node->parameters.size() - 1)
            std::cout << ", ";
    }
    std::cout << ") {\n";
    node->body->accept(this);
    std::cout << "  }\n";
}

// Block Node
void ASTPrinter::visit(Block *node)
{
    for (const auto &stmt : node->statements)
    {
        stmt->accept(this);
    }
}

// ReturnStatement Node
void ASTPrinter::visit(ReturnStatement *node)
{
    std::cout << "    ReturnStatement: ";
    if (node->value)
    {
        node->value->accept(this);
    }
    std::cout << ";\n";
}

// Literal Node
void ASTPrinter::visit(Literal *node)
{
    std::cout << node->value;
}

// IdentifierExpr Node
void ASTPrinter::visit(IdentifierExpr *node)
{
    std::cout << node->name;
}

// BinaryExpr Node
void ASTPrinter::visit(BinaryExpr *node)
{
    if (node->left)
    {
        node->left->accept(this);
    }
    std::cout << " " << node->op << " ";
    if (node->right)
    {
        node->right->accept(this);
    }
}