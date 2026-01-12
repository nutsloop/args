#include "../help.h++"
#include "../help/text/verbose.h++"

namespace nutsloop::claude_impl {

std::string help::verbose_() const { return std::string(VERBOSE_NAME_) + VERBOSE_; }

} // namespace nutsloop::claude_impl
