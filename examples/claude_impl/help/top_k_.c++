#include "../help.h++"
#include "../help/text/top_k.h++"

namespace nutsloop::claude_impl {

std::string help::top_k_() const { return std::string(TOP_K_NAME_) + TOP_K_; }

} // namespace nutsloop::claude_impl
