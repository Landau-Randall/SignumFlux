#include "scripting/sigflx_script_ast_visitor.h"

namespace SignumFlux
{
namespace Script
{
void ASTPrinter::visit(IntegerLiteral & node)
{
    Util::Logger::logf(Util::LogLevel::INFO,"Value of the IntegerLiteral node is: %lli",node.value_);
}


}
}