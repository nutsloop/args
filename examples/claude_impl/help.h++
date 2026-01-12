#pragma once
#include "args/types/version_t.h++"
#include "help/text/help.h++"

#include <array>
#include <string>
#include <tuple>
#include <unordered_map>

/**
 * Claude Implementation Help System
 *
 * This class provides comprehensive help documentation for all CLI options
 * in the claude_impl example. It demonstrates:
 * - Enum-based topic routing
 * - Dynamic help text generation
 * - Version information display
 * - Unknown topic handling
 *
 * To add a new help topic:
 * 1. Add Topic_ enum entry
 * 2. Add text constants in help/text/<topic>.h++
 * 3. Add private method <topic>_() in this class
 * 4. Add mapping in set_option_list_()
 * 5. Add case in get_help_topic_()
 * 6. Add implementation file help/<topic>_.c++
 */

namespace nutsloop::claude_impl {
using namespace chelp;

class help {

  enum class Topic_ {
    // Model configuration
    model,
    temperature,
    max_tokens,
    top_p,
    top_k,
    context_window,

    // Streaming and output
    stream,
    output_format,
    output_dir,

    // API configuration
    api_key,
    endpoint,
    timeout,
    retry_count,

    // Behavior flags
    disable_safety,
    verbose,
    dry_run,
    enable_cache,
    disable_cache,

    // File options
    config_file,
    input_file,
    log_file,
    log_level,

    // System
    system_prompt,
    help,
    version,
    unknown
  };

public:
  explicit help(std::string look_up_option, args::version_t version);
  [[nodiscard]] int print();
  [[nodiscard]] std::string to_string();

private:
  std::string look_up_option_;
  args::version_t version_info_{};

  using topic_enum_t_ = std::unordered_map<std::string, Topic_>;
  using help_ret_topic_status_ = std::tuple<std::string, int>;
  topic_enum_t_ option_list_;

  void set_option_list_();
  [[nodiscard]] std::string get_noun_name_() const;
  [[nodiscard]] std::string get_version_() const;

  // Help topic methods - each returns formatted help text
  [[nodiscard]] std::string help_() const;
  [[nodiscard]] std::string unknown_() const;
  [[nodiscard]] std::string version_topic_() const;

  // Model configuration topics
  [[nodiscard]] std::string model_() const;
  [[nodiscard]] std::string temperature_() const;
  [[nodiscard]] std::string max_tokens_() const;
  [[nodiscard]] std::string top_p_() const;
  [[nodiscard]] std::string top_k_() const;
  [[nodiscard]] std::string context_window_() const;

  // Streaming and output topics
  [[nodiscard]] std::string stream_() const;
  [[nodiscard]] std::string output_format_() const;
  [[nodiscard]] std::string output_dir_() const;

  // API configuration topics
  [[nodiscard]] std::string api_key_() const;
  [[nodiscard]] std::string endpoint_() const;
  [[nodiscard]] std::string timeout_() const;
  [[nodiscard]] std::string retry_count_() const;

  // Behavior flag topics
  [[nodiscard]] std::string disable_safety_() const;
  [[nodiscard]] std::string verbose_() const;
  [[nodiscard]] std::string dry_run_() const;
  [[nodiscard]] std::string enable_cache_() const;
  [[nodiscard]] std::string disable_cache_() const;

  // File option topics
  [[nodiscard]] std::string config_file_() const;
  [[nodiscard]] std::string input_file_() const;
  [[nodiscard]] std::string log_file_() const;
  [[nodiscard]] std::string log_level_() const;

  // System topics
  [[nodiscard]] std::string system_prompt_() const;

  // Map the given string option to enum help topic
  [[nodiscard]] Topic_ stoenum_();
  // Removes all leading hyphens from the look_up_option_ string.
  void remove_leading_hyphens_algo_inplace_();
  [[nodiscard]] help_ret_topic_status_ get_help_topic_(Topic_ flag) const;
};

} // namespace nutsloop::claude_impl
