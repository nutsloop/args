#pragma once

namespace nutsloop::args {

template <typename CheckerClass, typename HelperClass>
  requires ArgsChecker<CheckerClass> && (std::same_as<HelperClass, bool> || ArgsHelper<HelperClass>)
void sequencer<CheckerClass, HelperClass>::process_dashes_() {
  if (arg_.at(0) == '-') {
    if (arg_.at(1) == '-') {
      is_single_dash_ = false;
    } else {
      is_single_dash_ = true;
    }
  }
}

} // namespace nutsloop::args