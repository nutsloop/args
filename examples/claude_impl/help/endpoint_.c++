#include "../help.h++"
#include "../help/text/endpoint.h++"

namespace nutsloop::claude_impl {

std::string help::endpoint_() const { return std::string(ENDPOINT_NAME_) + ENDPOINT_; }

} // namespace nutsloop::claude_impl
