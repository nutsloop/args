#pragma once

namespace nutsloop::args {

template <typename CheckerClass, typename HelperClass>
  requires ArgsChecker<CheckerClass> && (std::same_as<HelperClass, bool> || ArgsHelper<HelperClass>)
bool sequencer<CheckerClass, HelperClass>::should_interpret_as_ull_() const {
  if (does_skip_digit_check_()) {
    return false;
  }
  return is_digit_() && is_in_ull_range_();
}

} // namespace nutsloop::args