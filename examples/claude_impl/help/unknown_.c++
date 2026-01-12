#include "../help.h++"
#include "../help/text/unknown.h++"

namespace nutsloop::claude_impl {

std::string help::unknown_() const { return std::string(UNKNOWN_NAME_) + UNKNOWN_; }

} // namespace nutsloop::claude_impl
