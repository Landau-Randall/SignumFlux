#pragma once
#include <cstdio>


namespace SignumFlux
{
namespace Util
{
enum class LogLevel
{
    DEBUG,
    INFO,
    WARN,
    ERROR
};

class Logger
{
public:
    static void log(LogLevel level, const char * msg);
    
    template<typename...Args>
    static void logf(LogLevel level, const char * format,Args && ...args);
};
}
}

#include "../../src/sigflx_lib/sigflx_util_log.tpp"