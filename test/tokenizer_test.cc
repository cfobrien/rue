#include <gtest/gtest.h>
#include <rue_tokenizer.h>

struct TokenizerTest : testing::Test
{
    std::string test;
};

TEST(IsCharInPatternTest, TokenizerAssertions)
{
    ASSERT_TRUE(RueTokenizer::is_char_in_pattern('r', "rue"));
    ASSERT_FALSE(RueTokenizer::is_char_in_pattern('R', "rue"));
    ASSERT_TRUE(RueTokenizer::is_char_in_pattern('\t', "with\ttab"));
    ASSERT_TRUE(RueTokenizer::is_char_in_pattern(' ', "with space"));
    ASSERT_TRUE(RueTokenizer::is_char_in_pattern('\n', "with\nnewline"));
}

TEST(EllipsisPaddingTest, TokenizerAssertions)
{
    ASSERT_EQ("Symb0l$", RueTokenizer::pad_with_ellipsis("Symb0l$", 99));
    ASSERT_EQ("Rue", RueTokenizer::pad_with_ellipsis("Rue", 3));
    ASSERT_EQ("Rue", RueTokenizer::pad_with_ellipsis("Rue", 1));
    ASSERT_EQ("R...", RueTokenizer::pad_with_ellipsis("Rue", 4));
}
