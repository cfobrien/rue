#include "rue_tokenizer.h"

namespace RueTokenizer
{

namespace Constants
{
const char *pmtd_whitespace = " \t\n\r";
const char *pmtd_keyword = "abcdefghijklmnopqrstuvwyxz";
const char *pmtd_user_def_lit_head = "ABCDEFGHIJKLMNOPQRSTUVWYXZ"
                                     "abcdefghijklmnopqrstuvwyxz"
                                     "_";
const char *pmtd_user_def_lit_tail = "ABCDEFGHIJKLMNOPQRSTUVWYXZ"
                                     "abcdefghijklmnopqrstuvwyxz"
                                     "0123456789_";
const char *pmtd_int_lit = "0123456789";

std::vector<std::string_view> supported_keywords = {"return"};
} // namespace Constants

std::string pad_with_ellipsis(std::string const &str, size_t const max_len)
{
    std::string padded;
    if (!str.length())
    {
        RUE_FAIL(RueError::RueError::NO_CONTENT, "Cannot pad empty string with ellipses");
    }
    if (str.length() <= max_len)
    {
        padded = str;
    }
    else
    {
        padded = str.substr(0, max_len - 3) + "...";
    }
    return padded;
}

std::variant<RueError::RueError, std::vector<RueTokenizer::Token>> tokenize(std::string_view const contents)
{
    if (contents.empty())
    {
        RUE_FAIL(RueError::RueError::NO_CONTENT, "Can't tokenize empty string. Aborting...");
    }

    uint32_t pos = 0;
    std::vector<RueTokenizer::Token> tokens;

    while (contents.length() >= pos)
    {
        std::string_view contents_tail(contents.data() + pos);
        pos += contents_tail.find_first_not_of(RueTokenizer::Constants::pmtd_whitespace);

        // check if current pos corresponds to the start of a keyword
        if (is_char_in_pattern(contents.at(pos), RueTokenizer::Constants::pmtd_keyword))
        {
            std::string_view longest_matching_keyword;

            for (std::string_view str : RueTokenizer::Constants::supported_keywords)
            {
                if (contents_tail.starts_with(str))
                {
                    if (str.length() > longest_matching_keyword.length())
                    {
                        longest_matching_keyword = str;
                    }
                }
            }

            if (longest_matching_keyword.length() > 0)
            {
                // found our keyword, advance pos and start fresh
                tokens.push_back({RueTokenizer::TokenType::KEYWORD, std::optional(longest_matching_keyword)});
                pos += longest_matching_keyword.length();
                continue;
            }
        }

        // We expect to have identified all tokens at this point in our loop.
        // Since we haven't, this means we're facing an unknown token. Let's
        // truncate at the nearest sign of whitespace and report our findings.
        std::string_view first_unknown_token(contents_tail.data(),
                                             contents_tail.find_first_of(RueTokenizer::Constants::pmtd_whitespace));

        RUE_FAIL(RueError::RueError::UNKNOWN_TOKEN,
                 "Unknown token is: " + pad_with_ellipsis(std::string(first_unknown_token), 15));
    }
    return RueError::RueError::SUCCESS;
}

} // namespace RueTokenizer