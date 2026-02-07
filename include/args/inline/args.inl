#pragma once

#include <thread>

#include <exception>

namespace nutsloop::args {

namespace detail {
#if defined(__cpp_lib_jthread) && __cpp_lib_jthread >= 201911L
using thread_t = std::jthread;
#else
using thread_t = std::thread;
#endif
} // namespace detail

template <typename CheckerClass, typename HelperClass>
  requires ArgsChecker<CheckerClass> && (std::same_as<HelperClass, bool> || ArgsHelper<HelperClass>)
sequencer<CheckerClass, HelperClass>::sequencer(int argc, char *argv[],
                                      const skip_digit_check_t &skip_digit_check,
                                      const version_opt_t &version) {

  version_ = version.value_or(version_t_{0, 0, 1, 0});
  skip_digit_check_ = skip_digit_check.value_or(skip_digit_check_list_t_{});
  std::exception_ptr thread_exception = nullptr;

  detail::thread_t parse([argv, this, argc, &thread_exception] {
    try {
      this->parse_(argc, argv);
    } catch (...) {
      thread_exception = std::current_exception();
    }
  });

  parse.join();

  if (thread_exception) {
    std::rethrow_exception(thread_exception);
  }
}

} // namespace nutsloop::args
