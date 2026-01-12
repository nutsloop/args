#include "../help.h++"
#include "../help/text/header.h++"

#include <iostream>

namespace nutsloop::claude_impl {

int help::print() {
  auto [text, status] = get_help_topic_(stoenum_());
  std::cout << get_noun_name_();
  std::cout << HEADER_;
  std::cout << get_version_();
  std::cout << text << std::endl;
  return status;
}

} // namespace nutsloop::claude_impl
