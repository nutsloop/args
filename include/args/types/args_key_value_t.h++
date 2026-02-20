#pragma once

#include <cstddef>
#include <string>
#include <variant>

namespace nutsloop::args {

using args_key_value_t_ = std::variant<std::string, unsigned long long, bool, std::nullptr_t>;

} // namespace nutsloop::args
