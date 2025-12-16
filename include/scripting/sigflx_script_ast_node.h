#pragma once

#include <cstddef>

namespace SignumFlux
{
namespace Script
{
enum class VariableType
{
    UNKNOWN,
    INTEGER,
    FLOAT,
    BOOL,
    STRING
};

enum class BinaryOperatorType
{
    PLUS, 
    MINUS,
    MULTIPLY,
    DIVIDE,

    EQUAL,
    NOT_EQUAL,
    GREATER_THAN,
    GREATER_EQUAL,
    LESS_THAN,
    LESS_EQUAL
};

template<typename Derived>
class ASTNode
{
protected:
    virtual void acceptImpl(ASTVisitor & visitor) = 0;
public:
    virtual ~ASTNode() = default;
    void accept(class ASTVisitor& visitor)
    {
        static_cast<Derived*>(this)->acceptImpl(visitor);
    };
};

class ExpressionBase
{
public:
    virtual ~ExpressionBase() = default;
    virtual void accept(ASTVisitor& visitor) = 0;
};

template<typename ExpressionDerived>
class Expression : public ASTNode<ExpressionDerived>, public ExpressionBase
{
public:
    virtual ~Expression() = default;
    void accept(ASTVisitor & visitor) override
    {
        ASTNode<ExpressionDerived>::accept(visitor);
    }
};

class IntegerLiteral : public Expression<IntegerLiteral>
{
protected:
    void acceptImpl(ASTVisitor & visitor) override;
public:
    long long value_;
    static constexpr VariableType type_ = VariableType::INTEGER;
    IntegerLiteral(long long value) : value_(value) {};
};

class FloatLiteral : public Expression<FloatLiteral>
{
protected:
    void acceptImpl(ASTVisitor & visitor) override;
public:
    double value_;
    static constexpr VariableType type_ = VariableType::FLOAT;
    FloatLiteral(double value) : value_(value) {};  
};

class BoolLiteral : public Expression<BoolLiteral>
{
protected:
    void acceptImpl(ASTVisitor & visitor) override;
public:
    bool value_;
    static constexpr VariableType type_ = VariableType::BOOL;
    BoolLiteral(bool value) : value_(value) {};
};

class StringLiteral : public Expression<StringLiteral>
{
protected:
    void acceptImpl(ASTVisitor & visitor) override;
public: 
    const char * value_ = nullptr;
    std::size_t valueLength_= 0;
    static constexpr VariableType type_ = VariableType::STRING;
    StringLiteral(const char * value,std::size_t valueLength) : value_(value),valueLength_(valueLength) {};
};

class Identifier : public Expression<Identifier>
{
protected:
    void acceptImpl(ASTVisitor & visitor) override;
public:
    const char * value_ = nullptr;
    Identifier(const char * value) : value_(value) {};
};

class BinaryExpression : public Expression<BinaryExpression>
{
protected:
    void acceptImpl(ASTVisitor & visitor) override;
public:
    BinaryOperatorType operator_;
    ExpressionBase * left_ = nullptr;
    ExpressionBase * right_ = nullptr;
    BinaryExpression(BinaryOperatorType ope,ExpressionBase * left,ExpressionBase * right) : 
    operator_(ope), left_(left), right_(right) {};
};

class FunctionCall : public Expression<FunctionCall>
{
protected:
    void acceptImpl(ASTVisitor & visitor) override;
public:
    ExpressionBase * function_ = nullptr;
    ExpressionBase * argument_ = nullptr;
    std::size_t argumentNumber_ = 0;
    FunctionCall(ExpressionBase * function, ExpressionBase * argument, std::size_t argumentLength):
    function_(function), argument_(argument), argumentNumber_(argumentLength) {};
    FunctionCall(ExpressionBase * function): 
    function_(function), argument_(nullptr), argumentNumber_(0) {};
};


class StatementBase
{
public:
    virtual ~StatementBase() = default;
    virtual void accept(ASTVisitor & visitor) = 0;
};

template<typename StatementDerived>
class Statement : public ASTNode<StatementDerived>, public StatementBase
{
public:
    virtual ~Statement() = default;
    void accept(ASTVisitor & visitor) override
    {
        ASTNode<StatementDerived>::accept(visitor);
    }
};

class VariableDeclaration : public Statement<VariableDeclaration>
{
protected:
    void acceptImpl(ASTVisitor & visitor) override;
public:
    const char * variableName_ = nullptr;
    ExpressionBase * initializer_ = nullptr;
    VariableDeclaration(const char * variableName,ExpressionBase * initializer) :
    variableName_(variableName), initializer_(initializer) {};
};

class ExpressionStatement : public Statement<ExpressionStatement>
{
protected:
    void acceptImpl(ASTVisitor & vistor) override;
public:
    ExpressionBase * expression_ = nullptr;
    ExpressionStatement(ExpressionBase * expression) : expression_(expression) {};
};

class IfStatement : public Statement<IfStatement>
{
protected:
    void acceptImpl(ASTVisitor & vistor) override;
public:
    ExpressionBase * condition_ = nullptr;
    StatementBase * thenStatement_ = nullptr;
    StatementBase * elseStatement_ = nullptr;
    IfStatement(ExpressionBase * condition, StatementBase * thenStatement, StatementBase * elseStatement):
    condition_(condition), thenStatement_(thenStatement), elseStatement_(elseStatement) {} ;
};

class BlockStatement : public Statement<BlockStatement>
{
protected:
    void acceptImpl(ASTVisitor & vistor) override;
public:
    StatementBase * statements_ = nullptr;
    std::size_t statementsNumber = 0;
    BlockStatement(StatementBase * statements) : statements_(statements) {};
};

}
}

#include "../../src/scripting/sigflx_script_ast_node.tpp"