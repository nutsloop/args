#pragma once

namespace nutsloop::args{

template <typename CheckerClass, typename HelperClass>
  requires ArgsChecker<CheckerClass> && (std::same_as<HelperClass, bool> || ArgsHelper<HelperClass>)
bool sequencer<CheckerClass, HelperClass>::is_digit_() const { // Ensure this is const
  return !value_.empty() && std::all_of(value_.begin(), value_.end(),
                                        [](const unsigned char c) { return std::isdigit(c); });
}

} // namespace nutsloop::args