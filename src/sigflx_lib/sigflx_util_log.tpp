#include "sigflx_lib/sigflx_util_log.h"


namespace SignumFlux
{
namespace Util
{
void Logger::log(LogLevel level, const char * msg)
{
    const char* prefix = nullptr;
    switch (level)
    {
        case LogLevel::DEBUG: prefix = "[DEBUG] "; break;
        case LogLevel::INFO:  prefix = "[INFO] ";  break;
        case LogLevel::WARN:  prefix = "[WARN] ";  break;
        case LogLevel::ERROR: prefix = "[ERROR] "; break;
        default: prefix = ""; break;
    }  
    char buffer[512];
    std::snprintf(buffer,sizeof(buffer),"%s%s\n", prefix,msg);
    std::fputs(buffer,stdout);
}

template<typename...Args>
void Logger::logf(LogLevel level, const char * format,Args && ...args)
{
    char buffer[512];
    std::snprintf(buffer, sizeof(buffer), format, std::forward<Args>(args)...);
    Logger::log(level, buffer);
}
}
}