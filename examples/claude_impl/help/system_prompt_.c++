#include "../help.h++"
#include "../help/text/system_prompt.h++"

namespace nutsloop::claude_impl {

std::string help::system_prompt_() const { return std::string(SYSTEM_PROMPT_NAME_) + SYSTEM_PROMPT_; }

} // namespace nutsloop::claude_impl
