#ifndef RUE_ERROR_H
#define RUE_ERROR_H

namespace RueError
{

#define RUE_FAIL(rue_err, rue_err_msg)                                                                                 \
    std::cout << "[!!!] " << #rue_err << " (" << __FILE__ << ": line " << __LINE__                                     \
              << ")\n"                                                                                                 \
                 "[!!!]     "                                                                                          \
              << rue_err_msg << std::endl;                                                                             \
    exit((int)rue_err)

enum class RueError
{
    SUCCESS,
    NO_CONTENT,
    UNKNOWN_TOKEN,
};

} // namespace RueError

#endif // RUE_ERROR_H
