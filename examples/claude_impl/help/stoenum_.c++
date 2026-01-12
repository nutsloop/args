#include "../help.h++"

namespace nutsloop::claude_impl {

help::Topic_ help::stoenum_() {

  remove_leading_hyphens_algo_inplace_();
  const auto it = option_list_.find(look_up_option_);
  return (it != option_list_.end()) ? it->second : Topic_::unknown;
}

} // namespace nutsloop::claude_impl
