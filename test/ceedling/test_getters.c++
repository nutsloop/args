#include "test_types.h++"
#include "unity.h"

TEST_SOURCE_FILE("src/args/args_stub.c++")
TEST_SOURCE_FILE("src/args/args_gcov_inst.c++")

void setUp(void) {}
void tearDown(void) {}

// ---------------------------------------------------------------------------
// has()
// ---------------------------------------------------------------------------

void test_has_returns_true_for_present_key(void) {
  fake_argv fa{"prog", "--verbose"};
  seq_t seq(fa.argc(), fa.argv());

  TEST_ASSERT_TRUE(seq.has("verbose"));
}

void test_has_returns_false_for_missing_key(void) {
  fake_argv fa{"prog", "--verbose"};
  seq_t seq(fa.argc(), fa.argv());

  TEST_ASSERT_FALSE(seq.has("nonexistent"));
}

// ---------------------------------------------------------------------------
// get_option_string()
// ---------------------------------------------------------------------------

void test_get_option_string_returns_string(void) {
  fake_argv fa{"prog", "--name=hello"};
  seq_t seq(fa.argc(), fa.argv());

  auto result = seq.get_option_string("name");
  TEST_ASSERT_EQUAL_STRING("hello",
      std::get<std::string>(result.value).c_str());
}

void test_get_option_string_missing_key_returns_nullptr(void) {
  fake_argv fa{"prog", "--verbose"};
  seq_t seq(fa.argc(), fa.argv());

  auto result = seq.get_option_string("name");
  TEST_ASSERT_TRUE(std::holds_alternative<std::nullptr_t>(result.value));
}

void test_get_option_string_wrong_type_throws(void) {
  fake_argv fa{"prog", "--verbose"};
  seq_t seq(fa.argc(), fa.argv());

  bool caught = false;
  try {
    seq.get_option_string("verbose"); // verbose is bool, not string
  } catch (const std::invalid_argument &) {
    caught = true;
  }
  TEST_ASSERT_TRUE_MESSAGE(caught,
      "expected throw for string getter on bool value");
}

// ---------------------------------------------------------------------------
// get_option_bool()
// ---------------------------------------------------------------------------

void test_get_option_bool_returns_true(void) {
  fake_argv fa{"prog", "--verbose"};
  seq_t seq(fa.argc(), fa.argv());

  auto result = seq.get_option_bool("verbose");
  TEST_ASSERT_TRUE(std::get<bool>(result.value));
}

void test_get_option_bool_returns_false_for_disable(void) {
  fake_argv fa{"prog", "--disable-cache"};
  seq_t seq(fa.argc(), fa.argv());

  auto result = seq.get_option_bool("disable-cache");
  TEST_ASSERT_FALSE(std::get<bool>(result.value));
}

void test_get_option_bool_missing_key_returns_nullptr(void) {
  fake_argv fa{"prog", "--verbose"};
  seq_t seq(fa.argc(), fa.argv());

  auto result = seq.get_option_bool("missing");
  TEST_ASSERT_TRUE(std::holds_alternative<std::nullptr_t>(result.value));
}

void test_get_option_bool_wrong_type_throws(void) {
  fake_argv fa{"prog", "--name=hello"};
  seq_t seq(fa.argc(), fa.argv());

  bool caught = false;
  try {
    seq.get_option_bool("name"); // name is string, not bool
  } catch (const std::invalid_argument &) {
    caught = true;
  }
  TEST_ASSERT_TRUE_MESSAGE(caught,
      "expected throw for bool getter on string value");
}

// ---------------------------------------------------------------------------
// get_option_uint()
// ---------------------------------------------------------------------------

void test_get_option_uint_returns_value(void) {
  fake_argv fa{"prog", "--count=100"};
  seq_t seq(fa.argc(), fa.argv());

  auto result = seq.get_option_uint("count");
  TEST_ASSERT_EQUAL_UINT64(100,
      std::get<unsigned long long>(result.value));
}

void test_get_option_uint_missing_key_returns_nullptr(void) {
  fake_argv fa{"prog", "--verbose"};
  seq_t seq(fa.argc(), fa.argv());

  auto result = seq.get_option_uint("count");
  TEST_ASSERT_TRUE(std::holds_alternative<std::nullptr_t>(result.value));
}

void test_get_option_uint_wrong_type_throws(void) {
  fake_argv fa{"prog", "--name=hello"};
  seq_t seq(fa.argc(), fa.argv());

  bool caught = false;
  try {
    seq.get_option_uint("name"); // name is string, not ull
  } catch (const std::invalid_argument &) {
    caught = true;
  }
  TEST_ASSERT_TRUE_MESSAGE(caught,
      "expected throw for uint getter on string value");
}

// ---------------------------------------------------------------------------
// get_option_addr()
// ---------------------------------------------------------------------------

void test_get_option_addr_returns_string(void) {
  fake_argv fa{"prog", "--endpoint=https://api.example.com"};
  seq_t seq(fa.argc(), fa.argv());

  auto result = seq.get_option_addr("endpoint");
  TEST_ASSERT_EQUAL_STRING("https://api.example.com",
      std::get<std::string>(result.value).c_str());
}

void test_get_option_addr_missing_key_returns_nullptr(void) {
  fake_argv fa{"prog", "--verbose"};
  seq_t seq(fa.argc(), fa.argv());

  auto result = seq.get_option_addr("endpoint");
  TEST_ASSERT_TRUE(std::holds_alternative<std::nullptr_t>(result.value));
}

