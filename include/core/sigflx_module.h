#pragma once

namespace SignumFlux
{
class Module
{
public:
    virtual ~Module() = default;

    virtual const char * name() const noexcept = 0;
    
};
}