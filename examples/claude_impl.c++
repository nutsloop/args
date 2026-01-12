/**
 * @file claude_impl.c++
 * @brief Extensive example demonstrating the nutsloop::args library
 *
 * This example implements a CLI tool for configuring AI model parameters,
 * showcasing all features of the args library including:
 * - String, numeric, and boolean argument parsing
 * - Custom validation via the check class
 * - Comprehensive help system via the help class
 * - Default values and environment variable fallbacks
 * - File path validation
 * - Switch handling (--enable-*, --disable-*)
 *
 * Usage examples:
 *   claude-impl --help
 *   claude-impl --help=model
 *   claude-impl --model=claude-sonnet-4-20250514 --max-tokens=8192
 *   claude-impl --stream --temperature=0.7 --verbose
 *   claude-impl --config-file=./config.json --dry-run
 */

#include "args.h++"
#include "claude_impl/check.h++"
#include "claude_impl/help.h++"

#include <exception>
#include <filesystem>
#include <format>
#include <iostream>
#include <string>

// Version information
static constexpr nutsloop::args::version_t VERSION = {1, 0, 0};

// Skip digit conversion for these options (treat as strings even if numeric)
static const nutsloop::args::skip_digit_check_t SKIP_DIGIT_CHECK = {
    {"temperature", "top-p", "api-key", "system-prompt"}};

