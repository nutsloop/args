#pragma once

#include <format>
#include <stdexcept>
#include <string>
#include <tuple>

namespace nutsloop::args {

class error final : public std::invalid_argument {

public:
  // Constructor with default message
  error() : std::invalid_argument(DEFAULT_ERROR_MESSAGE) {}
  explicit error(const std::tuple<std::string, std::string> &message) : std::invalid_argument("") {

    std::string disable_flag = std::get<1>(message);
    std::string enable_flag = std::get<0>(message);

    what_message_ = std::format("{} has conflict with {}", disable_flag, enable_flag);
  }

  [[nodiscard]] const char *what() const noexcept override { return what_message_.c_str(); }

  // Constructor with custom error message
  explicit error(const std::string &message) : std::invalid_argument(message) {}

private:
  static constexpr auto DEFAULT_ERROR_MESSAGE = "An argument error has occurred.";
  std::string what_message_;
};

} // namespace nutsloop::args
