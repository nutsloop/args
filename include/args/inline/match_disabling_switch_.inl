#pragma once

namespace nutsloop::args {

template <typename CheckerClass, typename HelperClass>
  requires ArgsChecker<CheckerClass> && (std::same_as<HelperClass, bool> || ArgsHelper<HelperClass>)
bool sequencer<CheckerClass, HelperClass>::match_disabling_switch_() {
  if (key_.find("disable-") != std::string::npos) {
    arguments_[key_] = false;
    return true;
  }
  return false;
}

} // namespace nutsloop::args