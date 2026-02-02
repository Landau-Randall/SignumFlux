#pragma once
#include <cstdint>
#include <string>
#include <variant>

enum class ParameterType
{
    Float,
    Int,
    Bool,
    String
};

namespace SignumFlux
{
namespace Modules
{
class Parameter
{
private:
    std::string name_;
    std::variant<
        float,
        int32_t,
        bool,
        std::string> parameterValue_;
    ParameterType type_;
public:
    Parameter() = default;
    Parameter(const std::string & valueName,float value);
    Parameter(const std::string & valueName,int32_t value);
    Parameter(const std::string & valueName,bool value);
    Parameter(const std::string & valueName,const std::string & value);

    ~Parameter() = default;

    const std::string & name() const noexcept { return name_; };
    ParameterType type() const noexcept { return type_; };
    
    template<typename T>
    T value() const noexcept { return std::get<T>(parameterValue_); };
};  
}
}

#include "../../src/module/sigflx_modules_parameter.tpp"