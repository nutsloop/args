#include "test_types.h++"
#include "unity.h"

TEST_SOURCE_FILE("src/args/args_stub.c++")
TEST_SOURCE_FILE("src/args/args_gcov_inst.c++")

void setUp(void) {}
void tearDown(void) {}

// ---------------------------------------------------------------------------
// parse_ -- flag parsing
// ---------------------------------------------------------------------------

void test_double_dash_flag_sets_bool_true(void) {
  fake_argv fa{"prog", "--verbose"};
  seq_t seq(fa.argc(), fa.argv());

  TEST_ASSERT_TRUE(seq.has("verbose"));
  TEST_ASSERT_TRUE(std::get<bool>(seq.get_args().at("verbose")));
}

void test_single_dash_flag_sets_bool_true(void) {
  fake_argv fa{"prog", "-x"};
  seq_t seq(fa.argc(), fa.argv());

  TEST_ASSERT_TRUE(seq.has("x"));
  TEST_ASSERT_TRUE(std::get<bool>(seq.get_args().at("x")));
}

void test_multiple_flags_all_stored(void) {
  fake_argv fa{"prog", "--verbose", "--debug", "-q"};
  seq_t seq(fa.argc(), fa.argv());

  TEST_ASSERT_TRUE(seq.has("verbose"));
  TEST_ASSERT_TRUE(seq.has("debug"));
  TEST_ASSERT_TRUE(seq.has("q"));
  TEST_ASSERT_EQUAL_UINT(3, seq.get_args().size());
}

// ---------------------------------------------------------------------------
// parse_ -- key=value string
// ---------------------------------------------------------------------------

void test_key_value_string(void) {
  fake_argv fa{"prog", "--name=hello"};
  seq_t seq(fa.argc(), fa.argv());

  TEST_ASSERT_TRUE(seq.has("name"));
  auto val = std::get<std::string>(seq.get_args().at("name"));
  TEST_ASSERT_EQUAL_STRING("hello", val.c_str());
}

void test_key_value_string_with_path(void) {
  fake_argv fa{"prog", "--config=/etc/app.json"};
  seq_t seq(fa.argc(), fa.argv());

  auto val = std::get<std::string>(seq.get_args().at("config"));
  TEST_ASSERT_EQUAL_STRING("/etc/app.json", val.c_str());
}

void test_key_value_string_with_embedded_equals(void) {
  fake_argv fa{"prog", "--query=key=value"};
  seq_t seq(fa.argc(), fa.argv());

  auto val = std::get<std::string>(seq.get_args().at("query"));
  TEST_ASSERT_EQUAL_STRING("key=value", val.c_str());
}

void test_single_dash_key_value(void) {
  fake_argv fa{"prog", "-n=world"};
  seq_t seq(fa.argc(), fa.argv());

  TEST_ASSERT_TRUE(seq.has("n"));
  auto val = std::get<std::string>(seq.get_args().at("n"));
  TEST_ASSERT_EQUAL_STRING("world", val.c_str());
}

// ---------------------------------------------------------------------------
// parse_ -- key=value numeric (ULL)
// ---------------------------------------------------------------------------

void test_key_value_numeric_small(void) {
  fake_argv fa{"prog", "--count=42"};
  seq_t seq(fa.argc(), fa.argv());

  auto val = std::get<unsigned long long>(seq.get_args().at("count"));
  TEST_ASSERT_EQUAL_UINT64(42, val);
}

void test_key_value_numeric_zero(void) {
  fake_argv fa{"prog", "--retries=0"};
  seq_t seq(fa.argc(), fa.argv());

  auto val = std::get<unsigned long long>(seq.get_args().at("retries"));
  TEST_ASSERT_EQUAL_UINT64(0, val);
}

void test_key_value_numeric_large(void) {
  fake_argv fa{"prog", "--tokens=999999999"};
  seq_t seq(fa.argc(), fa.argv());

  auto val = std::get<unsigned long long>(seq.get_args().at("tokens"));
  TEST_ASSERT_EQUAL_UINT64(999999999ULL, val);
}

// ---------------------------------------------------------------------------
// parse_ -- skip digit check
// ---------------------------------------------------------------------------

