#include <gtest/gtest.h>
#include "sigflx_lib/sigflx_strings_check.h"

TEST(CharTest,CharTyptCheck)
{
    using namespace SignumFlux::Strings;
    char test1 = 'a';
    char test2 = '1';
    char test3 = 'B';
    char test4 = '\n';
    EXPECT_TRUE(isAlnum(test1));
    EXPECT_TRUE(isAlnum(test2));
    EXPECT_TRUE(isAlnum(test3));
    EXPECT_FALSE(isAlnum(test4));

    EXPECT_TRUE(isAlpha(test1));
    EXPECT_TRUE(isAlpha('_'));
    EXPECT_TRUE(isAlpha(test3));
    EXPECT_FALSE(isAlpha(test4));

    EXPECT_FALSE(isUpper(test1));
    EXPECT_FALSE(isUpper(test2));
    EXPECT_TRUE(isUpper(test3));
    EXPECT_FALSE(isUpper(test4));

    EXPECT_TRUE(isLower(test1));
    EXPECT_FALSE(isLower(test2));
    EXPECT_FALSE(isLower(test3));
    EXPECT_FALSE(isLower(test4));

    EXPECT_FALSE(isDigit(test1));
    EXPECT_TRUE(isDigit(test2));
    EXPECT_FALSE(isDigit(test3));
    EXPECT_FALSE(isDigit(test4));

    EXPECT_FALSE(isSpace(test1));
    EXPECT_FALSE(isSpace(test2));
    EXPECT_FALSE(isSpace(test3));
    EXPECT_TRUE(isSpace(test4));
    
}