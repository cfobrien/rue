#include "rue_tokenizer.h"
#include "rue_ast.h"
#include <algorithm>
#include <regex>

namespace RueTokenizer
{

TokenInfo TOKEN_INFO = {{TokenType::KEYWORD, KEYWORD_PATTERN}, {TokenType::NUM_LIT, NUM_LIT_PATTERN}};

std::map<uint64_t, LexemeInfo> tokenize(std::string const &contents)
{
    auto compare_sub_match_length = [](std::sub_match<std::string::const_iterator> const &lhs,
                                       std::sub_match<std::string::const_iterator> const &rhs) {
        return lhs.length() > rhs.length();
    };

    std::map<uint64_t, LexemeInfo> lexeme_info;
    std::vector<uint64_t> newline_positions;

    std::smatch matches;
    auto const line_break_regex = std::regex(LINE_BREAK_PATTERN);

    for (auto it = std::sregex_iterator(contents.begin(), contents.end(), line_break_regex);
         it != std::sregex_iterator(); it++)
    {
        newline_positions.push_back((*it).position(0));
    }

    for (auto const &token_info : TOKEN_INFO)
    {
        auto const &[token_type, token_pattern] = token_info;
        auto const pattern_regex = std::regex(token_pattern);

        for (auto it = std::sregex_iterator(contents.begin(), contents.end(), pattern_regex);
             it != std::sregex_iterator(); it++)
        {
            auto match = *it;
            uint64_t const pos = match.position(0);
            auto const line_iter =
                std::find_if(newline_positions.begin(), newline_positions.end(),
                             [pos](uint64_t const known_newline_pos) { return known_newline_pos > pos; });
            uint64_t const line = std::distance(newline_positions.begin(), line_iter);
            uint64_t const prev_newline_pos =
                (newline_positions.size() && newline_positions.begin() == line_iter) ? 0 : *(line_iter - 1);
            uint64_t const column = pos - prev_newline_pos;

            lexeme_info[pos] = LexemeInfo(token_type, match[0].length(), line, column);
        }
    }

    /*for (auto const &kv : lexeme_info)
    {
        std::cout << "line " << kv.second.line << " col " << kv.second.column << ": "
                  << contents.substr(kv.first, kv.second.length) << "\n";
    }*/
    return lexeme_info;
}

} // namespace RueTokenizer