void test_skip_digit_check_keeps_numeric_as_string(void) {
  nutsloop::args::skip_digit_check_t skip{
      std::unordered_set<std::string>{"temperature"}};
  fake_argv fa{"prog", "--temperature=7"};
  seq_t seq(fa.argc(), fa.argv(), skip);

  auto val = std::get<std::string>(seq.get_args().at("temperature"));
  TEST_ASSERT_EQUAL_STRING("7", val.c_str());
}

void test_skip_digit_check_does_not_affect_other_keys(void) {
  nutsloop::args::skip_digit_check_t skip{
      std::unordered_set<std::string>{"temperature"}};
  fake_argv fa{"prog", "--temperature=7", "--count=42"};
  seq_t seq(fa.argc(), fa.argv(), skip);

  // temperature kept as string
  TEST_ASSERT_TRUE(std::holds_alternative<std::string>(
      seq.get_args().at("temperature")));
  // count still parsed as ull
  TEST_ASSERT_TRUE(std::holds_alternative<unsigned long long>(
      seq.get_args().at("count")));
}

// ---------------------------------------------------------------------------
// parse_ -- enable/disable switches
// ---------------------------------------------------------------------------

void test_enable_switch_stored_as_true(void) {
  fake_argv fa{"prog", "--enable-cache"};
  seq_t seq(fa.argc(), fa.argv());

  TEST_ASSERT_TRUE(seq.has("enable-cache"));
  TEST_ASSERT_TRUE(std::get<bool>(seq.get_args().at("enable-cache")));
}

void test_disable_switch_stored_as_false(void) {
  fake_argv fa{"prog", "--disable-safety"};
  seq_t seq(fa.argc(), fa.argv());

  TEST_ASSERT_TRUE(seq.has("disable-safety"));
  TEST_ASSERT_FALSE(std::get<bool>(seq.get_args().at("disable-safety")));
}

void test_enable_and_disable_coexist(void) {
  fake_argv fa{"prog", "--enable-cache", "--disable-safety"};
  seq_t seq(fa.argc(), fa.argv());

  TEST_ASSERT_TRUE(std::get<bool>(seq.get_args().at("enable-cache")));
  TEST_ASSERT_FALSE(std::get<bool>(seq.get_args().at("disable-safety")));
}

// ---------------------------------------------------------------------------
// parse_ -- help
// ---------------------------------------------------------------------------

void test_help_bare_flag(void) {
  fake_argv fa{"prog", "--help"};
  seq_t seq(fa.argc(), fa.argv());

  TEST_ASSERT_TRUE(seq.has("help"));
  auto val = std::get<std::string>(seq.get_args().at("help"));
  TEST_ASSERT_EQUAL_STRING("help", val.c_str());
}

void test_help_with_equals_value(void) {
  fake_argv fa{"prog", "--help=model"};
  seq_t seq(fa.argc(), fa.argv());

  auto val = std::get<std::string>(seq.get_args().at("help"));
  TEST_ASSERT_EQUAL_STRING("model", val.c_str());
}

void test_help_short_h_with_value(void) {
  fake_argv fa{"prog", "--h=temperature"};
  seq_t seq(fa.argc(), fa.argv());

  auto val = std::get<std::string>(seq.get_args().at("help"));
  TEST_ASSERT_EQUAL_STRING("temperature", val.c_str());
}

void test_help_question_mark_syntax(void) {
  fake_argv fa{"prog", "--?model"};
  seq_t seq(fa.argc(), fa.argv());

  auto val = std::get<std::string>(seq.get_args().at("help"));
  TEST_ASSERT_EQUAL_STRING("model", val.c_str());
}

void test_help_question_mark_equals(void) {
  fake_argv fa{"prog", "--?=endpoint"};
  seq_t seq(fa.argc(), fa.argv());

  auto val = std::get<std::string>(seq.get_args().at("help"));
  TEST_ASSERT_EQUAL_STRING("endpoint", val.c_str());
}

void test_help_stops_parsing_remaining_args(void) {
  fake_argv fa{"prog", "--help", "--verbose", "--name=test"};
  seq_t seq(fa.argc(), fa.argv());

  TEST_ASSERT_TRUE(seq.has("help"));
  // --verbose and --name should NOT be parsed (help breaks the loop)
  TEST_ASSERT_FALSE(seq.has("verbose"));
  TEST_ASSERT_FALSE(seq.has("name"));
}

// ---------------------------------------------------------------------------
// parse_ -- version
// ---------------------------------------------------------------------------

