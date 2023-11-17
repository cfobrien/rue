#include <fstream>
#include <variant>

#include "rue_error.h"
#include "rue_tokenizer.h"

int main(int argc, char *argv[])
{
    std::variant<RueError::RueError, std::vector<RueTokenizer::Token>> tokens =
        RueTokenizer::tokenize("return123   return    s1d3r2f23");
    if (std::holds_alternative<std::vector<RueTokenizer::Token>>(tokens))
    {
        std::cout << std::get<std::vector<RueTokenizer::Token>>(tokens).size() << std::endl;
    }

    if (argc != 2)
    {
        std::cerr << "Incorrect parameter..." << std::endl;
        std::cerr << "rue <input.rue>" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
