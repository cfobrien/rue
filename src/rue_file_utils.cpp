#include <format>

#include "rue_error.h"
#include "rue_file_utils.h"

namespace RueConstants
{

std::string constexpr RUE_SOURCE_SUFFIX(".rue");

} // namespace RueConstants

namespace RueFileUtils
{

const std::string_view get_rue_source_file_contents(const std::string_view input_filename)
{
    if (!input_filename.ends_with(RueConstants::RUE_SOURCE_SUFFIX))
    {
        RUE_FAIL(RueError::RueError::INVALID_INPUT_FILENAME,
                 std::format("Input source file must end with '{}'. Aborting...", RueConstants::RUE_SOURCE_SUFFIX));
    }
    return "test";
}

} // namespace RueFileUtils
