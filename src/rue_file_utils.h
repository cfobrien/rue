#ifndef RUE_FILE_UTILS_H
#define RUE_FILE_UTILS_H

#include <string>

namespace RueConstants
{

extern const std::string RUE_SOURCE_SUFFIX;

} // namespace RueConstants

namespace RueFileUtils
{

const std::string get_rue_source_file_contents(std::string const &input_filename);

} // namespace RueFileUtils

#endif // RUE_FILE_UTILS_H
