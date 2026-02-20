#pragma once

namespace nutsloop::args {
template <typename CheckerClass, typename HelperClass>
  requires ArgsChecker<CheckerClass> && (std::same_as<HelperClass, bool> || ArgsHelper<HelperClass>)
CheckerClass sequencer<CheckerClass, HelperClass>::get_option_addr(const std::string &key) const {
  if (const auto it = arguments_.find(key); it != arguments_.end()) {
    if (std::holds_alternative<std::string>(it->second)) {
      return CheckerClass(std::get<std::string>(it->second));
    }
    throw std::invalid_argument(std::format("--{} accept only string.", key));
  }
  return CheckerClass(nullptr);
}

} // namespace nutsloop::args
