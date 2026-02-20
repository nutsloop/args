#pragma once

namespace nutsloop::args {

template <typename CheckerClass, typename HelperClass>
  requires ArgsChecker<CheckerClass> && (std::same_as<HelperClass, bool> || ArgsHelper<HelperClass>)
bool sequencer<CheckerClass, HelperClass>::has(const std::string &key) const {
  return arguments_.contains(key);
}

} // namespace nutsloop::args