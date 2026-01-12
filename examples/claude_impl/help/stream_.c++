#include "../help.h++"
#include "../help/text/stream.h++"

namespace nutsloop::claude_impl {

std::string help::stream_() const { return std::string(STREAM_NAME_) + STREAM_; }

} // namespace nutsloop::claude_impl
