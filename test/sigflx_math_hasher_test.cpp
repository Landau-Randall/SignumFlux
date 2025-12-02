#include <gtest/gtest.h>
#include <iostream>
#include "sigflx_lib/sigflx_math_hasher.h"

TEST(HasherTest,HashValue)
{
    using namespace SignumFlux::Math;
    const char * a = "hello world";
    std::uint32_t value = pointerHash<char,std::uint32_t>(a);
    std::uint32_t value_2 = pointerHash<char,std::uint32_t>(a + 1);
    EXPECT_NE(value,value_2);
    std::cout << "value1 :" << value << std::endl;
    std::cout << "value2 :" << value_2 << std::endl;
}