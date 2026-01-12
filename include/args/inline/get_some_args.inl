#pragma once

namespace nutsloop::args {

template <typename CheckerClass, typename HelperClass>
  requires ArgsChecker<CheckerClass> && (std::same_as<HelperClass, bool> || ArgsHelper<HelperClass>)
args_t
sequencer<CheckerClass, HelperClass>::get_some_args(const std::vector<std::string> &selection) const {

  args_t some_arguments;
  for (auto &selected : selection) {
    if (arguments_.contains(selected)) {
      some_arguments[selected] = arguments_.at(selected);
    }
  }

  return some_arguments;
}

} // namespace nutsloop::args