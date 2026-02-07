#pragma once
#include <array>
#include <optional>

namespace nutsloop::args {

// Version format: {major, minor, patch, suffix} for "X.Y.Z-NNN"
using version_t = std::array<int, 4>;
using version_opt_t = std::optional<std::array<int, 4>>;

} // namespace nutsloop::args
