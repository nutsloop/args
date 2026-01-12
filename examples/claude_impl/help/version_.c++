#include "../help.h++"
#include "../help/text/version.h++"

namespace nutsloop::claude_impl {

std::string help::version_topic_() const { return std::string(VERSION_NAME_) + VERSION_; }

} // namespace nutsloop::claude_impl
