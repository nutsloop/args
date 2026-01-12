#include "../help.h++"
#include "../help/text/output_format.h++"

namespace nutsloop::claude_impl {

std::string help::output_format_() const { return std::string(OUTPUT_FORMAT_NAME_) + OUTPUT_FORMAT_; }

} // namespace nutsloop::claude_impl
