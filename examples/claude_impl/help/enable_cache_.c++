#include "../help.h++"
#include "../help/text/enable_cache.h++"

namespace nutsloop::claude_impl {

std::string help::enable_cache_() const { return std::string(ENABLE_CACHE_NAME_) + ENABLE_CACHE_; }

} // namespace nutsloop::claude_impl
