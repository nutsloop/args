#include "../help.h++"
#include "../help/text/nouns.h++"

namespace nutsloop::claude_impl {

std::string help::get_noun_name_() const {

  std::string message(NAME_);

  return message;
}

} // namespace nutsloop::claude_impl
