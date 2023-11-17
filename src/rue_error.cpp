#include "rue_error.h"

namespace RueError
{

void _rue_fail(RueError const rue_err_code, std::string_view const rue_err_name, std::string_view const rue_err_msg)
{
    std::cout << "[!!!] " << rue_err_name << " (" << __FILE__ << ": line " << __LINE__
              << ")\n"
                 "[!!!]     "
              << rue_err_msg << std::endl;
    exit((int)rue_err_code);
}

void _rue_assert(bool const cond, RueError const rue_err_code, std::string_view const rue_err_name,
                 std::string_view const rue_err_msg)
{
    if (!cond)
    {
        _rue_fail(rue_err_code, rue_err_name, rue_err_msg);
    }
}

} // namespace RueError
