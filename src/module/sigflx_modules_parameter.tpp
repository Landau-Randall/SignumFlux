#include "module/sigflx_modules_parameter.h"

namespace SignumFlux
{
namespace Modules
{
Parameter::Parameter(const std::string & valueName,float value):
uid_(Math::viewHash<const std::string & ,std::uint32_t>(valueName)),
name_(valueName),
parameterValue_(value),
type_(ParameterType::Float)
{

}

Parameter::Parameter(const std::string & valueName,int32_t value):
uid_(Math::viewHash<const std::string & ,std::uint32_t>(valueName)),
name_(valueName),
parameterValue_(value),
type_(ParameterType::Int)
{

}

Parameter::Parameter(const std::string & valueName,bool value):
uid_(Math::viewHash<const std::string & ,std::uint32_t>(valueName)),
name_(valueName),
parameterValue_(value),
type_(ParameterType::Bool)
{

}

Parameter::Parameter(const std::string & valueName,const std::string & value):
uid_(Math::viewHash<const std::string & ,std::uint32_t>(valueName)),
name_(valueName),
parameterValue_(value),
type_(ParameterType::String)
{

}
}
}