void test_version_double_dash(void) {
  fake_argv fa{"prog", "--version"};
  seq_t seq(fa.argc(), fa.argv());

  TEST_ASSERT_TRUE(seq.has("version"));
  auto val = std::get<std::string>(seq.get_args().at("version"));
  TEST_ASSERT_EQUAL_STRING("0.0.1", val.c_str());
}

void test_version_short_v(void) {
  fake_argv fa{"prog", "-v"};
  seq_t seq(fa.argc(), fa.argv());

  TEST_ASSERT_TRUE(seq.has("version"));
  auto val = std::get<std::string>(seq.get_args().at("version"));
  TEST_ASSERT_EQUAL_STRING("0.0.1", val.c_str());
}

void test_version_custom_number(void) {
  nutsloop::args::version_opt_t ver{std::array<int, 3>{2, 5, 13}};
  fake_argv fa{"prog", "--version"};
  seq_t seq(fa.argc(), fa.argv(), std::nullopt, ver);

  auto val = std::get<std::string>(seq.get_args().at("version"));
  TEST_ASSERT_EQUAL_STRING("2.5.13", val.c_str());
}

void test_version_stops_parsing(void) {
  fake_argv fa{"prog", "--version", "--verbose"};
  seq_t seq(fa.argc(), fa.argv());

  TEST_ASSERT_TRUE(seq.has("version"));
  TEST_ASSERT_FALSE(seq.has("verbose"));
}

// ---------------------------------------------------------------------------
// parse_ -- command (first non-dash argument)
// ---------------------------------------------------------------------------

void test_command_parsed_from_first_arg(void) {
  fake_argv fa{"prog", "deploy", "--verbose"};
  seq_t seq(fa.argc(), fa.argv());

  TEST_ASSERT_EQUAL_STRING("deploy", seq.get_command().c_str());
  TEST_ASSERT_TRUE(seq.has("verbose"));
}

void test_command_empty_when_first_arg_is_flag(void) {
  fake_argv fa{"prog", "--verbose"};
  seq_t seq(fa.argc(), fa.argv());

  TEST_ASSERT_EQUAL_STRING("", seq.get_command().c_str());
}

void test_command_only_no_flags(void) {
  fake_argv fa{"prog", "status"};
  seq_t seq(fa.argc(), fa.argv());

  TEST_ASSERT_EQUAL_STRING("status", seq.get_command().c_str());
  TEST_ASSERT_EQUAL_UINT(0, seq.get_args().size());
}

// ---------------------------------------------------------------------------
// parse_ -- error cases
// ---------------------------------------------------------------------------

void test_no_arguments_throws(void) {
  fake_argv fa{"prog"};
  bool caught = false;
  try {
    seq_t seq(fa.argc(), fa.argv());
  } catch (const std::invalid_argument &) {
    caught = true;
  }
  TEST_ASSERT_TRUE_MESSAGE(caught, "expected std::invalid_argument for no args");
}

void test_bare_word_after_command_throws(void) {
  fake_argv fa{"prog", "run", "stray"};
  bool caught = false;
  try {
    seq_t seq(fa.argc(), fa.argv());
  } catch (const std::invalid_argument &) {
    caught = true;
  }
  TEST_ASSERT_TRUE_MESSAGE(caught,
      "expected std::invalid_argument for bare word after command");
}

void test_trailing_equals_throws(void) {
  fake_argv fa{"prog", "--name="};
  bool caught = false;
  try {
    seq_t seq(fa.argc(), fa.argv());
  } catch (const std::invalid_argument &) {
    caught = true;
  }
  TEST_ASSERT_TRUE_MESSAGE(caught,
      "expected std::invalid_argument for trailing =");
}

// ---------------------------------------------------------------------------
// process_dashes_ -- single vs double dash detection
// ---------------------------------------------------------------------------

void test_process_dashes_double_dash_flag_strips_two(void) {
  fake_argv fa{"prog", "--verbose"};
  seq_t seq(fa.argc(), fa.argv());

  // double dash: key should be "verbose" (2 chars stripped)
  TEST_ASSERT_TRUE(seq.has("verbose"));
  TEST_ASSERT_FALSE(seq.has("-verbose"));
  TEST_ASSERT_FALSE(seq.has("--verbose"));
}

