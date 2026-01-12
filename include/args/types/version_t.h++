#pragma once
#include <array>
#include <optional>

namespace nutsloop::args {

using version_t = std::array<int, 3>;
using version_opt_t = std::optional<std::array<int, 3>>;

} // namespace nutsloop::args
