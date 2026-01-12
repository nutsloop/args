#include "../help.h++"

#include <format>

namespace nutsloop::claude_impl {

std::string help::get_version_() const {

  return std::format("  v{}.{}.{}\n\n", version_info_[0], version_info_[1], version_info_[2]);
}

} // namespace nutsloop::claude_impl
