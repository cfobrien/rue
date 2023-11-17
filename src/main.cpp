#include <fstream>
#include <variant>

#include "rue_error.h"
#include "rue_tokenizer.h"

int main(int argc, char *argv[])
{
    RUE_ASSERT(argc >= 2, RueError::RueError::MISSING_INPUT_FILENAME,
               "Missing input source file name. Aborting... (usage: rue <input.rue>)");

    std::string input_filename(argv[1]);
    if (!input_filename.ends_with(".rue"))
    {
        RUE_FAIL(RueError::RueError::INVALID_INPUT_FILENAME, "Input source file must end with '.rue'. Aborting...");
    }

    std::variant<RueError::RueError, std::vector<RueTokenizer::Token>> tokens =
        RueTokenizer::tokenize("return123   return    s1d3r2f23");
    if (std::holds_alternative<std::vector<RueTokenizer::Token>>(tokens))
    {
        std::cout << std::get<std::vector<RueTokenizer::Token>>(tokens).size() << std::endl;
    }

    return EXIT_SUCCESS;
}
