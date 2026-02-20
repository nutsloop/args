#include "test_types.h++"
#include "unity.h"

TEST_SOURCE_FILE("src/args/args_stub.c++")
TEST_SOURCE_FILE("src/args/args_gcov_inst.c++")

void setUp(void) {}
void tearDown(void) {}

// ---------------------------------------------------------------------------
// argv_to_string_ranges_ -- static method
// ---------------------------------------------------------------------------

void test_argv_to_string_ranges_multiple_args(void) {
  fake_argv fa{"prog", "--verbose", "--name=test"};
  auto result = seq_t::argv_to_string_ranges_(fa.argc(), fa.argv());
  TEST_ASSERT_EQUAL_STRING("--verbose|--name=test", result.c_str());
}

void test_argv_to_string_ranges_single_arg(void) {
  fake_argv fa{"prog", "--help"};
  auto result = seq_t::argv_to_string_ranges_(fa.argc(), fa.argv());
  TEST_ASSERT_EQUAL_STRING("--help", result.c_str());
}

void test_argv_to_string_ranges_no_args_returns_empty(void) {
  fake_argv fa{"prog"};
  auto result = seq_t::argv_to_string_ranges_(fa.argc(), fa.argv());
  TEST_ASSERT_EQUAL_STRING("", result.c_str());
}

void test_argv_to_string_ranges_custom_separator(void) {
  fake_argv fa{"prog", "a", "b", "c"};
  auto result = seq_t::argv_to_string_ranges_(fa.argc(), fa.argv(), ',');
  TEST_ASSERT_EQUAL_STRING("a,b,c", result.c_str());
}

void test_argv_to_string_ranges_many_args(void) {
  fake_argv fa{"prog", "--a", "--b", "--c", "--d"};
  auto result = seq_t::argv_to_string_ranges_(fa.argc(), fa.argv());
  TEST_ASSERT_EQUAL_STRING("--a|--b|--c|--d", result.c_str());
}

// ---------------------------------------------------------------------------
// join() free function
// ---------------------------------------------------------------------------

void test_join_multiple_strings(void) {
  char *buf[] = {
      const_cast<char *>("hello"),
      const_cast<char *>("world")};
  std::string dest;
  nutsloop::args::join(buf, 2, dest);
  TEST_ASSERT_EQUAL_STRING("hello\nworld", dest.c_str());
}

void test_join_custom_separator(void) {
  char *buf[] = {
      const_cast<char *>("a"),
      const_cast<char *>("b"),
      const_cast<char *>("c")};
  std::string dest;
  nutsloop::args::join(buf, 3, dest, ',');
  TEST_ASSERT_EQUAL_STRING("a,b,c", dest.c_str());
}

void test_join_single_element(void) {
  char *buf[] = {const_cast<char *>("only")};
  std::string dest;
  nutsloop::args::join(buf, 1, dest);
  TEST_ASSERT_EQUAL_STRING("only", dest.c_str());
}

void test_join_empty_clears_dest(void) {
  std::string dest = "leftover";
  nutsloop::args::join(nullptr, 0, dest);
  TEST_ASSERT_EQUAL_STRING("", dest.c_str());
}

void test_join_skips_nullptr_entries(void) {
  char *buf[] = {
      const_cast<char *>("a"),
      nullptr,
      const_cast<char *>("c")};
  std::string dest;
  nutsloop::args::join(buf, 3, dest);
  TEST_ASSERT_EQUAL_STRING("a\nc", dest.c_str());
}

// ---------------------------------------------------------------------------
// option_type_name_t -- compile-time type name resolution
// ---------------------------------------------------------------------------

void test_option_type_name_string(void) {
  auto name = nutsloop::option_type_name_t<std::string>::get();
  TEST_ASSERT_EQUAL_STRING("string", std::string(name).c_str());
}

void test_option_type_name_ull(void) {
  auto name = nutsloop::option_type_name_t<unsigned long long>::get();
  TEST_ASSERT_EQUAL_STRING("unsigned long long", std::string(name).c_str());
}

void test_option_type_name_bool(void) {
  auto name = nutsloop::option_type_name_t<bool>::get();
  TEST_ASSERT_EQUAL_STRING("bool", std::string(name).c_str());
}

void test_option_type_name_unknown(void) {
  auto name = nutsloop::option_type_name_t<int>::get();
  TEST_ASSERT_EQUAL_STRING("unknown", std::string(name).c_str());
}
