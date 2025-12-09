#pragma once

#include <cstddef>
#include "sigflx_lib/sigflx_container_vector_view.h"
#include "sigflx_lib/sigflx_strings_check.h"
#include "sigflx_lib/sigflx_container_map.h"

namespace SignumFlux
{
namespace Script
{
enum class TokenType
{
    LEFT_BRACKET,RIGHT_BRACKET,
    LEFT_BRACE,RIGHT_BRACE,
    COMMA,
    SEMICOLON,
    DOT,

    ILLEGAL,
    END_OF_FILE,

    IDENTIFIER,
    STRING,
    NUMBER,
    VARIANT,

    ASSIGN,
    PLUS,
    MINUS,
    ASTERIST,
    SLASH,

    EQUAL,
    NOT_EQUAL,
    LESS_THAN,
    GREATER_THAN,
    LESS_EQUAL,
    GREATER_EQUAL,

    KEYWORD_LET,
    KEYWORD_IF,
    KEYWORD_ELSE,
    KEYWORD_FOR
};

static inline const char * tokenToString(TokenType token);

template<typename CharType>
struct Token
{
    TokenType type;
    //Strings::StringView literal;
    Container::VectorView<const CharType> literal;
};

template<typename CharType>
class Lexer
{
private:
    Container::VectorView<const CharType> source_;
    std::size_t current_;

    void skipWhiteSpace();
    CharType peek() const;
    CharType advance();

    static Container::Map<Container::VectorView<const CharType>, TokenType> keywords_;
    static void initializeKeywords();  // 初始化函数

public:
    Lexer() = default;
    Lexer(const Lexer & object) = default;
    Lexer(Lexer && object) = default;
    Lexer(Container::VectorView<const CharType> source);

    ~Lexer() = default;

    Token<CharType> nextToken();
};
}
}

#include "../../src/scripting/sigflx_script_lexer.tpp"