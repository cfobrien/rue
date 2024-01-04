#ifndef RUE_TOKENIZER_H
#define RUE_TOKENIZER_H

#include <cstdint>
#include <iostream>
#include <map>
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
    NUM_LIT,
    BIN_OPERATOR,
    STRING_LIT
};

typedef std::pair<TokenType, std::optional<std::string_view>> Token;
typedef std::map<TokenType, std::string> TokenInfo;
typedef struct
{
    TokenType type;
    uint64_t length;
    uint64_t line;
    uint64_t column;
} LexemeInfo;

std::string const LINE_BREAK_PATTERN = "\n|\r\n|\r|\n\r";
std::string const NUM_LIT_PATTERN = "-?[0-9]*\\.?[0-9]+(e-?[0-9]*\\.?[0-9]+)?";
std::string const KEYWORD_PATTERN = "return|exit";

std::map<uint64_t, LexemeInfo> tokenize(std::string const &contents);

} // namespace RueTokenizer

#endif // RUE_TOKENIZER_H
