#pragma once

namespace SignumFlux
{
namespace Strings
{
template<typename CharType>
bool isAlnum(CharType ch);

template<typename CharType>
bool isAlpha(CharType ch);

template<typename CharType>
bool isUpper(CharType ch);

template<typename CharType>
bool isLower(CharType ch);

template<typename CharType>
bool isDigit(CharType ch);

template<typename CharType>
bool isSpace(CharType ch);
}
}

#include "../../src/sigflx_lib/sigflx_strings_check.tpp"