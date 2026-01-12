#include "../help.h++"
#include "../help/text/disable_safety.h++"

namespace nutsloop::claude_impl {

std::string help::disable_safety_() const { return std::string(DISABLE_SAFETY_NAME_) + DISABLE_SAFETY_; }

} // namespace nutsloop::claude_impl
