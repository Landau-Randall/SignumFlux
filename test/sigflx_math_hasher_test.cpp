#include <gtest/gtest.h>
#include <iostream>
#include "sigflx_lib/sigflx_container_vector_view.h"
#include "sigflx_lib/sigflx_math_hasher.h"

TEST(HasherTest,PointerValue)
{
    using namespace SignumFlux::Math;
    const char * a = "hello world";
    std::uint32_t value = pointerHash<const char *,std::uint32_t>(a);
    std::uint32_t value_2 = pointerHash<const char *,std::uint32_t>(a + 1);
    EXPECT_NE(value,value_2);
    std::cout << "pointer hash value1 :" << value << std::endl;
    std::cout << "pointer hash value2 :" << value_2 << std::endl;
}

TEST(HasherTest,ViewHash)
{
    using namespace SignumFlux::Math;
    using TestView = SignumFlux::Container::VectorView<const char>;
    const char * a = "hello,world";
    const char * b = "hello world";
    TestView test1(a,11);
    TestView test2(b,11);

    std::uint32_t value1 = viewHash<TestView,std::uint32_t>(test1);
    std::uint32_t value2 = viewHash<TestView,std::uint32_t>(test2);
    EXPECT_NE(value1,value2);
    std::cout << "view hash value1 :" << value1 << std::endl;
    std::cout << "view hash value2 :" << value2 << std::endl;

}