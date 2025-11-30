#pragma once
#include <cstddef>
#include "sigflx_lib/sigflx_allocators_fixed_pool.h"


namespace SignumFlux
{
namespace Strings
{
template<typename CharType>
std::size_t stringLength(const CharType * str);

template<typename CharType>
void stringCopy(CharType * target,const CharType * source,std::size_t n);

template<typename CharType>
int stringCompare(const CharType * firstStr,const CharType * secondStr);

template<typename CharType>
int stringCompare(const CharType * firstStr,const CharType * secondStr,std::size_t n);

template<typename CharType>
const CharType* stringFind(const CharType * str, CharType ch);

template<typename CharType> 
const CharType* stringFind(const CharType * str, const CharType* substr);

template<typename CharType> 
void stringFill(CharType* dest, CharType value, std::size_t n);

template<typename CharType>
std::size_t stringSignCount(const CharType * str,CharType sign);

template<typename CharType>
std::size_t stringSignCount(const CharType * str,std::size_t len,CharType sign);

template<typename CharType>
const CharType ** stringSplit(const CharType * str,CharType splitSign);

template<typename CharType>
const CharType ** stringSplit(const CharType * str, std::size_t len, CharType splitSign);

template<typename CharType>
void stringsRelease(const CharType ** strings);

template<typename CharType>
void stringConcatenate(CharType * dest,const CharType * src);

template<typename CharType>
void stringConcatenate(CharType * dest, const CharType * src, std::size_t n);

}
}

#include "../../src/sigflx_lib/sigflx_strings_c_methods.tpp"