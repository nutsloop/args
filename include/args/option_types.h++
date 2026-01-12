#pragma once

#include <string>      // For std::string
#include <string_view> // For std::string_view
#include <type_traits> // For std::is_same, std::disjunction_v, std::is_same_v

namespace nutsloop {

// Concept defining the allowed option types using std::disjunction_v
template <typename T>
concept OptionTypes =
    std::disjunction_v<std::is_same<T, std::string>, // Note: std::is_same, not std::is_same_v here
                       std::is_same<T, unsigned long long>, std::is_same<T, bool>>;

// Struct to get the type name string
template <typename T>

struct option_type_name_t {
  // static constexpr method returning std::string_view
  static constexpr std::string_view get() {
    // First, check if T conforms to the OptionTypes concept
    if constexpr (OptionTypes<T>) {
      // If T is an OptionType, determine which one it is
      if constexpr (std::is_same_v<T, std::string>) {
        return "string";
      } else if constexpr (std::is_same_v<T, unsigned long long>) {
        return "unsigned long long";
      } else if constexpr (std::is_same_v<T, bool>) {
        return "bool";
      } else {
        // This 'else' branch should ideally not be reached if OptionTypes<T> is true
        // and all types covered by the OptionTypes concept are handled above.
        // A static_assert here helps catch inconsistencies during compilation.
        // The '!std::is_same_v<T,T>' makes the condition dependent on T,
        // ensuring it's only evaluated if this branch is instantiated.
        static_assert(
            !std::is_same_v<T, T>,
            "Internal Error: Type satisfies OptionTypes but is not handled in "
            "OptionTypeName::get(). "
            "Please update OptionTypeName to cover all types in the OptionTypes concept.");
        return "error_unhandled_option_type"; // Fallback for safety, but should be unreachable
      }
    } else {
      // If T does not satisfy OptionTypes, return "unknown"
      return "unknown";
    }
  }
};

} // namespace nutsloop