#pragma once

namespace nutsloop::args {

template <typename CheckerClass, typename HelperClass>
  requires ArgsChecker<CheckerClass> && (std::same_as<HelperClass, bool> || ArgsHelper<HelperClass>)
void sequencer<CheckerClass, HelperClass>::parse_(const int argc, char *argv[]) {

  // create a vector from argv starting from 1
  std::vector<std::string> vec_args(argv + 1, argv + argc);

  if (vec_args.empty()) {
    throw std::invalid_argument("no arguments provided");
  }

  if (!vec_args[0].starts_with('-')) {
    command_ = vec_args[0];
    vec_args.erase(vec_args.begin());
  }

  if (vec_args.empty()) {
    return;
  }

  // iterate args
  for (const auto &arg : vec_args) {
    arg_ = arg;

    if (!arg_.starts_with("--") && !arg_.starts_with("-")) {
      throw std::invalid_argument(std::format("flags start with `--` or `-`. try --{}", arg_));
    }

    if (arg_.ends_with("=")) {
      throw std::invalid_argument(std::format("{}??? does it require a value? if yes try -> "
                                              "{}something\nif not, omit the `=` -> {}",
                                              arg_, arg_, arg_.substr(0, arg_.size() - 1)));
    }

    process_dashes_();

    equal_sign_pos_ = arg_.find('=');
    key_ = strip_dashes_();

    /// Handles the case where the input key-value pair does not contain an '=' sign,
    /// indicating a special processing mode for standalone keys.
    ///
    /// Behavior:
    /// 1. **Help Processing**:
    ///    - If the key starts with a question mark ('?'), it is treated as a help
    ///    request.
    ///      The portion of the string after '?' is stored in the `arguments_` map under
    ///      the "help" key.
    ///      - Example: "?help" → `arguments_["help"] = "help"`.
    ///      Processing stops for the current iteration (via `break`).
    ///    - If the key equals "help", it is also treated as a help request. The value
    ///    "help"
    ///      itself is stored under the "help" key in the `arguments_` map.
    ///      - Example: "help" → `arguments_["help"] = "help"`.
    ///      Processing again stops for this iteration (via `break`).
    ///
    /// 2. **Toggle / Switch Handling**:
    ///    - The following methods are used to handle switches or feature toggles:
    ///      - `match_enabling_switch_()`: Checks if the key contains "enable". If
    ///      found, the key is
    ///        stored in `arguments_` with a value of `true`, and processing continues.
    ///      - `match_disabling_switch_()`: Checks if the key contains "disable". If
    ///      found, the key
    ///        is stored in `arguments_` with a value of `false`, and processing
    ///        continues.
    ///      - `simple_switch_()`: For all other cases, stores the key in `arguments_`
    ///      with
    ///        a value of `true`. This acts as a generic toggle for standalone keys.
    ///    Each switch-handling method is invoked in order, and iteration proceeds to
    ///    the next key after successful processing (via `continue`).
    ///
    /// 3. **Default Processing**:
    ///    - If none of the specified conditions (help processing or switch-handling)
    ///    are met,
    ///      the loop proceeds to the next key without modification.
    ///
    /// Notes:
    /// - The absence of '=' is indicated by `equal_sign_pos_ == std::string::npos`.
    /// - The processed key-value pairs are stored in the `arguments_` map for further
    /// handling. Checks if the `equal_sign_pos_` indicates the absence of an equal sign
    /// in the input string.
    if (equal_sign_pos_ == std::string::npos) {

      /// If the `key_` starts with a question mark ('?'), it is interpreted as a
      /// request for help. The portion of the string after '?' is stored under the
      /// "help" key in the `arguments_` map.
      if (key_.at(0) == '?') {

        const std::string help_key = key_.substr(1);
        arguments_["help"] = help_key.empty() ? "help" : help_key;
        break;
      }

      /// If the `key_` is exactly "help", a help request is detected and stored in
      /// `arguments_`.
      if (key_ == "help") {
        arguments_["help"] = key_;
        break;
      }

      /// If the `key_` is exactly "version" OR "v", a version request is detected and stored
      /// in `arguments_`. This is a special case that is handled separately from the
      /// help request. The value "version" itself is stored under the "version" key in
      /// the `arguments_` map. This is useful for detecting version requests in the
      /// main program.
      if (key_ == "version" || key_ == "v") {
        std::string version =
            std::accumulate(version_.begin(), version_.end(), std::string(),
                            [](const std::string &acc, const int value) {
                              return acc + (acc.empty() ? "" : ".") + std::to_string(value);
                            });
        arguments_["version"] = version;
        break;
      }

      /// Attempts to enable a specific feature or mode using the
      /// `match_enabling_switch_` method. If successful, moves to the next iteration of
      /// the loop.
      if (this->match_enabling_switch_()) continue;

      /// Attempts to disable a specific feature or mode using the
      /// `match_disabling_switch_` method. If successful, moves to the next iteration
      /// of the loop.
      if (this->match_disabling_switch_()) continue;

      /// Handles cases for simple toggles using the `match_truthy_switch_` method.
      this->match_truthy_switch_();

      /// Proceeds to the next iteration of the loop when no specific condition is met.
      continue;
    }

    /// @brief Extracts the substring from `arg_` starting right after the position of
    /// `equal_sign_pos_` and assigns it to `value_`.
    ///
    /// This operation is often used for parsing strings where key-value pairs are
    /// separated by an equals sign ('='). For example, if `arg_` contains "key=value",
    /// and `equal_sign_pos_` points to the position of '=', then `value_` will be
    /// assigned "value".
    ///
    /// @note Assumes that `equal_sign_pos_ + 1` is a valid index in `arg_`.
    value_ = arg_.substr(equal_sign_pos_ + 1);

    // help key
    if (key_ == "help" || key_ == "h" || key_ == "?") {
      arguments_["help"] = value_;
      break;
    }

    // In your parsing method where key_ and value_ are set
    if (should_interpret_as_ull_()) {
      arguments_[key_] = std::stoull(value_);
    } else {
      arguments_[key_] = value_;
    }
  }
}

} // namespace nutsloop::args
