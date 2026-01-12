#include "../help.h++"
#include "../help/text/config_file.h++"

namespace nutsloop::claude_impl {

std::string help::config_file_() const { return std::string(CONFIG_FILE_NAME_) + CONFIG_FILE_; }

} // namespace nutsloop::claude_impl
