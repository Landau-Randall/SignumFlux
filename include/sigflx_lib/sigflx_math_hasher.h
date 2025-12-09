#pragma once
#include <type_traits>
#include <cstddef>
#include <cstdint>

namespace SignumFlux
{
namespace Math
{
template<typename PointerType,typename IntegerType>
IntegerType pointerHash(PointerType input);

template<typename ViewType,typename IntegerType>
IntegerType viewHash(ViewType input);

}
}

#include "../../src/sigflx_lib/sigflx_math_hasher.tpp"