#include "../help.h++"
#include "../help/text/header.h++"

#include <format>

namespace nutsloop::claude_impl {

std::string help::to_string() {
  auto [text, status] = get_help_topic_(stoenum_());
  return std::format("{}{}", get_noun_name_(), HEADER_) + get_version_() + text;
}

} // namespace nutsloop::claude_impl
