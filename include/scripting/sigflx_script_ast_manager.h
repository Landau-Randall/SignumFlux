#pragma once
#include <cstddef>
#include "scripting/sigflx_script_ast_node.h"

namespace SignumFlux
{
namespace Script
{
class ASTManager
{
private:
    ExpressionBase ** expressions_ = nullptr;
    StatementBase ** statements_ = nullptr;
public:
    
};
}
}