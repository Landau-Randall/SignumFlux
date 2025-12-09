#include <gtest/gtest.h>
#include "sigflx_lib/sigflx_container_vector_view.h"
#include "sigflx_lib/sigflx_container_map.h"
#include "scripting/sigflx_script_lexer.h"

using namespace SignumFlux::Container;

TEST(MapTest,FindAndInsert)
{
    using namespace SignumFlux::Script;
    using TestMap = Map<VectorView<const char>,TokenType>;
    using TestView = VectorView<const char>;
    TestMap dict(20);

    EXPECT_EQ(dict.size(),32);

    TestView LET("let",3);
    TestView IF("if",2);
    TestView ELSE("else",4);
    TestView FOR("for",3);

    dict.insert(LET,TokenType::KEYWORD_LET);
    dict.insert(IF,TokenType::KEYWORD_IF);
    dict.insert(ELSE,TokenType::KEYWORD_ELSE);
    dict.insert(FOR,TokenType::KEYWORD_FOR);

    const TokenType * testtoken = dict.find(LET);
    const TokenType * testtoken2 = dict.find(FOR);

    EXPECT_EQ(*testtoken,TokenType::KEYWORD_LET);
    EXPECT_EQ(*testtoken2,TokenType::KEYWORD_FOR);
}
