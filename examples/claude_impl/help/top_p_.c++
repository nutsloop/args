#include "../help.h++"
#include "../help/text/top_p.h++"

namespace nutsloop::claude_impl {

std::string help::top_p_() const { return std::string(TOP_P_NAME_) + TOP_P_; }

} // namespace nutsloop::claude_impl
