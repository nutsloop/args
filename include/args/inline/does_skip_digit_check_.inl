#pragma once

namespace nutsloop::args {

template <typename CheckerClass, typename HelperClass>
  requires ArgsChecker<CheckerClass> && (std::same_as<HelperClass, bool> || ArgsHelper<HelperClass>)
bool sequencer<CheckerClass, HelperClass>::does_skip_digit_check_() const {
  // Assuming skip_digit_check_ and key_ are members
  return skip_digit_check_.contains(key_);
}

} // namespace nutsloop::args