#ifndef RUE_TOKENIZER_H
#define RUE_TOKENIZER_H

#include <cstdint>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

#include "rue_error.h"

namespace RueTokenizer
{

enum class TokenType
{
    KEYWORD,
    USER_DEF_LIT,
    INT_LIT
};

typedef std::pair<TokenType, std::optional<std::string_view>> Token;

// Caller is responsible for passing in a null terminated pattern
constexpr bool is_char_in_pattern(const char seeked_char, std::string const &pat)
{
    for (char const c : pat)
    {
        if (seeked_char == c)
        {
            return true;
        }
    }
    return false;
}

std::string pad_with_ellipsis(std::string const &str, size_t const max_len);
std::variant<RueError::RueError, std::vector<RueTokenizer::Token>> tokenize(std::string_view const contents);

} // namespace RueTokenizer

#endif // RUE_TOKENIZER_H
