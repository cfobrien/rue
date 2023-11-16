#include <cstdint>
#include <fstream>
#include <iostream>
#include <optional>
#include <string_view>
#include <variant>
#include <vector>

#define RUE_FAIL(rue_err, rue_err_msg)                                                                                 \
    std::cout << "[!!!] " << #rue_err << " (" << __FILE__ << ": line " << __LINE__                                     \
              << ")\n"                                                                                                 \
                 "[!!!]     "                                                                                          \
              << rue_err_msg << std::endl;                                                                             \
    exit((int)rue_err)

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

enum class TokenType
{
    KEYWORD,
    USER_DEF_LIT,
    INT_LIT
};

enum class RueError
{
    SUCCESS,
    NO_CONTENT,
    UNKNOWN_TOKEN,
    ITCHY_BALLS
};

typedef std::pair<TokenType, std::optional<std::string_view>> Token;

// Caller is responsible for passing in a null terminated pattern
constexpr bool is_char_in_pattern(const char c, const char *pat)
{
    for (const char *pos = pat; *pos != '\0'; pos++)
    {
        if (*pos == c)
        {
            return true;
        }
    }
    return false;
}

constexpr std::string pad_with_ellipsis(std::string const &str, size_t const max_len)
{
    std::string padded;
    if (!str.length())
    {
        RUE_FAIL(RueError::NO_CONTENT, "Cannot pad empty string with ellipses");
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

std::variant<RueError, std::vector<Token>> tokenize(std::string_view const contents)
{
    if (contents.empty())
    {
        RUE_FAIL(RueError::NO_CONTENT, "Can't tokenize empty string. Aborting...");
    }

    uint32_t pos = 0;
    std::vector<Token> tokens;

    while (contents.length() >= pos)
    {
        std::string_view contents_tail(contents.data() + pos);
        pos += contents_tail.find_first_not_of(Constants::pmtd_whitespace);

        // check if current pos corresponds to the start of a keyword
        if (is_char_in_pattern(contents.at(pos), Constants::pmtd_keyword))
        {
            std::string_view longest_matching_keyword;

            for (std::string_view str : Constants::supported_keywords)
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
                tokens.push_back({TokenType::KEYWORD, std::optional(longest_matching_keyword)});
                pos += longest_matching_keyword.length();
                continue;
            }
        }

        // We expect to have identified all tokens at this point in our loop.
        // Since we haven't, this means we're facing an unknown token. Let's
        // truncate at the nearest sign of whitespace and report our findings.
        std::string_view first_unknown_token(contents_tail.data(),
                                             contents_tail.find_first_of(Constants::pmtd_whitespace));

        RUE_FAIL(RueError::UNKNOWN_TOKEN,
                 "Unknown token is: " + pad_with_ellipsis(std::string(first_unknown_token), 15));
    }
    return RueError::SUCCESS;
}

int main(int argc, char *argv[])
{
    std::variant<RueError, std::vector<Token>> tokens = tokenize("return123   return    s1d3r2f23");
    if (std::holds_alternative<std::vector<Token>>(tokens))
    {
        std::cout << std::get<std::vector<Token>>(tokens).size() << std::endl;
    }

    if (argc != 2)
    {
        std::cerr << "Incorrect parameter..." << std::endl;
        std::cerr << "rue <input.rue>" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
