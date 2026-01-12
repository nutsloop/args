#pragma once

#include "args/option_types.h++"
#include "args/types/args_key_value_t.h++"
#include "args/types/args_t.h++"
#include "args/types/skip_digit_check_t.h++"
#include "args/types/version_t.h++"

#include <algorithm>
#include <array>
#include <cctype>
#include <concepts>
#include <format>
#include <map>
#include <numeric>
#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <unordered_set>
#include <variant>
#include <vector>

namespace nutsloop::args {

template <typename CheckerClass>
concept ArgsChecker = std::constructible_from<CheckerClass, args_key_value_t_>;

template <typename HelperClass>
concept ArgsHelper =
    std::constructible_from<HelperClass, std::string, std::array<int, 3>>;

template <typename CheckerClass, typename HelperClass = bool>
  requires ArgsChecker<CheckerClass> &&
           (std::same_as<HelperClass, bool> || ArgsHelper<HelperClass>)

class sequencer {

  // MARK (sequencer) private types declaration.
  using skip_digit_check_list_t_ = std::unordered_set<std::string>;
  using version_t_ = std::array<int, 3>;
  using args_key_value_t_ =
      std::variant<std::string, unsigned long long, bool, std::nullptr_t>;

public:
  sequencer(int argc, char *argv[],
            const skip_digit_check_t &skip_digit_check = std::nullopt,
            const version_opt_t &version = std::nullopt);

  ~sequencer() = default;

  HelperClass get_help(std::string argument)
    requires ArgsHelper<HelperClass>;

  CheckerClass get_option_string(const std::string &key) const;

  CheckerClass get_option_addr(const std::string &key) const;

  CheckerClass get_option_uint(const std::string &key) const;

  CheckerClass get_option_bool(const std::string &key) const;

  [[nodiscard]] bool has(const std::string &key) const;

  [[nodiscard]] const args_t &get_args() const { return arguments_; }

  [[nodiscard]] const args_command_t &get_command() const { return command_; }

  template <OptionTypes T>
  [[nodiscard]] std::optional<T> get_arg(const std::string &key) const;

  /**
   * Retrieves a selection of argument key-value pairs from the parsed
   * arguments.
   *
   * This method filters the parsed arguments based on the provided selection
   * and returns a map containing the arguments that match the keys in the
   * selection.
   *
   * The arguments are retrieved only if they exist in the internal arguments
   * map.
   *
   * @param selection A vector of strings representing the keys to filter and
   * retrieve.
   * @return A map where the key is a string corresponding to the selected
   * argument, and the value is an args_key_value_t variant representing its
   * value. The returned map contains only the arguments that were found in the
   * internal state corresponding to the provided selection.
   */
  [[nodiscard]] args_t
  get_some_args(const std::vector<std::string> &selection) const;
  static std::string argv_to_string_ranges_(int argc, char *argv[],
                                            char separator = '|');

private:
  args_t arguments_;
  args_command_t command_;
  skip_digit_check_list_t_ skip_digit_check_;
  bool is_single_dash_{false};
  size_t equal_sign_pos_{0};
  std::string value_;
  std::string key_;
  std::string arg_;
  std::array<int, 3> version_{};

  void parse_(int argc, char *argv[]);

  void match_truthy_switch_();

  void process_dashes_();

  [[nodiscard]] bool match_enabling_switch_();

  [[nodiscard]] bool match_disabling_switch_();

  [[nodiscard]] bool is_digit_() const;

  [[nodiscard]] bool does_skip_digit_check_() const;

  [[nodiscard]] bool is_in_ull_range_() const;

  [[nodiscard]] bool should_interpret_as_ull_() const;

  [[nodiscard]] std::string strip_dashes_() const;

  [[maybe_unused]] static std::string argv_to_string_(int argc, char *argv[]);
};
} // namespace nutsloop::args

#include "args/inline/args.inl"
#include "args/inline/argv_to_string_.inl"
#include "args/inline/argv_to_string_ranges_.inl"
#include "args/inline/does_skip_digit_check_.inl"
#include "args/inline/get_arg.inl"
#include "args/inline/get_help.inl"
#include "args/inline/get_option_addr.inl"
#include "args/inline/get_option_bool.inl"
#include "args/inline/get_option_string.inl"
#include "args/inline/get_option_uint.inl"
#include "args/inline/get_some_args.inl"
#include "args/inline/has.inl"
#include "args/inline/is_digit_.inl"
#include "args/inline/is_in_ull_range_.inl"
#include "args/inline/match_disabling_switch_.inl"
#include "args/inline/match_enabling_switch_.inl"
#include "args/inline/match_truthy_switch_.inl"
#include "args/inline/parse_.inl"
#include "args/inline/process_dashes_.inl"
#include "args/inline/should_interpret_as_ull_.inl"
#include "args/inline/strip_dashes_.inl"
