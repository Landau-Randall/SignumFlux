#include <gtest/gtest.h>
#include <string>
#include <iostream>
#include "module/sigflx_modules_oscillator.h"

TEST(OscillatorTest,BuildTest)
{
    using namespace SignumFlux::Modules;
    Oscillator test1(std::string("sin_wave"),WaveType::Sine);
    EXPECT_NE(test1.uid(),0);
    EXPECT_EQ(test1.parameterNumber(),4);
    EXPECT_EQ(test1.wave(),WaveType::Sine);
    EXPECT_EQ(test1.isEnabled(),false);
}

TEST(OscillatorTest,GenerateTest)
{
    using namespace SignumFlux::Modules;
    Oscillator test1(std::string("wave"),WaveType::Step);
    SignumFlux::Signal<float> signal(10,44100.0f);
    float params[2] = {0.0,1.0};
    test1.prepare(&params[0]);
    test1.enable();
    test1.process(signal);

    for (auto & ele : signal)
    {
        std::cout << ele << ' ' ;
    }

    std::cout << std::endl;
}