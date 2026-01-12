#include "../help.h++"

namespace nutsloop::claude_impl {

void help::set_option_list_() {
  // Help and version
  option_list_.insert({"help", Topic_::help});
  option_list_.insert({"version", Topic_::version});

  // Model configuration
  option_list_.insert({"model", Topic_::model});
  option_list_.insert({"temperature", Topic_::temperature});
  option_list_.insert({"max-tokens", Topic_::max_tokens});
  option_list_.insert({"top-p", Topic_::top_p});
  option_list_.insert({"top-k", Topic_::top_k});
  option_list_.insert({"context-window", Topic_::context_window});

  // Streaming and output
  option_list_.insert({"stream", Topic_::stream});
  option_list_.insert({"output-format", Topic_::output_format});
  option_list_.insert({"output-dir", Topic_::output_dir});

  // API configuration
  option_list_.insert({"api-key", Topic_::api_key});
  option_list_.insert({"endpoint", Topic_::endpoint});
  option_list_.insert({"timeout", Topic_::timeout});
  option_list_.insert({"retry-count", Topic_::retry_count});

  // Behavior flags
  option_list_.insert({"disable-safety", Topic_::disable_safety});
  option_list_.insert({"verbose", Topic_::verbose});
  option_list_.insert({"dry-run", Topic_::dry_run});
  option_list_.insert({"enable-cache", Topic_::enable_cache});
  option_list_.insert({"disable-cache", Topic_::disable_cache});

  // File options
  option_list_.insert({"config-file", Topic_::config_file});
  option_list_.insert({"input-file", Topic_::input_file});
  option_list_.insert({"log-file", Topic_::log_file});
  option_list_.insert({"log-level", Topic_::log_level});

  // System
  option_list_.insert({"system-prompt", Topic_::system_prompt});
}

} // namespace nutsloop::claude_impl
