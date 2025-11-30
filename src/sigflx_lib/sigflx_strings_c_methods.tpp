#include "sigflx_lib/sigflx_strings_c_methods.h"

namespace SignumFlux
{
namespace Strings
{
template<typename CharType>
std::size_t stringLength(const CharType * str)
{
    if (str != nullptr)
    {
        std::size_t index = 0;
        while (str[index] != static_cast<CharType>('\0'))
        {
            index++;
        }
        return index;
    }
    else
    {
        return 0;
    }
}

template<typename CharType>
void stringCopy(CharType * target,const CharType * source,std::size_t n)
{
    if (target != nullptr && source != nullptr)
    {
        std::size_t i = 0;
        for (;i < n - 1 && (source[i] != static_cast<CharType>('\0'));++i)
        {
            target[i] = source[i];
        }
        target[i] = static_cast<CharType>('\0');
    }
    else
    {
        return;
    }
}

template<typename CharType>
int stringCompare(const CharType * firstStr,const CharType * secondStr)
{
    if (firstStr != nullptr && secondStr != nullptr)
    {
        std::size_t i = 0;
        while (firstStr[i] != static_cast<CharType>('\0') && secondStr[i] != static_cast<CharType>('\0'))
        {
            if (firstStr[i] > secondStr[i])
                return 1;
            if (firstStr[i] < secondStr[i])
                return -1;
            ++i;
        }
        if (firstStr[i] == static_cast<CharType>('\0') && secondStr[i] == static_cast<CharType>('\0'))
            return 0;
        if (firstStr[i] == static_cast<CharType>('\0'))
            return -1;
        return 1;
    }
    else
    {
        return -2;
    }
}

template<typename CharType>
int stringCompare(const CharType * firstStr,const CharType * secondStr,std::size_t n)
{
    if (firstStr != nullptr && secondStr != nullptr && n != 0)
    {
        std::size_t i = 0;
        for (;i < n && firstStr[i] != static_cast<CharType>('\0') && secondStr[i] != static_cast<CharType>('\0');++i)
        {
            if (firstStr[i] > secondStr[i])
                return 1;
            if (firstStr[i] < secondStr[i])
                return -1;
        }
        if (i == n)
            return 0;
        if (firstStr[i] == secondStr[i])
            return 0;
        if (firstStr[i] == static_cast<CharType>('\0'))
            return -1;
        return 1;
        
    }
    else
    {
        return -2;
    }
}

template<typename CharType>
const CharType* stringFind(const CharType* str, CharType ch)
{
    if (str != nullptr)
    {
        if (ch == static_cast<CharType>('\0'))
        {
            return nullptr;
        }

        while(*str != static_cast<CharType>('\0'))
        {
            if (*str == ch)
            {
                return str;
            }
            ++str;
        }
        return nullptr;
    }
    else
    {
        return nullptr;
    }
}

template<typename CharType> 
const CharType* stringFind(const CharType* str, const CharType* substr)
{
    if (str != nullptr)
    {
        if (substr == nullptr || *substr == static_cast<CharType>('\0'))
            return str;
        
        const CharType * copystr,* copysubstr;
        while (*str != static_cast<CharType>('\0'))
        {
            copystr = str;
            copysubstr = substr;
            while (*copystr == *copysubstr && *copysubstr != static_cast<CharType>('\0'))
            {
                ++copystr;
                ++copysubstr;
            }
            if (*copysubstr == static_cast<CharType>('\0'))
                return str;
            ++str;
        }

        return nullptr;
    }
    else
    {
        return nullptr;
    }
}

template<typename CharType> 
void stringFill(CharType* dest, CharType value, std::size_t n)
{
    if (dest != nullptr)
    {
        for (std::size_t i = 0;i < n;i++)
        {
            dest[i] = value;
        }
    }
    else
    {
        return;
    }
}

template<typename CharType>
std::size_t stringSignCount(const CharType * str,CharType sign)
{
    std::size_t count = 0;
    const CharType * counter = str;
    while (*counter != static_cast<CharType>('\0'))
    {
        if (*counter == sign)
            ++count;
        ++counter;
    }
    return count;
}

template<typename CharType>
std::size_t stringSignCount(const CharType * str,std::size_t len,CharType sign)
{
    std::size_t count = 0;
    for (std::size_t i = 0;i < len;++i)
    {
        if (str[i] == sign)
            ++count; 
    }
    return count;
}

template<typename CharType>
const CharType ** stringSplit(const CharType * str,CharType splitSign)
{
    if (str != nullptr && splitSign != static_cast<CharType>('\0'))
    {
        std::size_t count = 1;
        count += stringSignCount(str,splitSign);
        
        const CharType ** result = new const CharType*[count + 1];
        const CharType * start = str;
        const CharType * counter = str;
        std::size_t index = 0;
        while (*counter != static_cast<CharType>('\0'))
        {
            if (*counter == splitSign)
            {
                result[index++] = start;
                start = counter + 1;
            }
            ++counter;
        }
        result[index++] = start;
        result[index] = nullptr;
        return result;
    }
    else
    {
        return nullptr;
    }
}

template<typename CharType>
const CharType ** stringSplit(const CharType * str, std::size_t len, CharType splitSign)
{
    if (str != nullptr && len = 0 && splitSign != static_cast<CharType>('\0'))
    {
        std::size_t count = 1;
        count += stringSignCount(str,len,splitSign);
        const CharType ** result = new const CharType*[count + 1];
        std::size_t index = 0;
        result[index++] = str;

        for (std::size_t i = 0;i < len;++i)
        {
            if (str[i] == splitSign)
                result[index++] = (str + i + 1);
        }

        result[index] = nullptr;
        
        return result;
    }
    else
    {
        return nullptr;
    }


}

template<typename CharType>
void stringsRelease(const CharType ** strings)
{
    if (strings != nullptr)
    {
        delete [] strings;
    }
}

template<typename CharType>
void stringConcatenate(CharType * dest,const CharType * src)
{
    if (dest != nullptr && src != nullptr)
    {
        CharType * start1 = dest;
        while (*start1 != static_cast<CharType>('\0'))
        {
            ++start1;
        }
        std::size_t length = stringLength(src);
        stringCopy(start1,src,length + 1);
    }
    else
    {
        return;
    }
}


template<typename CharType>
void stringConcatenate(CharType * dest, const CharType * src, std::size_t n)
{
    if (dest != nullptr && src != nullptr)
    {
        CharType * start1 = dest;
        while (*start1 != static_cast<CharType>('\0'))
        {
            ++start1;
        }
        stringCopy(start1,src,n + 1);
    }
    else
    {
        return;
    }
}
}
}