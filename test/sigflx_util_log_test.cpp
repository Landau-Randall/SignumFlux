#include <gtest/gtest.h>
#include "sigflx_lib/sigflx_util_log.h"


TEST(LogTest,AllTest)
{
    using namespace SignumFlux::Util;
    Logger::log(LogLevel::ERROR,"it is error!\n");
    Logger::logf(LogLevel::INFO,"must be the water %c %d %f \n",'a',120,0.125);
}