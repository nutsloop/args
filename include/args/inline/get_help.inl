#pragma once

namespace nutsloop::args {

template <typename CheckerClass, typename HelperClass>
  requires ArgsChecker<CheckerClass> &&
           (std::same_as<HelperClass, bool> || ArgsHelper<HelperClass>)
           HelperClass sequencer<CheckerClass, HelperClass>::get_help(std::string argument)
             requires ArgsHelper<HelperClass>
{
  return HelperClass(argument, version_);
}

} // namespace nutsloop::args