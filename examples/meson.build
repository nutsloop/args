# ─────────────────────────────────────────────────────────────────────────────
# Claude Implementation Example (AI Model Configuration CLI)
# ─────────────────────────────────────────────────────────────────────────────
claude_impl_inc = include_directories('claude_impl')

claude_impl_sources = files(
  # Core help implementation
  'claude_impl/help/help.c++',
  'claude_impl/help/print.c++',
  'claude_impl/help/to_string.c++',
  'claude_impl/help/set_option_list_.c++',
  'claude_impl/help/stoenum_.c++',
  'claude_impl/help/get_help_topic_.c++',
  'claude_impl/help/get_noun_name_.c++',
  'claude_impl/help/get_version_.c++',
  'claude_impl/help/remove_leading_hyphens_algo_inplace_.c++',

  # Help topic implementations
  'claude_impl/help/help_.c++',
  'claude_impl/help/unknown_.c++',
  'claude_impl/help/version_.c++',

  # Model configuration topics
  'claude_impl/help/model_.c++',
  'claude_impl/help/temperature_.c++',
  'claude_impl/help/max_tokens_.c++',
  'claude_impl/help/top_p_.c++',
  'claude_impl/help/top_k_.c++',
  'claude_impl/help/context_window_.c++',

  # Streaming and output topics
  'claude_impl/help/stream_.c++',
  'claude_impl/help/output_format_.c++',
  'claude_impl/help/output_dir_.c++',

  # API configuration topics
  'claude_impl/help/api_key_.c++',
  'claude_impl/help/endpoint_.c++',
  'claude_impl/help/timeout_.c++',
  'claude_impl/help/retry_count_.c++',

  # Behavior flag topics
  'claude_impl/help/disable_safety_.c++',
  'claude_impl/help/verbose_.c++',
  'claude_impl/help/dry_run_.c++',
  'claude_impl/help/enable_cache_.c++',
  'claude_impl/help/disable_cache_.c++',

  # File option topics
  'claude_impl/help/config_file_.c++',
  'claude_impl/help/input_file_.c++',
  'claude_impl/help/log_file_.c++',
  'claude_impl/help/log_level_.c++',

  # System topics
  'claude_impl/help/system_prompt_.c++',
)

claude_impl_src = files('claude_impl.c++')
claude_impl_exe = executable(
  'claude-impl',
  claude_impl_src,
  claude_impl_sources,
  include_directories: [args_inc, claude_impl_inc],
  dependencies: threads_dep,
  link_with: args_lib,
  install: false,
)

# ─────────────────────────────────────────────────────────────────────────────
# Integration Tests using claude-impl
# ─────────────────────────────────────────────────────────────────────────────
test_script = find_program('../tests/test_claude_impl.sh')

# Test cases
test_cases = [
  'no_args',
  'help',
  'help_topic',
  'valid_model',
  'invalid_model',
  'max_tokens',
  'max_tokens_invalid',
  'temperature',
  'temperature_out_of_range',
  'boolean_switches',
  'enable_disable_cache',
  'output_format',
  'output_format_invalid',
  'log_level',
  'multiple_options',
  'context_window_valid',
  'context_window_invalid',
]

foreach test_case : test_cases
  test(
    'claude_impl_' + test_case,
    test_script,
    args: [claude_impl_exe.full_path(), test_case],
    suite: 'integration',
    timeout: 30,
  )
endforeach
