#include "../help.h++"
#include "../help/text/temperature.h++"

namespace nutsloop::claude_impl {

std::string help::temperature_() const { return std::string(TEMPERATURE_NAME_) + TEMPERATURE_; }

} // namespace nutsloop::claude_impl
