#include "../help.h++"
#include "../help/text/timeout.h++"

namespace nutsloop::claude_impl {

std::string help::timeout_() const { return std::string(TIMEOUT_NAME_) + TIMEOUT_; }

} // namespace nutsloop::claude_impl
