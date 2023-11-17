#ifndef RUE_ERROR_H
#define RUE_ERROR_H

#include <iostream>
#include <string_view>

namespace RueError
{

#define RUE_FAIL(rue_err, rue_err_msg) _rue_fail(rue_err, #rue_err, rue_err_msg)

#define RUE_ASSERT(cond, rue_err, rue_err_msg) _rue_assert((cond), rue_err, #rue_err, rue_err_msg)

enum class RueError
{
    SUCCESS,
    NO_CONTENT,
    UNKNOWN_TOKEN,
    INVALID_INPUT_FILENAME,
    MISSING_INPUT_FILENAME
};

void _rue_fail(RueError const rue_err_code, std::string_view const rue_err_name, std::string_view const rue_err_msg);
void _rue_assert(bool const cond, RueError const rue_err_code, std::string_view const rue_err_name,
                 std::string_view const rue_err_msg);

} // namespace RueError

#endif // RUE_ERROR_H
