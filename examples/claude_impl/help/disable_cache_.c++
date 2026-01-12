#include "../help.h++"
#include "../help/text/disable_cache.h++"

namespace nutsloop::claude_impl {

std::string help::disable_cache_() const { return std::string(DISABLE_CACHE_NAME_) + DISABLE_CACHE_; }

} // namespace nutsloop::claude_impl
