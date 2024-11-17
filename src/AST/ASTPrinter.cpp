// ASTPrinter.cpp
#include "AST/ASTPrinter.hpp"
#include "AST/AST.hpp"
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

// Visit method for the VariableDefinition node
void ASTPrinter::visit(VariableDefinition *node)
{
    printIndent();
    std::cout << "VariableDefinition: ";
    node->type->accept(this);
    std::cout << " ";
    node->initializer->accept(this);
    std::cout << ";\n";
}

// Visit method for the StructDefinition node
void ASTPrinter::visit(StructDefinition *node)
{
    printIndent();
    std::cout << "StructDefinition: ";
    node->type->accept(this);
    std::cout << "\n";
    node->body->accept(this);
}

// Visit method for the FunctionDeclaration node
void ASTPrinter::visit(FunctionDeclaration *node)
{
    printIndent();
    std::cout << "FunctionDeclaration: ";
    node->returnType->accept(this);
    std::cout << " " << node->name << "(";
    node->parameters->accept(this);
    std::cout << ");\n";
}

// Visit method for the FunctionDefinition node
void ASTPrinter::visit(FunctionDefinition *node)
{
    printIndent();
    node->returnType->accept(this);
    std::cout << " " << node->name << "(";
    node->parameters->accept(this);
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

// Visit method for the NamespaceStatement node
void ASTPrinter::visit(NamespaceStatement *node)
{
    printIndent();
    std::cout << "NamespaceStatement: ";
    node->name->accept(this);
    std::cout << "\n";
    node->body->accept(this);
}

// Visit method for the ImportStatement node
void ASTPrinter::visit(ImportStatement *node)
{
    printIndent();
    std::cout << "ImportStatement: \"" << node->path;
    if (node->value)
    {
        std::cout << "\" as ";
        node->value->accept(this);
    }
    std::cout << "\";\n";
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

// Visit method for the LabelStatement node
void ASTPrinter::visit(LabelStatement *node)
{
    printIndent();
    node->name->accept(this);
    std::cout << ": \n";
}

// Visit method for the LabelCaseStatement node
void ASTPrinter::visit(LabelCaseStatement *node)
{
    printIndent();
    if (node->isCase)
    {
        std::cout << "case ";
    }
    else
    {
        std::cout << "label ";
    }
    node->label->accept(this);
}

// Visit method for the GotolStatement node
void ASTPrinter::visit(GotoStatement *node)
{
    printIndent();
    std::cout << "goto ";
    node->name->accept(this);
    std::cout << ";\n";
}

// Visit method for the Literal node
void ASTPrinter::visit(Literal *node)
{
    switch (node->value.index())
    {
    case 0:
        std::cout << std::get<int64_t>(node->value);
        break;
    case 1:
        std::cout << std::get<double>(node->value);
        break;
    case 2:
        std::cout << "\"" << std::get<std::string>(node->value) << "\"";
        break;
    case 3:
        std::cout << "'" << std::get<char>(node->value) << "'";
        break;
    case 4:
        std::cout << std::get<bool>(node->value);
        break;
    default:
        break;
    }
}

// Visit method for the IdentifierExpr node
void ASTPrinter::visit(IdentifierExpr *node)
{
    std::cout << node->name;
}

// Visit method for the BasicTypeExpr node
void ASTPrinter::visit(BasicTypeExpr *node)
{
    switch (node->type)
    {
    case BasicTypeExpr::Float:
        std::cout << "float";
        break;
    case BasicTypeExpr::Double:
        std::cout << "double";
        break;
    case BasicTypeExpr::Char:
        std::cout << "char";
        break;
    case BasicTypeExpr::Bool:
        std::cout << "bool";
        break;
    case BasicTypeExpr::Void:
        std::cout << "void";
        break;
    case BasicTypeExpr::Int64:
        std::cout << "int64";
        break;
    case BasicTypeExpr::Int32:
        std::cout << "int32";
        break;
    case BasicTypeExpr::Int16:
        std::cout << "int16";
        break;
    case BasicTypeExpr::Int8:
        std::cout << "int8";
        break;
    case BasicTypeExpr::UInt64:
        std::cout << "uint64";
        break;
    case BasicTypeExpr::UInt32:
        std::cout << "uint32";
        break;
    case BasicTypeExpr::UInt16:
        std::cout << "uint16";
        break;
    case BasicTypeExpr::UInt8:
        std::cout << "uint8";
        break;
    default:
        std::cout << "void";
        break;
    }
}

// Visit method for the NamespaceExpr node
void ASTPrinter::visit(NamespaceExpr *node)
{
    node->name->accept(this);
    std::cout << "::";
    node->member->accept(this);
}

// Visit method for the MemberAccessExpr node
void ASTPrinter::visit(MemberAccessExpr *node)
{
    node->name->accept(this);
    if (node->ptr)
    {
        std::cout << "->";
    }
    else
    {
        std::cout << ".";
    }
    node->member->accept(this);
}

// Visit method for the AssignmentExpr node
void ASTPrinter::visit(AssignmentExpr *node)
{
    node->left->accept(this);
    std::cout << " = ";
    node->right->accept(this);
}

// Visit method for the AssignmentExpr node
void ASTPrinter::visit(ParameterExpr *node)
{
    node->type->accept(this);
    std::cout << " ";
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
    node->name->accept(this);
    std::cout << "(";
    node->parameters->accept(this);
    std::cout << ")";
}

// Visit method for the SubscriptExpr node
void ASTPrinter::visit(SubscriptExpr *node)
{
    node->name->accept(this);
    std::cout << "[";
    node->parameters->accept(this);
    std::cout << "]";
}

// Visit method for the MultiExpr node
void ASTPrinter::visit(MultiExpr *node)
{
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
}
