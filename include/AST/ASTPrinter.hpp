#ifndef AST_PRINTER_HPP
#define AST_PRINTER_HPP

#include "AST.hpp"

// ASTPrinter: A concrete visitor to print the AST
struct ASTPrinter : ASTVisitor
{
    void visit(Program *node) override;
    void visit(VariableDeclaration *node) override;
    void visit(FunctionDeclaration *node) override;
    void visit(Block *node) override;
    void visit(ReturnStatement *node) override;
    void visit(Literal *node) override;
    void visit(IdentifierExpr *node) override;
    void visit(BinaryExpr *node) override;
    // Implement additional visit methods for other AST nodes as needed
};

#endif // AST_PRINTER_HPP
