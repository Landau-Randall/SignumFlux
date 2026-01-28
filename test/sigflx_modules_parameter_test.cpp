#include <gtest/gtest.h>
#include <string>
#include <iostream>
#include "module/sigflx_modules_parameter.h"

using namespace SignumFlux::Modules;

TEST(ParameterTest,ParameterConstruction)
{
    Parameter freq(std::string("freq"),44100.0f);
    Parameter phase(std::string("phase"),1.0f);
    Parameter wave(std::string("wave"),std::string("sine"));

    std::cout << freq.name() << " : " << freq.value<float>() <<  std::endl;
    std::cout << phase.name() << " : " << phase.value<float>() << std::endl;
    std::cout << wave.name() << wave.value<std::string>() << std::endl;

    EXPECT_NE(freq.uid(),phase.uid());
}