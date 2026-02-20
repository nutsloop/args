#pragma once

namespace nutsloop::args {

template <typename CheckerClass, typename HelperClass>
  requires ArgsChecker<CheckerClass> && (std::same_as<HelperClass, bool> || ArgsHelper<HelperClass>)
void sequencer<CheckerClass, HelperClass>::match_truthy_switch_() {
  arguments_[key_] = true;
}

} // namespace nutsloop::args