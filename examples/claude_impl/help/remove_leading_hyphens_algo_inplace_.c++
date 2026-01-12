#include "../help.h++"

#include <algorithm>

namespace nutsloop::claude_impl {

void help::remove_leading_hyphens_algo_inplace_() {
  const auto it =
      std::find_if_not(look_up_option_.begin(), look_up_option_.end(),
                       [](const char c) { return c == '-'; });
  look_up_option_.erase(look_up_option_.begin(), it);
}

} // namespace nutsloop::claude_impl
