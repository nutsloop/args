#pragma once

namespace nutsloop::args {

template <typename CheckerClass, typename HelperClass>
  requires ArgsChecker<CheckerClass> && (std::same_as<HelperClass, bool> || ArgsHelper<HelperClass>)
template <OptionTypes T>
[[nodiscard]] std::optional<T>
sequencer<CheckerClass, HelperClass>::get_arg(const std::string &key) const {
  const auto it = arguments_.find(key);
  if (it == arguments_.end()) {
    return std::nullopt;
  }

  if (auto value = std::get_if<T>(&it->second)) {
    return *value;
  }

  throw std::invalid_argument(
      std::format("--{} accept only {}", option_type_name_t<T>::get(), key));
}

} // namespace nutsloop::args
