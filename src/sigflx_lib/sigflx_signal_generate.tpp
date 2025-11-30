#include "sigflx_lib/sigflx_signal_generate.h"

namespace SignumFlux
{
namespace Signal
{
template<typename T>
void inpulse(T * data,std::size_t len,T amp)
{
    if (data != nullptr && len != 0)
    {
        for (std::size_t i = 0;i < len;++i)
            data[i] = (i == 0) ? (amp) : (T(0));
    }
}

template<typename T>
void step(T * data,std::size_t len,std::size_t delay,T amp)
{
    if (data != nullptr && len != 0)
    {
        for (std::size_t i = 0;i < len;++i)
            data[i] = (i >= delay) ? (amp) : (T(0));
            
    }
}

template<typename T>
void sine(T* data, std::size_t len, T freq, T amp = T(1), T phase = T(0), T sampleRate = T(44100))
{
    if (data != nullptr && len != 0)
    {
        for (std::size_t i = 0;i < len;++i)
            data[i] = amp * std::sin((2.0 * Math::pi_v<T> * freq * i) / sampleRate + phase);
    }
}

template<typename T>
void cosine(T* data, std::size_t len, T freq, T amp = T(1), T phase = T(0), T sampleRate = T(44100))
{
    if (data != nullptr && len != 0)
    {
        for (std::size_t i = 0;i < len;++i)
            data[i] = amp * std::cos((2.0 * Math::pi_v<T> * freq * i) / sampleRate + phase);
    }
}

template<typename T>
void square(T * data, std::size_t len,T freq, T amp = T(1), T phase = T(0), T sampleRate = T(44100), T duty = T(0.5))
{
    if (data != nullptr && len != 0)
    {
        for (std::size_t i = 0; i < len; ++i)
        {
            T currentPhase = std::fmod((freq * i / sampleRate) + (phase / (2.0 * Math::pi_v<T>)), T(1.0));
            data[i] = (currentPhase < duty) ? amp : -amp;
        }
    }
}

template<typename T>
void sawtooth(T* data, std::size_t len, T freq, T amp = T(1), T phase = T(0), T sampleRate = T(44100))
{
    if (data != nullptr && len != 0)
    {
        for (std::size_t i = 0;i < len;++i)
        {           
            T currentPhase = std::fmod((freq * i / sampleRate) + (phase / (2.0 * Math::pi_v<T>)), T(1.0));
            data[i] = amp * (currentPhase * T(2.0) - T(1.0));            
        }
    }
}

template<typename T>
void triangle(T* data, std::size_t len, T freq, T amp = T(1), T phase = T(0), T sampleRate = T(44100))
{
    if (data != nullptr && len != 0)
    {
        for (std::size_t i = 0; i < len; ++i)
        {
            T currentPhase = std::fmod((freq * i / sampleRate) + (phase / (2.0 * Math::pi_v<T>)), T(1.0));
            T value = T(2.0) * std::abs(T(2.0) * currentPhase - T(1.0)) - T(1.0);
            data[i] = amp * value;
        }
    }
}

template<typename T>
void ramp(T * data,std::size_t len, T start, T end)
{
    if (data != nullptr && len != 0)
    {
        const double step = static_cast<double>(end - start) / (len - 1);
        
        for (std::size_t i = 0;i < len;++i)
        {
            data[i] = static_cast<T>(start + step * i);
        }
    }
}

}
}