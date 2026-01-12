#include "../help.h++"
#include "../help/text/api_key.h++"

namespace nutsloop::claude_impl {

std::string help::api_key_() const { return std::string(API_KEY_NAME_) + API_KEY_; }

} // namespace nutsloop::claude_impl
