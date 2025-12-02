#pragma once
#include <type_traits>
#include <cstddef>
#include <cstdint>

namespace SignumFlux
{
namespace Math
{
template<typename InputType,typename IntegerType>
IntegerType pointerHash(const InputType * input);

}
}

#include "../../src/sigflx_lib/sigflx_math_hasher.tpp"