#pragma once
#include <cstddef>
#include <cmath>
#include "sigflx_lib/sigflx_math_constant.h"

namespace SignumFlux
{
namespace Digital
{
template<typename T>
void inpulse(T * data,std::size_t len,T amp = T(1));

template<typename T>
void step(T * data,std::size_t len,std::size_t delay = 0,T amp = T(1));

template<typename T>
void sine(T* data, std::size_t len, T freq, T amp = T(1), T phase = T(0), T sampleRate = T(44100));

template<typename T>
void cosine(T* data, std::size_t len, T freq, T amp = T(1), T phase = T(0), T sampleRate = T(44100));

template<typename T>
void square(T * data, std::size_t len,T freq, T amp = T(1), T phase = T(0), T sampleRate = T(44100), T duty = T(0.5));

template<typename T>
void sawtooth(T* data, std::size_t len, T freq, T amp = T(1), T phase = T(0), T sampleRate = T(44100));

template<typename T>
void triangle(T* data, std::size_t len, T freq, T amp = T(1), T phase = T(0), T sampleRate = T(44100));

template<typename T>
void ramp(T * data,std::size_t len, T start, T end);
}
}

#include "../../src/sigflx_lib/sigflx_digital_generate.tpp"