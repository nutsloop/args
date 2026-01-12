#include "../help.h++"
#include "../help/text/log_level.h++"

namespace nutsloop::claude_impl {

std::string help::log_level_() const { return std::string(LOG_LEVEL_NAME_) + LOG_LEVEL_; }

} // namespace nutsloop::claude_impl
