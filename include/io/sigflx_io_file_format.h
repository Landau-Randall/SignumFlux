#pragma once
#include <type_traits>
#include "sigflx_lib/sigflx_strings_c_methods.h"

namespace SignumFlux
{
namespace IO
{
enum class Format
{
    NONE,
    WAV,
    MP3
};

template<typename CharType>
constexpr const CharType* getFormatExtension(Format format) 
{
    if constexpr (std::is_same_v<CharType, char>) 
    {
        constexpr const char* extensions[3] = {"\0", "wav", "mp3"};
        return extensions[static_cast<int>(format)];
    } 
    else if constexpr (std::is_same_v<CharType, wchar_t>) 
    {
        constexpr const wchar_t* extensions[3] = {L"\0", L"wav", L"mp3"};
        return extensions[static_cast<int>(format)];
    }
    return nullptr;
}

template<typename CharType>
bool isFormatFile(const CharType * filepath,Format form)
{
    
}

}
}