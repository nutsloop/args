#pragma once

namespace nutsloop::args {

template <typename CheckerClass, typename HelperClass>
  requires ArgsChecker<CheckerClass> && (std::same_as<HelperClass, bool> || ArgsHelper<HelperClass>)
CheckerClass sequencer<CheckerClass, HelperClass>::get_option_uint(const std::string &key) const {
  if (const auto it = arguments_.find(key); it != arguments_.end()) {
    if (std::holds_alternative<unsigned long long>(it->second)) {
      return CheckerClass(std::get<unsigned long long>(it->second));
    }
    throw std::invalid_argument(std::format("--{} accept only integer, in the range of int.", key));
  }
  return CheckerClass(nullptr);
}

} // namespace nutsloop::args
