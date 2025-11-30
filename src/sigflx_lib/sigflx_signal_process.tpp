#include "sigflx_lib/sigflx_signal_process.h"

namespace SignumFlux
{
namespace Signal
{
template<typename T>
void add(T * dest,std::size_t len,T * additor1,T * additor2)
{
    if (dest != nullptr && len != 0 && additor1 != nullptr && additor2 != nullptr)
    {
        for (std::size_t i = 0;i < len;++i)
        {
            dest[i] = additor1[i] + additor2[i];
        }
    }
}

template<typename T>
void substract(T * dest,std::size_t len,T * substractor1,T * substractor2)
{
    if (dest != nullptr && len != 0 && substractor1 != nullptr && substractor2 != nullptr)
    {
        for (std::size_t i = 0;i < len;++i)
        {
            dest[i] = substractor1[i] + substractor2[i];
        }
    }
}

template<typename T>
void multiply(T * dest,std::size_t len,T * multiplier1,T * multiplier2)
{
    if (dest != nullptr && len != 0 && multiplier1 != nullptr && multiplier2 != nullptr)
    {
        for (std::size_t i = 0;i < len;++i)
        {
            dest[i] = multiplier1[i] * multiplier2[i];
        }
    }
}

template<typename T>
void scale(T * dest, std::size_t len, const T * source, T gain)
{
    if (dest != nullptr && len != 0 && source != nullptr)
    {
        for (std::size_t i = 0;i < len;++i)
        {
            dest[i] = gain * source[i];
        }
    }
}

template<typename T>
void mix(T * dest, std::size_t len, const T * source1, T gain1, const T * source2, T gain2)
{
    if (dest != nullptr && len != 0 && source1 != nullptr && source2 != nullptr)
    {
        for (std::size_t i = 0;i < len;++i)
        {
            dest[i] = gain1 * source1[i] + gain2 * source2[i];
        }
    }
}

template<typename T>
void crossfade(T * dest, std::size_t len, const T * sourceA, const T * sourceB, const T * control)
{
    if (dest != nullptr && len != 0 && sourceA != nullptr && sourceB != nullptr && control != nullptr)
    {
        const T one = T(1); 
        for (std::size_t i = 0; i < len; ++i)
        {
            const T ctrl = control[i];
            const T gainA = one - ctrl;
            const T gainB = ctrl;
            
            dest[i] = sourceA[i] * gainA + sourceB[i] * gainB;
        }
    }
}

template<typename T>
void clear(T * dest, std::size_t len)
{
    if (dest != nullptr && len != 0)
    {
        for (std::size_t i = 0;i < len;++i)
        {
            dest[i] = T(0);
        }
    }
}

template<typename T>
void fill(T * dest,std::size_t len,T value)
{
    if (dest != nullptr && len != 0)
    {
        for (std::size_t i = 0;i < len;++i)
        {
            dest[i] = value;
        }
    }
}

template<typename T>
void clamp(T * dest,std::size_t len,T * source,T min,T max)
{
    if (dest != nullptr && len != 0 && source != nullptr && min <= max)
    {
        for (std::size_t i = 0;i < len;++i)
        {
            dest[i] = std::max(std::min(max,source[i]),min);
        }
    }
}

template<typename T,typename Func>
void traverse(T * data,std::size_t len,Func op)
{
    if (data != nullptr && len != 0)
    {
        for (std::size_t i = 0;i < len;++i)
        {
            op(data[i]);
        }
    }
}

template<typename T,typename Func>
void transform(T * dest, std::size_t len, T * source, Func op)
{
    if (dest != nullptr && len != 0 && source != nullptr)
    {
        for (std::size_t i = 0;i < len;++i)
        {
            dest[i] = op(source[i]);
        }
    }
}
}
}