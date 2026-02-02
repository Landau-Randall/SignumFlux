#pragma once
#include <string>

namespace SignumFlux
{
template<typename Derived>
class Module
{
protected:
    virtual void manageImpl(class ModuleScheduler & scheduler) = 0;
public:
    Module() = default;
    Module(const Module & object) = delete;
    Module(Module && object) noexcept = default;

    virtual ~Module() = default;

    Module & operator=(const Module & object) = delete;
    Module & operator=(Module && object) noexcept = default;

    virtual const std::string & name() const noexcept = 0;
    virtual void enable() = 0;
    virtual void disable() = 0;
    virtual bool isEnabled() const = 0;

    void manage(class ModuleScheduler & scheduler)
    {
        static_cast<Derived*>(this)->ManageImpl(scheduler);
    }
};
}