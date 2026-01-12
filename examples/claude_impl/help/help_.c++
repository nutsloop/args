#include "../help.h++"
#include "../help/text/help.h++"

namespace nutsloop::claude_impl {

std::string help::help_() const { return std::string(HELP_NAME_) + HELP_; }

} // namespace nutsloop::claude_impl
