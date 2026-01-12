#include "../help.h++"
#include "../help/text/output_dir.h++"

namespace nutsloop::claude_impl {

std::string help::output_dir_() const { return std::string(OUTPUT_DIR_NAME_) + OUTPUT_DIR_; }

} // namespace nutsloop::claude_impl
