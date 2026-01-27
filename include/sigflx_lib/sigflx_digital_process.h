#pragma once

#include <cstddef>
#include <algorithm>

namespace SignumFlux
{
namespace Digital
{
template<typename T>
void add(T * dest,std::size_t len,T * additor1,T * additor2);

template<typename T>
void substract(T * dest,std::size_t len,T * substractor1,T * substractor2);

template<typename T>
void multiply(T * dest, std::size_t len, T * multiplier1, T * multiplier2);

template<typename T>
void scale(T * dest, std::size_t len, const T * source, T gain);

template<typename T>
void mix(T * dest, std::size_t len, const T * source1, T gain1, const T * source2, T gain2);

template<typename T>
void crossfade(T * dest, std::size_t len, const T * sourceA, const T * sourceB, const T * control);

template<typename T>
void clamp(T * dest, std::size_t len,T * source,T min,T max);

template<typename T>
void clear(T * dest, std::size_t len);

template<typename T>
void fill(T * dest, std::size_t len, T value);

template<typename T,typename Func>
void traverse(T * data, std::size_t len, Func op);

template<typename T,typename Func>
void transform(T * dest, std::size_t len, T * source, Func op);

}
}

#include "../../src/sigflx_lib/sigflx_digital_process.tpp"