#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <variant>

namespace nutsloop::args {

using args_t =
    std::unordered_map<std::string,
                       std::variant<std::string, unsigned long long, bool, std::nullptr_t>>;

using args_list_t = std::unordered_set<std::string>;

using args_command_t = std::string;
using args_list_command_t = std::unordered_set<std::string>;

} // namespace nutsloop::args