void print_configuration(
    const std::string &model, const std::string &temperature,
    unsigned long long max_tokens, const std::string &top_p,
    unsigned long long top_k, unsigned long long context_window, bool stream,
    const std::string &output_format, const std::filesystem::path &output_dir,
    const std::string &endpoint, unsigned long long timeout,
    unsigned long long retry_count, bool verbose, bool dry_run,
    bool cache_enabled, const std::string &log_level,
    const std::filesystem::path &log_file,
    const std::filesystem::path &config_file,
    const std::filesystem::path &input_file, const std::string &system_prompt) {
  std::cout << "\n";
  std::cout << "========================================\n";
  std::cout << "       Claude Implementation Config     \n";
  std::cout << "========================================\n\n";

  std::cout << "MODEL CONFIGURATION\n";
  std::cout << "  Model:          " << model << "\n";
  std::cout << "  Temperature:    " << temperature << "\n";
  std::cout << "  Max Tokens:     " << max_tokens << "\n";
  std::cout << "  Top-P:          " << top_p << "\n";
  std::cout << "  Top-K:          " << top_k << "\n";
  std::cout << "  Context Window: " << context_window << "\n";
  std::cout << "\n";

  std::cout << "OUTPUT SETTINGS\n";
  std::cout << "  Streaming:      " << (stream ? "enabled" : "disabled")
            << "\n";
  std::cout << "  Output Format:  " << output_format << "\n";
  std::cout << "  Output Dir:     " << output_dir.string() << "\n";
  std::cout << "\n";

  std::cout << "API CONFIGURATION\n";
  std::cout << "  Endpoint:       " << endpoint << "\n";
  std::cout << "  Timeout:        " << timeout << " seconds\n";
  std::cout << "  Retry Count:    " << retry_count << "\n";
  std::cout << "  API Key:        " << "(configured)\n";
  std::cout << "\n";

  std::cout << "BEHAVIOR FLAGS\n";
  std::cout << "  Verbose:        " << (verbose ? "yes" : "no") << "\n";
  std::cout << "  Dry Run:        " << (dry_run ? "yes" : "no") << "\n";
  std::cout << "  Cache:          " << (cache_enabled ? "enabled" : "disabled")
            << "\n";
  std::cout << "\n";

  std::cout << "LOGGING\n";
  std::cout << "  Log Level:      " << log_level << "\n";
  if (!log_file.empty()) {
    std::cout << "  Log File:       " << log_file.string() << "\n";
  }
  std::cout << "\n";

  std::cout << "FILES\n";
  if (!config_file.empty()) {
    std::cout << "  Config File:    " << config_file.string() << "\n";
  }
  if (!input_file.empty()) {
    std::cout << "  Input File:     " << input_file.string() << "\n";
  }
  std::cout << "\n";

  if (!system_prompt.empty()) {
    std::cout << "SYSTEM PROMPT\n";
    std::cout << "  \"" << system_prompt.substr(0, 50);
    if (system_prompt.length() > 50)
      std::cout << "...";
    std::cout << "\"\n";
    std::cout << "\n";
  }

  std::cout << "========================================\n";
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "claude-impl - AI Model Configuration CLI\n";
    std::cout << "Version: " << VERSION[0] << "." << VERSION[1] << "."
              << VERSION[2] << "\n\n";
    std::cout << "Usage: " << argv[0] << " [options]\n\n";
    std::cout << "Run with --help for available options.\n";
    return 0;
  }

  try {
    // Create the argument parser with custom check and help classes
    nutsloop::args::sequencer<nutsloop::claude_impl::check,
                              nutsloop::claude_impl::help>
        parser(argc, argv, SKIP_DIGIT_CHECK, VERSION);

    // ─────────────────────────────────────────────────────────────────────
    // Handle help requests
    // ─────────────────────────────────────────────────────────────────────
    if (parser.has("help") || parser.has("?")) {
      auto topic = parser.get_arg<std::string>("help").value_or(
          parser.get_arg<std::string>("?").value_or("help"));
      auto helper = parser.get_help(topic);
      return helper.print();
    }

    // ─────────────────────────────────────────────────────────────────────
    // Model Configuration
    // ─────────────────────────────────────────────────────────────────────
    std::string model = parser.get_option_string("model").model();
    std::string temperature =
        parser.get_option_string("temperature").temperature();
    unsigned long long max_tokens =
        parser.get_option_uint("max-tokens").max_tokens();
    std::string top_p = parser.get_option_string("top-p").top_p();
    unsigned long long top_k = parser.get_option_uint("top-k").top_k();
    unsigned long long context_window =
        parser.get_option_uint("context-window").context_window();

    // ─────────────────────────────────────────────────────────────────────
    // Streaming and Output
    // ─────────────────────────────────────────────────────────────────────
    bool stream = parser.get_option_bool("stream").stream();
    std::string output_format =
        parser.get_option_string("output-format").output_format();
    std::filesystem::path output_dir =
        parser.get_option_string("output-dir").output_dir();

    // ─────────────────────────────────────────────────────────────────────
    // API Configuration
    // ─────────────────────────────────────────────────────────────────────
    // Note: In a real implementation, you would validate the API key
    // For this example, we'll make it optional and use a placeholder
    std::string api_key;
    try {
      api_key = parser.get_option_string("api-key").api_key();
    } catch (const std::exception &) {
      // API key not provided - that's okay for demo purposes
      api_key = "(not configured - set ANTHROPIC_API_KEY or use --api-key)";
    }

    std::string endpoint = parser.get_option_string("endpoint").endpoint();
    unsigned long long timeout = parser.get_option_uint("timeout").timeout();
    unsigned long long retry_count =
        parser.get_option_uint("retry-count").retry_count();

    // ─────────────────────────────────────────────────────────────────────
    // Behavior Flags
    // ─────────────────────────────────────────────────────────────────────
    bool disable_safety =
        parser.get_option_bool("disable-safety").disable_safety();
    bool verbose = parser.get_option_bool("verbose").verbose();
    bool dry_run = parser.get_option_bool("dry-run").dry_run();

    // Handle cache flags (enable-cache is default true, disable-cache
    // overrides)
    bool cache_enabled = parser.get_option_bool("enable-cache").enable_cache();
    if (parser.has("disable-cache")) {
      cache_enabled = !parser.get_option_bool("disable-cache").disable_cache();
    }

    // ─────────────────────────────────────────────────────────────────────
    // File Options
    // ─────────────────────────────────────────────────────────────────────
    std::filesystem::path config_file =
        parser.get_option_string("config-file").config_file();
    std::filesystem::path input_file =
        parser.get_option_string("input-file").input_file();
    std::filesystem::path log_file =
        parser.get_option_string("log-file").log_file();
    std::string log_level = parser.get_option_string("log-level").log_level();

    // ─────────────────────────────────────────────────────────────────────
    // System Prompt
    // ─────────────────────────────────────────────────────────────────────
    std::string system_prompt =
        parser.get_option_string("system-prompt").system_prompt();

    // ─────────────────────────────────────────────────────────────────────
    // Safety Warning
    // ─────────────────────────────────────────────────────────────────────
    if (disable_safety) {
      std::cerr << "\n";
      std::cerr << "WARNING: Safety checks are disabled!\n";
      std::cerr << "This may allow potentially harmful operations.\n";
      std::cerr << "\n";
    }

    // ─────────────────────────────────────────────────────────────────────
    // Dry Run Mode
    // ─────────────────────────────────────────────────────────────────────
    if (dry_run) {
      std::cout << "\n[DRY RUN MODE - No API calls will be made]\n";
    }

    // ─────────────────────────────────────────────────────────────────────
    // Display Configuration
    // ─────────────────────────────────────────────────────────────────────
    if (verbose || dry_run) {
      print_configuration(model, temperature, max_tokens, top_p, top_k,
                          context_window, stream, output_format, output_dir,
                          endpoint, timeout, retry_count, verbose, dry_run,
                          cache_enabled, log_level, log_file, config_file,
                          input_file, system_prompt);
    } else {
      // Brief output
      std::cout << "Configuration loaded successfully.\n";
      std::cout << "  Model: " << model << "\n";
      std::cout << "  Max Tokens: " << max_tokens << "\n";
      std::cout << "  Stream: " << (stream ? "yes" : "no") << "\n";
      std::cout << "\nRun with --verbose for full configuration details.\n";
    }

    // ─────────────────────────────────────────────────────────────────────
    // Example: Accessing raw arguments
    // ─────────────────────────────────────────────────────────────────────
    if (verbose) {
      std::cout << "\n--- Raw Arguments Debug ---\n";
      const auto &all_args = parser.get_args();
      for (const auto &[key, value] : all_args) {
        std::cout << "  " << key << " = ";
        if (std::holds_alternative<std::string>(value)) {
          std::cout << "\"" << std::get<std::string>(value) << "\" (string)\n";
        } else if (std::holds_alternative<unsigned long long>(value)) {
          std::cout << std::get<unsigned long long>(value) << " (uint)\n";
        } else if (std::holds_alternative<bool>(value)) {
          std::cout << (std::get<bool>(value) ? "true" : "false")
                    << " (bool)\n";
        } else {
          std::cout << "(null)\n";
        }
      }

      // Check for subcommand
      const auto &command = parser.get_command();
      if (!command.empty()) {
        std::cout << "\n  Subcommand: " << command << "\n";
      }
    }

  } catch (const std::exception &ex) {
    std::cerr << "claude-impl error: " << ex.what() << "\n";
    std::cerr << "Run with --help for usage information.\n";
    return 1;
  }

  return 0;
}
