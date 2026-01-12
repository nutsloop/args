#include "../help.h++"

namespace nutsloop::claude_impl {

help::help_ret_topic_status_ help::get_help_topic_(const Topic_ flag) const {

  std::string topic_str;
  int status_code = 0; // Default to success

  switch (flag) {
  // Help and version
  case Topic_::help:
    topic_str = help_();
    break;
  case Topic_::version:
    topic_str = version_topic_();
    break;

  // Model configuration
  case Topic_::model:
    topic_str = model_();
    break;
  case Topic_::temperature:
    topic_str = temperature_();
    break;
  case Topic_::max_tokens:
    topic_str = max_tokens_();
    break;
  case Topic_::top_p:
    topic_str = top_p_();
    break;
  case Topic_::top_k:
    topic_str = top_k_();
    break;
  case Topic_::context_window:
    topic_str = context_window_();
    break;

  // Streaming and output
  case Topic_::stream:
    topic_str = stream_();
    break;
  case Topic_::output_format:
    topic_str = output_format_();
    break;
  case Topic_::output_dir:
    topic_str = output_dir_();
    break;

  // API configuration
  case Topic_::api_key:
    topic_str = api_key_();
    break;
  case Topic_::endpoint:
    topic_str = endpoint_();
    break;
  case Topic_::timeout:
    topic_str = timeout_();
    break;
  case Topic_::retry_count:
    topic_str = retry_count_();
    break;

  // Behavior flags
  case Topic_::disable_safety:
    topic_str = disable_safety_();
    break;
  case Topic_::verbose:
    topic_str = verbose_();
    break;
  case Topic_::dry_run:
    topic_str = dry_run_();
    break;
  case Topic_::enable_cache:
    topic_str = enable_cache_();
    break;
  case Topic_::disable_cache:
    topic_str = disable_cache_();
    break;

  // File options
  case Topic_::config_file:
    topic_str = config_file_();
    break;
  case Topic_::input_file:
    topic_str = input_file_();
    break;
  case Topic_::log_file:
    topic_str = log_file_();
    break;
  case Topic_::log_level:
    topic_str = log_level_();
    break;

  // System
  case Topic_::system_prompt:
    topic_str = system_prompt_();
    break;

  default:
    topic_str = unknown_();
    status_code = 1;
    break;
  }

  return {topic_str, status_code};
}

} // namespace nutsloop::claude_impl
