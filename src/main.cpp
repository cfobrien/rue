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

    std::string const &input_file_contents = RueFileUtils::get_rue_source_file_contents(argv[1]);

    std::variant<RueError::RueError, std::vector<RueTokenizer::Token>> tokens =
        RueTokenizer::tokenize(input_file_contents);
    if (std::holds_alternative<std::vector<RueTokenizer::Token>>(tokens))
    {
        std::cout << std::get<std::vector<RueTokenizer::Token>>(tokens).size() << std::endl;
    }

    return EXIT_SUCCESS;
}
