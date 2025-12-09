#include "scripting/sigflx_script_lexer.h"
#include <iostream>

namespace SignumFlux
{
namespace Script
{

static inline const char * tokenToString(TokenType token)
{
    switch (token)
    {
        case TokenType::LEFT_BRACKET: return "LEFT_BRACKET";
        case TokenType::RIGHT_BRACKET: return "RIGHT_BRACKET";
        case TokenType::LEFT_BRACE: return "LEFT_BRACE";
        case TokenType::RIGHT_BRACE: return "RIGHT_BRACE";
        case TokenType::COMMA: return "COMMA";
        case TokenType::SEMICOLON: return "SEMICOLON";
        case TokenType::ILLEGAL: return "ILLEGAL";
        case TokenType::END_OF_FILE: return "END_OF_FILE";
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::STRING: return "STRING";
        case TokenType::NUMBER: return "NUMBER";
        case TokenType::VARIANT: return "VARIANT";
        case TokenType::ASSIGN: return "ASSIGN";
        case TokenType::PLUS: return "PLUS";
        case TokenType::MINUS: return "MINUS";
        case TokenType::ASTERIST: return "ASTERIST";
        case TokenType::SLASH: return "SLASH";
        case TokenType::EQUAL: return "EQUAL";
        case TokenType::NOT_EQUAL: return "NOT_EQUAL";
        case TokenType::LESS_THAN: return "LESS_THAN";
        case TokenType::GREATER_THAN: return "GREATER_THAN";
        case TokenType::LESS_EQUAL: return "LESS_EQUAL";
        case TokenType::GREATER_EQUAL: return "GREATER_EQUAL";
        case TokenType::KEYWORD_LET: return "KEYWORD_LET";
        case TokenType::KEYWORD_IF: return "KEYWORD_IF";
        case TokenType::KEYWORD_ELSE: return "KEYWORD_ELSE";
        case TokenType::KEYWORD_FOR: return "KEYWORD_FOR";
        case TokenType::DOT: return "DOT";
        default: return "UNKNOWN";
    }
}

template<typename CharType>
Container::Map<Container::VectorView<const CharType>, TokenType> 
Lexer<CharType>::keywords_(16);


template class Lexer<char>;

template class Lexer<char16_t>;

template class Lexer<char32_t>;

template<typename CharType>
void Lexer<CharType>::skipWhiteSpace()
{
    while (current_ < source_.size() && Strings::isSpace(source_[current_]))
        ++current_;
}

template<typename CharType>
CharType Lexer<CharType>::peek() const
{
    if (current_ < source_.size())
    {
        return source_[current_];
    }
    else
    {
        return static_cast<CharType>('\0');
    }
    
}

template<typename CharType>
CharType Lexer<CharType>::advance()
{
    if (current_ < source_.size())
    {
        return source_[current_++];
    }
    else
    {
        return static_cast<CharType>('\0');
    }
}

template<>
void Lexer<char>::initializeKeywords()
{
    static const char letString[] = "let";
    static const char ifString[] = "if";
    static const char elseString[] = "else";
    static const char forString[] = "for";

    keywords_.insert(Container::VectorView<const char>(letString,3),TokenType::KEYWORD_LET);
    keywords_.insert(Container::VectorView<const char>(ifString,2),TokenType::KEYWORD_IF);
    keywords_.insert(Container::VectorView<const char>(elseString,4),TokenType::KEYWORD_ELSE);
    keywords_.insert(Container::VectorView<const char>(forString,3),TokenType::KEYWORD_FOR);
}

template<>
void Lexer<char16_t>::initializeKeywords()
{
    static const char16_t letString[] = u"let";
    static const char16_t ifString[] = u"if";
    static const char16_t elseString[] = u"else";
    static const char16_t forString[] = u"for";

    keywords_.insert(Container::VectorView<const char16_t>(letString,3),TokenType::KEYWORD_LET);
    keywords_.insert(Container::VectorView<const char16_t>(ifString,2),TokenType::KEYWORD_IF);
    keywords_.insert(Container::VectorView<const char16_t>(elseString,4),TokenType::KEYWORD_ELSE);
    keywords_.insert(Container::VectorView<const char16_t>(forString,3),TokenType::KEYWORD_FOR);
}

template<>
void Lexer<char32_t>::initializeKeywords()
{
    static const char32_t letString[] = U"let";
    static const char32_t ifString[] = U"if";
    static const char32_t elseString[] = U"else";
    static const char32_t forString[] = U"for";

    keywords_.insert(Container::VectorView<const char32_t>(letString,3),TokenType::KEYWORD_LET);
    keywords_.insert(Container::VectorView<const char32_t>(ifString,2),TokenType::KEYWORD_IF);
    keywords_.insert(Container::VectorView<const char32_t>(elseString,4),TokenType::KEYWORD_ELSE);
    keywords_.insert(Container::VectorView<const char32_t>(forString,3),TokenType::KEYWORD_FOR);
}

template<typename CharType>
Lexer<CharType>::Lexer(Container::VectorView<const CharType> source):
source_(source),
current_(0)
{
    static bool initialized = false;
    if (!initialized) {
        initializeKeywords();
        initialized = true;
    }
}

template<typename CharType>
Token<CharType> Lexer<CharType>::nextToken()
{
    skipWhiteSpace();

    if (current_ < source_.size())
    {
        std::size_t start = current_;
        
        CharType ch = advance();
        
        if (Strings::isAlpha(ch))
        {
            while (Strings::isAlpha(peek()) || Strings::isDigit(peek()))
                advance();

            const TokenType * tokenPointer =  keywords_.find(source_.subView(start, current_ - start));

            if (tokenPointer != nullptr)
                return {*tokenPointer,source_.subView(start, current_ - start)};
            else
                return {TokenType::IDENTIFIER, source_.subView(start, current_ - start)};   
        }
        
        if (Strings::isDigit(ch))
        {
            while (Strings::isDigit(peek()))
                advance();

            if (peek() == static_cast<CharType>('.')) 
            {
                advance();
                while (Strings::isDigit(peek())) 
                    advance();
            }
            return {TokenType::NUMBER, source_.subView(start,current_ - start)};
        }

        switch (ch)
        {
            case static_cast<CharType>('('):
                return {TokenType::LEFT_BRACKET,source_.subView(start,1)};
            case static_cast<CharType>(')'):
                return {TokenType::RIGHT_BRACKET,source_.subView(start,1)};
            case static_cast<CharType>('{'):
                return {TokenType::LEFT_BRACE,source_.subView(start,1)};
            case static_cast<CharType>('}'):
                return {TokenType::RIGHT_BRACE,source_.subView(start,1)};
            case static_cast<CharType>(','):
                return {TokenType::COMMA,source_.subView(start,1)};
            case static_cast<CharType>(';'):
                return {TokenType::SEMICOLON,source_.subView(start,1)};
            case static_cast<CharType>('"'):
            {
                start++;
                while (peek() != static_cast<CharType>('"') && peek() != static_cast<CharType>('\0'))
                    advance();
                
                if (peek() == static_cast<CharType>('\0')) 
                    return {TokenType::ILLEGAL, source_.subView(start - 1, current_ - (start - 1))};

                auto literal = source_.subView(start, current_ - start);
                advance();
                return {TokenType::STRING, literal};
            }
            case static_cast<CharType>('+'):
                return {TokenType::PLUS,source_.subView(start,1)};
            case static_cast<CharType>('-'):
                return {TokenType::MINUS,source_.subView(start,1)};
            case static_cast<CharType>('*'):
                return {TokenType::ASTERIST,source_.subView(start,1)};
            case static_cast<CharType>('/'):
                return {TokenType::SLASH,source_.subView(start,1)};
            case static_cast<CharType>('='):
            {
                if (peek() == static_cast<CharType>('='))
                {   
                    advance();
                    return {TokenType::EQUAL,source_.subView(start,2)};
                }
                else
                {
                    return {TokenType::ASSIGN,source_.subView(start,1)};
                }
            }
            case static_cast<CharType>('<'):
            {
                if (peek() == static_cast<CharType>('='))
                {
                    advance();
                    return {TokenType::LESS_EQUAL,source_.subView(start,2)};
                }
                else
                {
                    return {TokenType::LESS_THAN,source_.subView(start,1)};
                }
            }
            case static_cast<CharType>('>'):
            {
                if (peek() == static_cast<CharType>('='))
                {
                    advance();
                    return {TokenType::GREATER_EQUAL,source_.subView(start,2)};
                }
                else
                {
                    return {TokenType::GREATER_THAN,source_.subView(start,1)};
                }
            }
            case static_cast<CharType>('!'):
            {
                if (peek() == static_cast<CharType>('='))
                {
                    advance();
                    return {TokenType::NOT_EQUAL,source_.subView(start,2)};
                }
                else
                {
                    return {TokenType::ILLEGAL, source_.subView(start,1)};
                }
            }
            case static_cast<CharType>('.'):
                return {TokenType::DOT, source_.subView(start,1)};
        }
        return {TokenType::ILLEGAL, source_.subView(start, 1)};
    }
    else
    {
        return {TokenType::END_OF_FILE, Container::VectorView<const CharType>()};
    }

}

}
}