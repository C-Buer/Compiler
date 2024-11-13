// ASTPrinter.hpp
#ifndef AST_PRINTER_HPP
#define AST_PRINTER_HPP

#include "AST.hpp"

// ASTPrinter: A concrete visitor to print the AST in Microsoft style with proper indentation
struct ASTPrinter : ASTVisitor
{
    ASTPrinter();

    // Override visit methods for each AST node type
    void visit(Program *node) override;
    void visit(VariableDefinition *node) override;
    void visit(StructDefinition *node) override;
    void visit(FunctionDeclaration *node) override;
    void visit(FunctionDefinition *node) override;
    void visit(Block *node) override;
    void visit(LabelStatement *node) override;
    void visit(LabelCaseStatement *node) override;
    void visit(GotoStatement *node) override;
    void visit(IfStatement *node) override;
    void visit(ForStatement *node) override;
    void visit(WhileStatement *node) override;
    void visit(ReturnStatement *node) override;
    void visit(ExpressionStatement *node) override;
    void visit(Literal *node) override;
    void visit(IdentifierExpr *node) override;
    void visit(BasicTypeExpr *node) override;
    void visit(NamespaceExpr *node) override;
    void visit(MemberAccessExpr *node) override;
    void visit(AssignmentExpr *node) override;
    void visit(ParameterExpr *node) override;
    void visit(BinaryExpr *node) override;
    void visit(FunctionCallExpr *node) override;
    void visit(SubscriptExpr *node) override;
    void visit(MultiExpr *node) override;

  private:
    int indentLevel;          // Current indentation level
    const int indentSize = 4; // Number of spaces per indentation level

    // Helper function to print the current indentation
    void printIndent();
};

#endif // AST_PRINTER_HPP
