#include "sigflx_lib/sigflx_strings_check.h"

namespace SignumFlux
{
namespace Strings
{
template<typename CharType>
bool isAlnum(CharType ch)
{
    return (ch >= static_cast<CharType>('A') && ch <= static_cast<CharType>('Z')) || 
           (ch >= static_cast<CharType>('a') && ch <= static_cast<CharType>('z')) ||
           (ch >= static_cast<CharType>('0') && ch <= static_cast<CharType>('9'));
}

template<typename CharType>
bool isAlpha(CharType ch)
{
    return (ch >= static_cast<CharType>('A') && ch <= static_cast<CharType>('Z')) || 
           (ch >= static_cast<CharType>('a') && ch <= static_cast<CharType>('z')) ||
           (ch == static_cast<CharType>('_'));
}

template<typename CharType>
bool isUpper(CharType ch)
{
    return (ch >= static_cast<CharType>('A') && ch <= static_cast<CharType>('Z'));
}

template<typename CharType>
bool isLower(CharType ch)
{
    return (ch >= static_cast<CharType>('a') && ch <= static_cast<CharType>('z'));
}

template<typename CharType>
bool isDigit(CharType ch)
{
    return (ch >= static_cast<CharType>('0') && ch <= static_cast<CharType>('9'));
}

template<typename CharType>
bool isSpace(CharType ch)
{
    return ch == static_cast<CharType>(' ')  ||
           ch == static_cast<CharType>('\t') ||
           ch == static_cast<CharType>('\n') ||
           ch == static_cast<CharType>('\r') ||
           ch == static_cast<CharType>('\v') ||
           ch == static_cast<CharType>('\f');
}

}
}