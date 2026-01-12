#include "../help.h++"
#include "../help/text/context_window.h++"

namespace nutsloop::claude_impl {

std::string help::context_window_() const { return std::string(CONTEXT_WINDOW_NAME_) + CONTEXT_WINDOW_; }

} // namespace nutsloop::claude_impl
