#include <format>
#include <fstream>
#include <variant>

#include "rue_error.h"
#include "rue_file_utils.h"
#include "rue_tokenizer.h"

int main(int argc, char *argv[])
{
    RUE_ASSERT(argc >= 2, RueError::RueError::MISSING_INPUT_FILENAME,
               std::format("Missing input source file name. Aborting... (usage: rue <input>{})",
                           RueConstants::RUE_SOURCE_SUFFIX));

    std::string input_filename(argv[1]);
    std::variant<RueError::RueError, std::vector<RueTokenizer::Token>> tokens =
        RueTokenizer::tokenize("return123   return    s1d3r2f23");
    if (std::holds_alternative<std::vector<RueTokenizer::Token>>(tokens))
    {
        std::cout << std::get<std::vector<RueTokenizer::Token>>(tokens).size() << std::endl;
    }

    return EXIT_SUCCESS;
}
