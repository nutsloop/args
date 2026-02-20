#pragma once

namespace nutsloop::args {

template <typename CheckerClass, typename HelperClass>
  requires ArgsChecker<CheckerClass> && (std::same_as<HelperClass, bool> || ArgsHelper<HelperClass>)
std::string sequencer<CheckerClass, HelperClass>::argv_to_string_(const int argc, char *argv[]) {

  std::string result;

  for (int i = 1; i < argc; ++i) {
    result += argv[i];
    if (i + 1 < argc) {
      result += '|';
    }
  }

  return result;
}

} // namespace nutsloop::args