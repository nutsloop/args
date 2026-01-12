#pragma once
#include <optional>
#include <string>
#include <unordered_set>

namespace nutsloop::args {

using skip_digit_check_t = std::optional<std::unordered_set<std::string>>;

}
