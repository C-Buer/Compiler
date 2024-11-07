// ASTPrinter.cpp
#include "AST/ASTPrinter.hpp"
#include <iostream>

// Constructor initializes the indentation level to zero
ASTPrinter::ASTPrinter() : indentLevel(0)
{
}

// Helper function to print spaces based on the current indentation level
void ASTPrinter::printIndent()
{
    for (int i = 0; i < indentLevel * indentSize; ++i)
    {
        std::cout << ' ';
    }
}

// Visit method for the Program node
void ASTPrinter::visit(Program *node)
{
    std::cout << "Program:\n";
    indentLevel++;
    for (const auto &stmt : node->statements)
    {
        stmt->accept(this);
    }
    indentLevel--;
}

// Visit method for the VariableDeclaration node
void ASTPrinter::visit(VariableDeclaration *node)
{
    printIndent();
    std::cout << "VariableDeclaration: " << node->type << " " << node->name;
    if (node->initializer)
    {
        std::cout << " = ";
        node->initializer->accept(this);
    }
    std::cout << ";\n";
}

// Visit method for the FunctionDeclaration node
void ASTPrinter::visit(FunctionDeclaration *node)
{
    printIndent();
    std::cout << "FunctionDeclaration: " << node->returnType << " " << node->name << "(";
    for (size_t i = 0; i < node->parameters.size(); ++i)
    {
        std::cout << node->parameters[i].type << " " << node->parameters[i].name;
        if (i < node->parameters.size() - 1)
            std::cout << ", ";
    }
    std::cout << ")\n";
    node->body->accept(this);
}

// Visit method for the Block node
void ASTPrinter::visit(Block *node)
{
    printIndent();
    std::cout << "{\n";
    indentLevel++;
    for (const auto &stmt : node->statements)
    {
        stmt->accept(this);
    }
    indentLevel--;
    printIndent();
    std::cout << "}\n";
}

// Visit method for the ReturnStatement node
void ASTPrinter::visit(ReturnStatement *node)
{
    printIndent();
    std::cout << "ReturnStatement: ";
    if (node->value)
    {
        node->value->accept(this);
    }
    std::cout << ";\n";
}

// Visit method for the IfStatement node
void ASTPrinter::visit(IfStatement *node)
{
    printIndent();
    std::cout << "IfStatement:\n";
    indentLevel++;

    // Condition
    printIndent();
    std::cout << "Condition: ";
    node->condition->accept(this);
    std::cout << "\n";

    // Then Branch
    printIndent();
    std::cout << "Then:\n";
    node->thenBranch->accept(this);

    // Else Branch
    if (node->elseBranch)
    {
        printIndent();
        std::cout << "Else:\n";
        node->elseBranch->accept(this);
    }

    indentLevel--;
}

// Visit method for the ForStatement node
void ASTPrinter::visit(ForStatement *node)
{
    printIndent();
    std::cout << "ForStatement:\n";
    indentLevel++;

    // Initializer
    if (node->initializer)
    {
        printIndent();
        std::cout << "Initializer:\n";
        indentLevel++;
        node->initializer->accept(this);
        indentLevel--;
    }

    // Condition
    if (node->condition)
    {
        printIndent();
        std::cout << "Condition: ";
        node->condition->accept(this);
        std::cout << "\n";
    }

    // Increment
    if (node->increment)
    {
        printIndent();
        std::cout << "Increment: ";
        node->increment->accept(this);
        std::cout << "\n";
    }

    // Body
    printIndent();
    std::cout << "Body:\n";
    node->body->accept(this);

    indentLevel--;
}

// Visit method for the WhileStatement node
void ASTPrinter::visit(WhileStatement *node)
{
    printIndent();
    std::cout << "WhileStatement:\n";
    indentLevel++;

    // Condition
    printIndent();
    std::cout << "Condition: ";
    node->condition->accept(this);
    std::cout << "\n";

    // Body
    printIndent();
    std::cout << "Body:\n";
    node->body->accept(this);

    indentLevel--;
}

// Visit method for the ExpressionStatement node
void ASTPrinter::visit(ExpressionStatement *node)
{
    printIndent();
    std::cout << "ExpressionStatement: ";
    node->expression->accept(this);
    std::cout << ";\n";
}

// Visit method for the Literal node
void ASTPrinter::visit(Literal *node)
{
    std::cout << node->value;
}

// Visit method for the IdentifierExpr node
void ASTPrinter::visit(IdentifierExpr *node)
{
    std::cout << node->name;
}

// Visit method for the AssignmentExpr node
void ASTPrinter::visit(AssignmentExpr *node)
{
    node->left->accept(this);
    std::cout << " = ";
    node->right->accept(this);
}

// Visit method for the BinaryExpr node
void ASTPrinter::visit(BinaryExpr *node)
{
    std::cout << "(";
    if (node->left)
    {
        node->left->accept(this);
    }
    std::cout << " " << node->op << " ";
    if (node->right)
    {
        node->right->accept(this);
    }
    std::cout << ")";
}

// Visit method for the FunctionCallExpr node
void ASTPrinter::visit(FunctionCallExpr *node)
{
    std::cout << node->name << "(";
    for (auto it = node->parameters.begin(); it != node->parameters.end(); it++)
    {
        if (it + 1 == node->parameters.end())
        {
            (**it).accept(this);
        }
        else
        {
            (**it).accept(this);
            std::cout << ", ";
        }
    }
    std::cout << ")";
}
