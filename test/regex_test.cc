#include <gtest/gtest.h>
#include <regex>
#include <rue_tokenizer.h>

TEST(MatchNumLitTest, RegexAssertions)
{
    std::vector<std::string> matches = {"-12.3", "12.3e-4", "1.2e-3.4567", "1", "-.1e-2"};
    std::vector<std::string> non_matches = {"-12.3e", "1e-234.", "e1", "", "e1-", ".-1"};

    for (std::string const &match : matches)
    {
        ASSERT_TRUE(std::regex_match(match, std::regex(RueTokenizer::NUM_LIT_PATTERN)));
    }

    for (std::string const &non_match : non_matches)
    {
        ASSERT_TRUE(std::regex_match(non_match, std::regex(RueTokenizer::NUM_LIT_PATTERN)));
    }
}

TEST(MatchKeywordTest, RegexAssertions)
{
    ASSERT_TRUE(std::regex_match("return", std::regex(RueTokenizer::KEYWORD_PATTERN)));
    ASSERT_TRUE(std::regex_match("exit", std::regex(RueTokenizer::KEYWORD_PATTERN)));
    ASSERT_FALSE(std::regex_match("anything else", std::regex(RueTokenizer::KEYWORD_PATTERN)));
}