void test_process_dashes_single_dash_flag_strips_one(void) {
  fake_argv fa{"prog", "-x"};
  seq_t seq(fa.argc(), fa.argv());

  // single dash: key should be "x" (1 char stripped)
  TEST_ASSERT_TRUE(seq.has("x"));
  TEST_ASSERT_FALSE(seq.has("-x"));
}

void test_process_dashes_double_dash_key_value(void) {
  fake_argv fa{"prog", "--port=8080"};
  seq_t seq(fa.argc(), fa.argv());

  // double dash key=value: key is "port"
  TEST_ASSERT_TRUE(seq.has("port"));
  auto val = std::get<unsigned long long>(seq.get_args().at("port"));
  TEST_ASSERT_EQUAL_UINT64(8080, val);
}

void test_process_dashes_single_dash_key_value(void) {
  fake_argv fa{"prog", "-p=8080"};
  seq_t seq(fa.argc(), fa.argv());

  // single dash key=value: key is "p"
  TEST_ASSERT_TRUE(seq.has("p"));
  auto val = std::get<unsigned long long>(seq.get_args().at("p"));
  TEST_ASSERT_EQUAL_UINT64(8080, val);
}

void test_process_dashes_single_dash_multichar_key(void) {
  fake_argv fa{"prog", "-port=9090"};
  seq_t seq(fa.argc(), fa.argv());

  // single dash with multi-char key: key is "port"
  TEST_ASSERT_TRUE(seq.has("port"));
  auto val = std::get<unsigned long long>(seq.get_args().at("port"));
  TEST_ASSERT_EQUAL_UINT64(9090, val);
}

void test_process_dashes_mixed_single_and_double(void) {
  fake_argv fa{"prog", "--verbose", "-q", "--name=test", "-n=short"};
  seq_t seq(fa.argc(), fa.argv());

  // double dash flag
  TEST_ASSERT_TRUE(seq.has("verbose"));
  TEST_ASSERT_TRUE(std::get<bool>(seq.get_args().at("verbose")));

  // single dash flag
  TEST_ASSERT_TRUE(seq.has("q"));
  TEST_ASSERT_TRUE(std::get<bool>(seq.get_args().at("q")));

  // double dash key=value
  auto name = std::get<std::string>(seq.get_args().at("name"));
  TEST_ASSERT_EQUAL_STRING("test", name.c_str());

  // single dash key=value
  auto n = std::get<std::string>(seq.get_args().at("n"));
  TEST_ASSERT_EQUAL_STRING("short", n.c_str());
}

void test_process_dashes_single_dash_enable_switch(void) {
  fake_argv fa{"prog", "-enable-debug"};
  seq_t seq(fa.argc(), fa.argv());

  TEST_ASSERT_TRUE(seq.has("enable-debug"));
  TEST_ASSERT_TRUE(std::get<bool>(seq.get_args().at("enable-debug")));
}

void test_process_dashes_single_dash_disable_switch(void) {
  fake_argv fa{"prog", "-disable-logging"};
  seq_t seq(fa.argc(), fa.argv());

  TEST_ASSERT_TRUE(seq.has("disable-logging"));
  TEST_ASSERT_FALSE(std::get<bool>(seq.get_args().at("disable-logging")));
}

// ---------------------------------------------------------------------------
// parse_ -- mixed real-world scenarios
// ---------------------------------------------------------------------------

void test_mixed_flags_values_switches_command(void) {
  fake_argv fa{"prog", "serve", "--verbose", "--port=8080",
               "--enable-ssl", "--host=localhost", "--disable-logging"};
  seq_t seq(fa.argc(), fa.argv());

  TEST_ASSERT_EQUAL_STRING("serve", seq.get_command().c_str());
  TEST_ASSERT_TRUE(std::get<bool>(seq.get_args().at("verbose")));
  TEST_ASSERT_EQUAL_UINT64(8080, std::get<unsigned long long>(
      seq.get_args().at("port")));
  TEST_ASSERT_TRUE(std::get<bool>(seq.get_args().at("enable-ssl")));
  TEST_ASSERT_EQUAL_STRING("localhost",
      std::get<std::string>(seq.get_args().at("host")).c_str());
  TEST_ASSERT_FALSE(std::get<bool>(seq.get_args().at("disable-logging")));
  TEST_ASSERT_EQUAL_UINT(5, seq.get_args().size());
}
