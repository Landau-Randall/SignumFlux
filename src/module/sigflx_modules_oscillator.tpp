#include "module/sigflx_modules_oscillator.h"

namespace SignumFlux
{
namespace Modules
{

void Oscillator::manageImpl(class ModuleScheduler & scheduler) 
{

}

std::size_t Oscillator::getParameterNumber(WaveType type)
{
    switch (type)
    {
    case WaveType::Inpulse:
        return 1;
    case WaveType::Step:
        return 2;
    case WaveType::Sine:
        return 4;
    case WaveType::Cosine:
        return 4;
    case WaveType::Square:
        return 5;
    case WaveType::Sawtooth:
        return 4;
    case WaveType::Triangle:
        return 4;
    case WaveType::Ramp:
        return 2;
    default:
        return 0;
        break;
    }
}

Oscillator::Oscillator(const std::string & name,WaveType wave):
uid_(Math::viewHash<const std::string &,std::uint32_t>(name)),
name_(std::move(name)),
parameterNumber_(getParameterNumber(wave)),
wave_(wave),
enabled_(false)
{

}

Oscillator::Oscillator(Oscillator && object) noexcept:
uid_(object.uid_),
name_(std::move(object.name_)),
parameterNumber_(object.parameterNumber_),
wave_(object.wave_),
enabled_(object.enabled_)
{
    object.uid_ = 0;
    object.parameterNumber_ = 0;
    object.enabled_ = false;
}


Oscillator & Oscillator::operator=(Oscillator && object) noexcept
{
    if (this != &object)
    {
        uid_ = object.uid_;
        name_= std::move(object.name_);
        parameterNumber_ = object.parameterNumber_;
        wave_ = object.wave_;
        enabled_ = object.enabled_;

        object.uid_ = 0;
        object.parameterNumber_ = 0;
        object.enabled_ = false;
    }
    return *this;
}


void Oscillator::prepare(float * parameter)
{
    if (parameter != nullptr)
    {
        for (std::size_t i = 0;i < parameterNumber_;++i)
        {
            parameters_[i] = parameter[i];
        }
    }
}

template<typename T>
void Oscillator::process(Signal<T> & object)
{
    if (enabled_)
    {
        switch (wave_)
        {
        case WaveType::Inpulse:
            Digital::inpulse(object.data(),object.frames(),parameters_[0]);
            break;
        case WaveType::Step:
            Digital::step(object.data(),object.frames(),parameters_[0],parameters_[1]);
            break;
        case WaveType::Sine:
            Digital::sine(object.data(),object.frames(),parameters_[0],parameters_[1],parameters_[2],parameters_[3]);
            break;
        case WaveType::Cosine:
            Digital::cosine(object.data(),object.frames(),parameters_[0],parameters_[1],parameters_[2],parameters_[3]);
            break;
        case WaveType::Square:
            Digital::square(object.data(),object.frames(),parameters_[0],parameters_[1],parameters_[2],parameters_[3],parameters_[4]);
            break;
        case WaveType::Sawtooth:
            Digital::sawtooth(object.data(),object.frames(),parameters_[0],parameters_[1],parameters_[2],parameters_[3]);
            break;
        case WaveType::Triangle:
            Digital::triangle(object.data(),object.frames(),parameters_[0],parameters_[1],parameters_[2],parameters_[3]);
            break;
        case WaveType::Ramp:
            Digital::ramp(object.data(),object.frames(),parameters_[0],parameters_[1]);
            break;
        default:
            return;
        }
    }
}
}
}