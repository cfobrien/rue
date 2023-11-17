#ifndef RUE_FILE_UTILS_H
#define RUE_FILE_UTILS_H

#include <string>
#include <string_view>

namespace RueConstants
{

extern const std::string RUE_SOURCE_SUFFIX;

} // namespace RueConstants

namespace RueFileUtils
{

const std::string_view get_rue_source_file_contents(const std::string_view input_filename);

} // namespace RueFileUtils

#endif // RUE_FILE_UTILS_H
