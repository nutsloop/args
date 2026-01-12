#pragma once

namespace nutsloop::args {

template <typename CheckerClass, typename HelperClass>
  requires ArgsChecker<CheckerClass> && (std::same_as<HelperClass, bool> || ArgsHelper<HelperClass>)
std::string sequencer<CheckerClass, HelperClass>::strip_dashes_() const {
  if (is_single_dash_) {
    return arg_.substr(1, equal_sign_pos_ - 1);
  }
  return arg_.substr(2, equal_sign_pos_ - 2);
}

} // namespace nutsloop::args