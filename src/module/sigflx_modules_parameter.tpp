#include "module/sigflx_modules_parameter.h"

namespace SignumFlux
{
namespace Modules
{
Parameter::Parameter(const std::string & valueName,float value):
name_(valueName),
parameterValue_(value),
type_(ParameterType::Float)
{

}

Parameter::Parameter(const std::string & valueName,int32_t value):
name_(valueName),
parameterValue_(value),
type_(ParameterType::Int)
{

}

Parameter::Parameter(const std::string & valueName,bool value):
name_(valueName),
parameterValue_(value),
type_(ParameterType::Bool)
{

}

Parameter::Parameter(const std::string & valueName,const std::string & value):
name_(valueName),
parameterValue_(value),
type_(ParameterType::String)
{

}
}
}