#include "args/error.h++"
#include "unity.h"

#include <string>
#include <tuple>

TEST_SOURCE_FILE("src/args/args_stub.c++")
TEST_SOURCE_FILE("src/args/args_gcov_inst.c++")

void setUp(void) {}
void tearDown(void) {}

// ---------------------------------------------------------------------------
// error -- tuple constructor (the primary constructor used in practice)
// ---------------------------------------------------------------------------

void test_error_tuple_conflict_message(void) {
  auto pair = std::make_tuple(std::string("enable-cache"),
                              std::string("disable-cache"));
  nutsloop::args::error err(pair);
  TEST_ASSERT_EQUAL_STRING(
      "disable-cache has conflict with enable-cache", err.what());
}

void test_error_tuple_reversed_order(void) {
  auto pair = std::make_tuple(std::string("disable-logging"),
                              std::string("enable-logging"));
  nutsloop::args::error err(pair);
  TEST_ASSERT_EQUAL_STRING(
      "enable-logging has conflict with disable-logging", err.what());
}

// ---------------------------------------------------------------------------
// error -- inheritance
// ---------------------------------------------------------------------------

void test_error_is_invalid_argument(void) {
  bool caught_as_invalid_argument = false;
  try {
    throw nutsloop::args::error("test");
  } catch (const std::invalid_argument &) {
    caught_as_invalid_argument = true;
  }
  TEST_ASSERT_TRUE(caught_as_invalid_argument);
}

void test_error_is_logic_error(void) {
  bool caught_as_logic = false;
  try {
    throw nutsloop::args::error("test");
  } catch (const std::logic_error &) {
    caught_as_logic = true;
  }
  TEST_ASSERT_TRUE(caught_as_logic);
}

void test_error_is_exception(void) {
  bool caught_as_exception = false;
  try {
    throw nutsloop::args::error("test");
  } catch (const std::exception &) {
    caught_as_exception = true;
  }
  TEST_ASSERT_TRUE(caught_as_exception);
}

// ---------------------------------------------------------------------------
// error -- default and string constructors
// NOTE: what() override returns what_message_ which is only populated
//       by the tuple constructor. The default/string constructors pass
//       their message to std::invalid_argument base but the override
//       shadows it. This documents that behavior.
// ---------------------------------------------------------------------------

void test_error_default_constructor_what_returns_empty(void) {
  nutsloop::args::error err;
  // what_message_ is empty; the base class message is shadowed
  TEST_ASSERT_EQUAL_STRING("", err.what());
}

void test_error_string_constructor_what_returns_empty(void) {
  nutsloop::args::error err("this message is lost");
  // what_message_ is empty; the base class message is shadowed
  TEST_ASSERT_EQUAL_STRING("", err.what());
}
