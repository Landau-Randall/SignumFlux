#pragma once
#include <string>
#include <cstdint>
#include <cstddef>
#include "core/sigflx_module.h"
#include "core/sigflx_signal.h" 
#include "sigflx_lib/sigflx_digital_generate.h"
#include "sigflx_lib/sigflx_math_hasher.h"

enum class WaveType
{
    Inpulse,
    Step,
    Sine,
    Cosine,
    Square,
    Sawtooth,
    Triangle,
    Ramp
};

namespace SignumFlux
{
namespace Modules
{
class Oscillator : public Module<Oscillator>
{
private:
    std::uint32_t uid_ = 0;
    std::string name_;
    float parameters_[5];
    std::size_t parameterNumber_;
    WaveType wave_;
    bool enabled_;

    static std::size_t getParameterNumber(WaveType type);
protected:
    void manageImpl(class ModuleScheduler & scheduler) override;
public:
    Oscillator() = default;   
    Oscillator(const std::string & name,WaveType wave);
    Oscillator(const Oscillator & object) = delete;
    Oscillator(Oscillator && object) noexcept;

    ~Oscillator() = default;

    Oscillator & operator=(const Oscillator & object) = delete;
    Oscillator & operator=(Oscillator && object) noexcept;

    std::uint32_t uid() const noexcept { return uid_; };
    const std::string & name() const noexcept override { return name_; };
    WaveType wave() const noexcept { return wave_; };
    std::size_t parameterNumber() const noexcept { return parameterNumber_; };
    void enable() override { enabled_ = true; };
    void disable() override { enabled_ = false; };
    bool isEnabled() const override { return enabled_; };

    void prepare(float * parameter);

    template<typename T>
    void process(Signal<T> & object);
};
}
}

#include "../../src/module/sigflx_modules_oscillator.tpp"