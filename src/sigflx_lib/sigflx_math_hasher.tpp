#include "sigflx_lib/sigflx_math_hasher.h"

namespace SignumFlux
{
namespace Math
{
template<typename PointerType,typename IntegerType>
IntegerType pointerHash(PointerType input)
{
    static_assert(std::is_integral<IntegerType>::value,"IntegerType must be the intefer!\n");

    std::uintptr_t firstValue = reinterpret_cast<std::uintptr_t>(input);
    firstValue ^= firstValue >> 33;
    firstValue *= 0xff51afd7ed558ccd;
    firstValue ^= firstValue >> 33;
    firstValue *= 0xc4ceb9fe1a85ec53;
    firstValue ^= firstValue >> 33;

    return static_cast<IntegerType>(firstValue);
}

template<typename ViewType,typename IntegerType>
IntegerType viewHash(ViewType input)
{
    static_assert(std::is_integral<IntegerType>::value,"IntegerType must be the intefer!\n");

    std::size_t hash = 5381;
    for (const auto & value : input)
    {
        hash = ((hash << 5) + hash) + value;
    }
    return static_cast<IntegerType>(hash);
}
}
}