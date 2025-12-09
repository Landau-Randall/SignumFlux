#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include "sigflx_lib/sigflx_container_vector_view.h"
#include "scripting/sigflx_script_lexer.h"
#include "sigflx_lib/sigflx_strings_c_methods.h"
#define EXPECT_VIEW_EQ(view, c_str) \
    do { \
        const char* expected_str = (c_str); \
        size_t expected_len = strlen(expected_str); \
        EXPECT_EQ((view).size(), expected_len); \
        EXPECT_EQ(strncmp((view).data(), expected_str, expected_len), 0); \
    } while (0)

TEST(LexerTest,TokenTest1)
{
    const char * test_text = 
    "\
        let frequency = 440.0; \n \
        let phase = 1.0; \n \
        let sampleRate = 44100.0; \n \
        let oscillator = basic_generator(\"sine\",frequency,sampleRate,phase); \n \
        let signalOne = Signal; \n \
        oscillator.generate(signalOne); \n \
        if (signalOne != zeroSignal) \n \
        { \n \
            audio.combination(signalOne,SignalTwo); \n \
            for (audio) \n  \
            { \n \
               audio.play(); \n  \
            } \n \
        } \n \
        else \n \
        { \n \
            print(\" sound lost \") \n \
        } \n ";
    SignumFlux::Container::VectorView<const char> test_view(test_text,SignumFlux::Strings::stringLength(test_text));
    SignumFlux::Script::Lexer<char> test_lexer(test_view);
    std::vector<SignumFlux::Script::Token<char>> test_vector;
    auto token = test_lexer.nextToken();
    while (token.type != SignumFlux::Script::TokenType::END_OF_FILE)
    {
        test_vector.push_back(token);
        token = test_lexer.nextToken();
    }
    for (const auto & toke : test_vector)
    {
        for (std::size_t i = 0;i < toke.literal.size();++i)
        {
            std::cout <<  toke.literal[i];
        }
        SignumFlux::Script::TokenType token = toke.type;
        std::cout << " : " << SignumFlux::Script::tokenToString(toke.type) << std::endl;
    }

}