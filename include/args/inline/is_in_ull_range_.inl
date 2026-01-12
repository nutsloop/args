#pragma once

namespace nutsloop::args {

template <typename CheckerClass, typename HelperClass>
  requires ArgsChecker<CheckerClass> && (std::same_as<HelperClass, bool> || ArgsHelper<HelperClass>)
bool sequencer<CheckerClass, HelperClass>::is_in_ull_range_() const {
  // Assuming value_ is a member
  // PRECONDITION: value_ should be a non-empty string of digits.
  static const std::string max_value_str =
      std::to_string(std::numeric_limits<unsigned long long>::max());
  return value_.size() < max_value_str.size() ||
         (value_.size() == max_value_str.size() && value_ <= max_value_str);
}

} // namespace nutsloop::args