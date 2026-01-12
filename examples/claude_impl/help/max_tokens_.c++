#include "../help.h++"
#include "../help/text/max_tokens.h++"

namespace nutsloop::claude_impl {

std::string help::max_tokens_() const { return std::string(MAX_TOKENS_NAME_) + MAX_TOKENS_; }

} // namespace nutsloop::claude_impl
