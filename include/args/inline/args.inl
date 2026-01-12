#pragma once

#include "thread"

#include <exception>

namespace nutsloop::args {

template <typename CheckerClass, typename HelperClass>
  requires ArgsChecker<CheckerClass> && (std::same_as<HelperClass, bool> || ArgsHelper<HelperClass>)
sequencer<CheckerClass, HelperClass>::sequencer(int argc, char *argv[],
                                      const skip_digit_check_t &skip_digit_check,
                                      const version_opt_t &version) {

  version_ = version.value_or(version_t_{0, 0, 1});
  skip_digit_check_ = skip_digit_check.value_or(skip_digit_check_list_t_{});
  std::exception_ptr thread_exception = nullptr;

  std::jthread parse([argv, this, argc, &thread_exception] {
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
