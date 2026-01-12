#include "../help.h++"
#include "../help/text/retry_count.h++"

namespace nutsloop::claude_impl {

std::string help::retry_count_() const { return std::string(RETRY_COUNT_NAME_) + RETRY_COUNT_; }

} // namespace nutsloop::claude_impl
