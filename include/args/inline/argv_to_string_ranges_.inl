#pragma once
#include <ranges>

namespace nutsloop::args {

template <typename CheckerClass, typename HelperClass>
  requires ArgsChecker<CheckerClass> && (std::same_as<HelperClass, bool> || ArgsHelper<HelperClass>)
std::string sequencer<CheckerClass, HelperClass>::argv_to_string_ranges_(int argc, char *argv[],
                                                                    char separator /*='|'*/) {

  if (argc <= 1) {
    return "";
  }

#if defined(__cpp_lib_ranges_join_with)
  // Create a span of the arguments, excluding the program name
  auto relevant_args_span = std::span(argv + 1, argc - 1);

  // Filter out nullptrs and transform char* to string_view (or string)
  // then join with '|'
  auto joined_view = relevant_args_span |
                     std::views::filter([](const char *s) { return s != nullptr; }) |
                     std::views::transform([](const char *s) { return std::string_view(s); }) |
                     std::views::join_with(separator); // The default delimiter is '|'

  // Convert the resulting view to a std::string
#if __cplusplus >= 202302L // C++23 check
  return std::ranges::to<std::string>(joined_view);
#else // C++20
  std::string result_str;
  for (char c : joined_view) {
    result_str += c;
  }
  return result_str;
  // Or for C++20, a common pattern is:
  // return std::string(joined_view.begin(), joined_view.end());
  // However, join_with produces an input_range, so the above might not be the most efficient direct
  // construction. Iterating and appending or using a stringstream for construction from a C++20
  // join_with view is common.
#endif
#else
  std::string result;
  for (int i = 1; i < argc; ++i) {
    if (argv[i] == nullptr) {
      continue;
    }
    if (!result.empty()) {
      result += separator;
    }
    result += argv[i];
  }
  return result;
#endif
}

inline void join(char *buf[], size_t buf_size, std::string &dest, char sep = '\n') {
  if (buf_size == 0) {
    dest.clear();
    return;
  }

#if defined(__cpp_lib_ranges_join_with)
  auto relevant_args_span = std::span(buf, buf_size);

  auto joined_view = relevant_args_span |
                     std::views::filter([](const char *s) { return s != nullptr; }) |
                     std::views::transform([](const char *s) { return std::string_view(s); }) |
                     std::views::join_with(sep);

#if __cplusplus >= 202302L // C++23
  dest = std::ranges::to<std::string>(joined_view);
#else // C++20
  dest.clear();
  for (char c : joined_view) {
    dest += c;
  }
#endif
#else
  dest.clear();
  for (size_t i = 0; i < buf_size; ++i) {
    if (buf[i] == nullptr) {
      continue;
    }
    if (!dest.empty()) {
      dest += sep;
    }
    dest += buf[i];
  }
#endif
}

} // namespace nutsloop::args


// example of using join. should not be here.
/*std::string buf_recv{};
char *buf[] = {
  const_cast<char *>("I"),    const_cast<char *>("love"), const_cast<char *>("you"),
  const_cast<char *>("more"), const_cast<char *>("than"), const_cast<char *>("words"),
  const_cast<char *>("can"),  const_cast<char *>("say"),  nullptr};

join(buf, sizeof(buf[0]), buf_recv);

std::cout << buf_recv << std::endl;

std::cout << sequencer<check, help>::argv_to_string_ranges_(argc, argv);*/