void test_get_option_addr_wrong_type_throws(void) {
  fake_argv fa{"prog", "--verbose"};
  seq_t seq(fa.argc(), fa.argv());

  bool caught = false;
  try {
    seq.get_option_addr("verbose"); // verbose is bool
  } catch (const std::invalid_argument &) {
    caught = true;
  }
  TEST_ASSERT_TRUE_MESSAGE(caught,
      "expected throw for addr getter on bool value");
}

// ---------------------------------------------------------------------------
// get_arg<T>()
// ---------------------------------------------------------------------------

void test_get_arg_string_returns_value(void) {
  fake_argv fa{"prog", "--name=test"};
  seq_t seq(fa.argc(), fa.argv());

  auto result = seq.template get_arg<std::string>("name");
  TEST_ASSERT_TRUE(result.has_value());
  TEST_ASSERT_EQUAL_STRING("test", result.value().c_str());
}

void test_get_arg_bool_returns_value(void) {
  fake_argv fa{"prog", "--verbose"};
  seq_t seq(fa.argc(), fa.argv());

  auto result = seq.template get_arg<bool>("verbose");
  TEST_ASSERT_TRUE(result.has_value());
  TEST_ASSERT_TRUE(result.value());
}

void test_get_arg_ull_returns_value(void) {
  fake_argv fa{"prog", "--count=55"};
  seq_t seq(fa.argc(), fa.argv());

  auto result = seq.template get_arg<unsigned long long>("count");
  TEST_ASSERT_TRUE(result.has_value());
  TEST_ASSERT_EQUAL_UINT64(55, result.value());
}

void test_get_arg_missing_key_returns_nullopt(void) {
  fake_argv fa{"prog", "--verbose"};
  seq_t seq(fa.argc(), fa.argv());

  auto result = seq.template get_arg<std::string>("missing");
  TEST_ASSERT_FALSE(result.has_value());
}

void test_get_arg_type_mismatch_throws(void) {
  fake_argv fa{"prog", "--verbose"};
  seq_t seq(fa.argc(), fa.argv());

  bool caught = false;
  try {
    seq.template get_arg<std::string>("verbose"); // verbose is bool
  } catch (const std::invalid_argument &) {
    caught = true;
  }
  TEST_ASSERT_TRUE_MESSAGE(caught,
      "expected throw for get_arg type mismatch");
}

// ---------------------------------------------------------------------------
// get_some_args()
// ---------------------------------------------------------------------------

void test_get_some_args_returns_matching_subset(void) {
  fake_argv fa{"prog", "--verbose", "--name=test", "--count=10"};
  seq_t seq(fa.argc(), fa.argv());

  auto subset = seq.get_some_args({"verbose", "name"});
  TEST_ASSERT_EQUAL_UINT(2, subset.size());
  TEST_ASSERT_TRUE(subset.contains("verbose"));
  TEST_ASSERT_TRUE(subset.contains("name"));
  TEST_ASSERT_FALSE(subset.contains("count"));
}

void test_get_some_args_skips_missing_keys(void) {
  fake_argv fa{"prog", "--verbose"};
  seq_t seq(fa.argc(), fa.argv());

  auto subset = seq.get_some_args({"verbose", "nonexistent"});
  TEST_ASSERT_EQUAL_UINT(1, subset.size());
  TEST_ASSERT_TRUE(subset.contains("verbose"));
}

void test_get_some_args_empty_selection_returns_empty(void) {
  fake_argv fa{"prog", "--verbose"};
  seq_t seq(fa.argc(), fa.argv());

  auto subset = seq.get_some_args({});
  TEST_ASSERT_EQUAL_UINT(0, subset.size());
}

void test_get_some_args_all_missing_returns_empty(void) {
  fake_argv fa{"prog", "--verbose"};
  seq_t seq(fa.argc(), fa.argv());

  auto subset = seq.get_some_args({"a", "b", "c"});
  TEST_ASSERT_EQUAL_UINT(0, subset.size());
}

// ---------------------------------------------------------------------------
// get_args() -- full map access
// ---------------------------------------------------------------------------

void test_get_args_returns_correct_count(void) {
  fake_argv fa{"prog", "--a", "--b=hello", "--c=99"};
  seq_t seq(fa.argc(), fa.argv());

  TEST_ASSERT_EQUAL_UINT(3, seq.get_args().size());
}

// ---------------------------------------------------------------------------
// get_help() -- with HelperClass
// ---------------------------------------------------------------------------

void test_get_help_constructs_helper(void) {
  fake_argv fa{"prog", "--help"};
  seq_help_t seq(fa.argc(), fa.argv());

  auto helper = seq.get_help("model");
  TEST_ASSERT_EQUAL_STRING("model", helper.look_up.c_str());
}

void test_get_help_passes_version(void) {
  nutsloop::args::version_opt_t ver{std::array<int, 3>{3, 2, 1}};
  fake_argv fa{"prog", "--help"};
  seq_help_t seq(fa.argc(), fa.argv(), std::nullopt, ver);

  auto helper = seq.get_help("topic");
  TEST_ASSERT_EQUAL_INT(3, helper.ver[0]);
  TEST_ASSERT_EQUAL_INT(2, helper.ver[1]);
  TEST_ASSERT_EQUAL_INT(1, helper.ver[2]);
}
