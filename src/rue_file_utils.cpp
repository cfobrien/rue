#include <format>
#include <fstream>
#include <iostream>

#include "rue_error.h"
#include "rue_file_utils.h"

namespace RueConstants
{

std::string constexpr RUE_SOURCE_SUFFIX(".rue");

} // namespace RueConstants

namespace RueFileUtils
{

const std::string get_rue_source_file_contents(std::string const &input_filename)
{
    if (!input_filename.ends_with(RueConstants::RUE_SOURCE_SUFFIX))
    {
        RUE_FAIL(RueError::RueError::INVALID_INPUT_FILENAME,
                 std::format("Input source file must end with '{}'. Aborting...", RueConstants::RUE_SOURCE_SUFFIX));
    }

    std::ifstream input_file;
    input_file.open(input_filename, std::ios::in);
    RUE_ASSERT(input_file.is_open(), RueError::RueError::CANNOT_OPEN_FILE,
               std::format("Cannot open input file '{}'", input_filename));

    std::string line_contents, input_file_contents;
    while (getline(input_file, line_contents))
    {
        input_file_contents += line_contents + '\n';
    }

    RUE_ASSERT(input_file_contents.length(), RueError::RueError::EMPTY_INPUT_FILE,
               std::format("Found no contents in input file '{}'", input_filename));

    input_file.close();
    RUE_ASSERT(!input_file.is_open(), RueError::RueError::CANNOT_CLOSE_FILE,
               std::format("Cannot close input file '{}'", input_filename));

    return input_file_contents;
}

} // namespace RueFileUtils
