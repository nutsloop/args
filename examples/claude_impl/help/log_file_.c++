#include "../help.h++"
#include "../help/text/log_file.h++"

namespace nutsloop::claude_impl {

std::string help::log_file_() const { return std::string(LOG_FILE_NAME_) + LOG_FILE_; }

} // namespace nutsloop::claude_impl
