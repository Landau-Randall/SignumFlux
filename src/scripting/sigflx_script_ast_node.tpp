#include "scripting/sigflx_script_ast_node.h"

namespace SignumFlux
{
namespace Script
{
void IntegerLiteral::acceptImpl(ASTVisitor& visitor) {
    visitor.visit(*this);
}

void FloatLiteral::acceptImpl(ASTVisitor& visitor) {
    visitor.visit(*this);
}

void BoolLiteral::acceptImpl(ASTVisitor& visitor) {
    visitor.visit(*this);
}

void StringLiteral::acceptImpl(ASTVisitor& visitor) {
    visitor.visit(*this);
}

void Identifier::acceptImpl(ASTVisitor& visitor) {
    visitor.visit(*this);
}

void BinaryExpression::acceptImpl(ASTVisitor& visitor) {
    visitor.visit(*this);
}

void FunctionCall::acceptImpl(ASTVisitor& visitor) {
    visitor.visit(*this);
}

void VariableDeclaration::acceptImpl(ASTVisitor& visitor) {
    visitor.visit(*this);
}

void ExpressionStatement::acceptImpl(ASTVisitor& visitor) {
    visitor.visit(*this);
}

void IfStatement::acceptImpl(ASTVisitor& visitor) {
    visitor.visit(*this);
}

void BlockStatement::acceptImpl(ASTVisitor& visitor) {
    visitor.visit(*this);
}
}
}