#pragma once
#include "scripting/sigflx_script_ast_node.h"

namespace SignumFlux
{
namespace Script
{
class ASTVisitor
{
public:
    virtual ~ASTVisitor() = default;

    virtual void visit(IntegerLiteral& node) = 0;
    virtual void visit(FloatLiteral& node) = 0;
    virtual void visit(BoolLiteral& node) = 0;
    virtual void visit(StringLiteral& node) = 0;
    virtual void visit(Identifier& node) = 0;
    virtual void visit(BinaryExpression& node) = 0;
    virtual void visit(FunctionCall& node) = 0;
    
    virtual void visit(VariableDeclaration& node) = 0;
    virtual void visit(ExpressionStatement& node) = 0;
    virtual void visit(IfStatement& node) = 0;
    virtual void visit(BlockStatement& node) = 0;
};

class ASTPrinter : public ASTVisitor
{
public:
    ~ASTPrinter() = default;

    void visit(IntegerLiteral & node) override;
    void visit(FloatLiteral & node) override;
    void visit(BoolLiteral & node) override;
};
}
}