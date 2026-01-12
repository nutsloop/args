#pragma once

namespace nutsloop::args {

template <typename CheckerClass, typename HelperClass>
  requires ArgsChecker<CheckerClass> && (std::same_as<HelperClass, bool> || ArgsHelper<HelperClass>)
CheckerClass sequencer<CheckerClass, HelperClass>::get_option_bool(const std::string &key) const {
  if (const auto it = arguments_.find(key); it != arguments_.end()) {
    if (std::holds_alternative<bool>(it->second)) {
      return CheckerClass(std::get<bool>(it->second));
    }

    std::string boolean = "`true`";
    if (it->first.find("enable-") != std::string::npos) {
      boolean = "`true`";
    } else if (it->first.find("disable-") != std::string::npos) {
      boolean = "`false`";
    }

    throw std::invalid_argument(std::format(
        "--{} is a simple switch that returns {} and should omit the `=` sign.", key, boolean));
  }
  return CheckerClass(nullptr);
}

} // namespace nutsloop::args
