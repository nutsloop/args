#pragma once
#include "args/types/args_key_value_t.h++"

#include <algorithm>
#include <array>
#include <cctype>
#include <filesystem>
#include <format>
#include <regex>
#include <stdexcept>
#include <string>
#include <utility>
#include <variant>

namespace nutsloop::claude_impl {

using nutsloop::args::args_key_value_t_;

class check {
public:
  explicit check(args_key_value_t_ value = nullptr) : value_(std::move(value)) {}

  ~check() = default;

  // ─────────────────────────────────────────────────────────────────────────────
  // STRING OPTIONS
  // ─────────────────────────────────────────────────────────────────────────────

  [[nodiscard]] std::string model() const {
    std::string model_name;

    if (std::holds_alternative<std::string>(this->value_)) {
      model_name = std::get<std::string>(this->value_);
    } else if (std::holds_alternative<std::nullptr_t>(this->value_)) {
      model_name = "claude-opus-4-5-20251101";
    } else {
      throw std::invalid_argument(
          std::format("invalid argument type for --model, expected string"));
    }

    static constexpr std::array valid_models = {
        "claude-opus-4-5-20251101",
        "claude-sonnet-4-20250514",
        "claude-3-5-haiku-20241022",
        "claude-3-opus-20240229",
        "claude-3-sonnet-20240229",
        "claude-3-haiku-20240307",
    };

    const auto it = std::find(valid_models.begin(), valid_models.end(), model_name);
    if (it == valid_models.end()) {
      std::string valid_list;
      for (const auto &m : valid_models) {
        if (!valid_list.empty()) valid_list += ", ";
        valid_list += m;
      }
      throw std::invalid_argument(
          std::format("--model '{}' is not a valid model. Valid models: {}",
                      model_name, valid_list));
    }

    return model_name;
  }

  [[nodiscard]] std::string api_key() const {
    std::string key;

    if (std::holds_alternative<std::string>(this->value_)) {
      key = std::get<std::string>(this->value_);
    } else if (std::holds_alternative<std::nullptr_t>(this->value_)) {
      // Check environment variable
      const char* env_key = std::getenv("ANTHROPIC_API_KEY");
      if (env_key != nullptr) {
        key = env_key;
      } else {
        throw std::invalid_argument(
            "--api-key is required. Provide via --api-key=<key> or set ANTHROPIC_API_KEY environment variable");
      }
    } else {
      throw std::invalid_argument(
          std::format("invalid argument type for --api-key, expected string"));
    }

    // Validate API key format (sk-ant-...)
    if (key.length() < 20) {
      throw std::invalid_argument("--api-key appears to be invalid (too short)");
    }

    if (key.substr(0, 7) != "sk-ant-") {
      throw std::invalid_argument(
          "--api-key must start with 'sk-ant-' prefix");
    }

    return key;
  }

  [[nodiscard]] std::string endpoint() const {
    std::string url;

    if (std::holds_alternative<std::string>(this->value_)) {
      url = std::get<std::string>(this->value_);
    } else if (std::holds_alternative<std::nullptr_t>(this->value_)) {
      url = "https://api.anthropic.com/v1/messages";
    } else {
      throw std::invalid_argument(
          std::format("invalid argument type for --endpoint, expected string"));
    }

    // Basic URL validation
    if (url.substr(0, 8) != "https://" && url.substr(0, 7) != "http://") {
      throw std::invalid_argument(
          std::format("--endpoint '{}' must be a valid URL starting with http:// or https://", url));
    }

    return url;
  }

  [[nodiscard]] std::string output_format() const {
    std::string format;

    if (std::holds_alternative<std::string>(this->value_)) {
      format = std::get<std::string>(this->value_);
    } else if (std::holds_alternative<std::nullptr_t>(this->value_)) {
      format = "json";
    } else {
      throw std::invalid_argument(
          std::format("invalid argument type for --output-format, expected string"));
    }

    // Convert to lowercase for comparison
    std::string lower_format = format;
    std::transform(lower_format.begin(), lower_format.end(), lower_format.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    static constexpr std::array valid_formats = {"json", "text", "markdown", "xml"};
    const auto it = std::find(valid_formats.begin(), valid_formats.end(), lower_format);

    if (it == valid_formats.end()) {
      throw std::invalid_argument(
          std::format("--output-format '{}' is invalid. Valid formats: json, text, markdown, xml", format));
    }

    return lower_format;
  }

  [[nodiscard]] std::string log_level() const {
    std::string level;

    if (std::holds_alternative<std::string>(this->value_)) {
      level = std::get<std::string>(this->value_);
    } else if (std::holds_alternative<std::nullptr_t>(this->value_)) {
      level = "info";
    } else {
      throw std::invalid_argument(
          std::format("invalid argument type for --log-level, expected string"));
    }

    // Convert to lowercase
    std::string lower_level = level;
    std::transform(lower_level.begin(), lower_level.end(), lower_level.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    static constexpr std::array valid_levels = {"debug", "info", "warn", "error", "none"};
    const auto it = std::find(valid_levels.begin(), valid_levels.end(), lower_level);

    if (it == valid_levels.end()) {
      throw std::invalid_argument(
          std::format("--log-level '{}' is invalid. Valid levels: debug, info, warn, error, none", level));
    }

    return lower_level;
  }

  [[nodiscard]] std::string temperature() const {
    std::string temp_str;

    if (std::holds_alternative<std::string>(this->value_)) {
      temp_str = std::get<std::string>(this->value_);
    } else if (std::holds_alternative<unsigned long long>(this->value_)) {
      // Handle integer input (e.g., --temperature=1)
      temp_str = std::to_string(std::get<unsigned long long>(this->value_));
    } else if (std::holds_alternative<std::nullptr_t>(this->value_)) {
      temp_str = "1.0";
    } else {
      throw std::invalid_argument(
          std::format("invalid argument type for --temperature, expected decimal number"));
    }

    // Validate it's a valid decimal number
    try {
      double temp = std::stod(temp_str);
      if (temp < 0.0 || temp > 2.0) {
        throw std::out_of_range(
            std::format("--temperature {} is out of range. Must be between 0.0 and 2.0", temp_str));
      }
    } catch (const std::invalid_argument&) {
      throw std::invalid_argument(
          std::format("--temperature '{}' is not a valid decimal number", temp_str));
    }

    return temp_str;
  }

  [[nodiscard]] std::string top_p() const {
    std::string top_p_str;

    if (std::holds_alternative<std::string>(this->value_)) {
      top_p_str = std::get<std::string>(this->value_);
    } else if (std::holds_alternative<unsigned long long>(this->value_)) {
      top_p_str = std::to_string(std::get<unsigned long long>(this->value_));
    } else if (std::holds_alternative<std::nullptr_t>(this->value_)) {
      top_p_str = "0.9";
    } else {
      throw std::invalid_argument(
          std::format("invalid argument type for --top-p, expected decimal number"));
    }

    try {
      double p = std::stod(top_p_str);
      if (p < 0.0 || p > 1.0) {
        throw std::out_of_range(
            std::format("--top-p {} is out of range. Must be between 0.0 and 1.0", top_p_str));
      }
    } catch (const std::invalid_argument&) {
      throw std::invalid_argument(
          std::format("--top-p '{}' is not a valid decimal number", top_p_str));
    }

    return top_p_str;
  }

  [[nodiscard]] std::string system_prompt() const {
    std::string prompt;

    if (std::holds_alternative<std::string>(this->value_)) {
      prompt = std::get<std::string>(this->value_);
    } else if (std::holds_alternative<std::nullptr_t>(this->value_)) {
      prompt = "";
    } else {
      throw std::invalid_argument(
          std::format("invalid argument type for --system-prompt, expected string"));
    }

    // Warn if system prompt is very long
    if (prompt.length() > 10000) {
      throw std::invalid_argument(
          std::format("--system-prompt is too long ({} chars). Maximum recommended: 10000 characters",
                      prompt.length()));
    }

    return prompt;
  }

  // ─────────────────────────────────────────────────────────────────────────────
  // NUMERIC OPTIONS
  // ─────────────────────────────────────────────────────────────────────────────

  [[nodiscard]] unsigned long long max_tokens() const {
    unsigned long long tokens;

    if (std::holds_alternative<unsigned long long>(this->value_)) {
      tokens = std::get<unsigned long long>(this->value_);
    } else if (std::holds_alternative<std::nullptr_t>(this->value_)) {
      tokens = 4096;
    } else {
      throw std::invalid_argument(
          std::format("invalid argument type for --max-tokens, expected number"));
    }

    if (tokens == 0) {
      throw std::invalid_argument("--max-tokens must be greater than 0");
    }

    // Claude's maximum context window
    if (tokens > 200000) {
      throw std::out_of_range(
          std::format("--max-tokens {} exceeds maximum allowed value of 200000", tokens));
    }

    return tokens;
  }

  [[nodiscard]] unsigned long long top_k() const {
    unsigned long long k;

    if (std::holds_alternative<unsigned long long>(this->value_)) {
      k = std::get<unsigned long long>(this->value_);
    } else if (std::holds_alternative<std::nullptr_t>(this->value_)) {
      k = 40;
    } else {
      throw std::invalid_argument(
          std::format("invalid argument type for --top-k, expected number"));
    }

    if (k == 0) {
      throw std::invalid_argument("--top-k must be greater than 0");
    }

    if (k > 500) {
      throw std::out_of_range(
          std::format("--top-k {} is too high. Maximum recommended value is 500", k));
    }

    return k;
  }

  [[nodiscard]] unsigned long long timeout() const {
    unsigned long long seconds;

    if (std::holds_alternative<unsigned long long>(this->value_)) {
      seconds = std::get<unsigned long long>(this->value_);
    } else if (std::holds_alternative<std::nullptr_t>(this->value_)) {
      seconds = 120;
    } else {
      throw std::invalid_argument(
          std::format("invalid argument type for --timeout, expected number"));
    }

    if (seconds == 0) {
      throw std::invalid_argument("--timeout must be greater than 0 seconds");
    }

    if (seconds > 3600) {
      throw std::out_of_range(
          std::format("--timeout {} seconds is too high. Maximum: 3600 seconds (1 hour)", seconds));
    }

    return seconds;
  }

  [[nodiscard]] unsigned long long retry_count() const {
    unsigned long long count;

    if (std::holds_alternative<unsigned long long>(this->value_)) {
      count = std::get<unsigned long long>(this->value_);
    } else if (std::holds_alternative<std::nullptr_t>(this->value_)) {
      count = 3;
    } else {
      throw std::invalid_argument(
          std::format("invalid argument type for --retry-count, expected number"));
    }

    if (count > 10) {
      throw std::out_of_range(
          std::format("--retry-count {} is too high. Maximum: 10 retries", count));
    }

    return count;
  }

  [[nodiscard]] unsigned long long context_window() const {
    unsigned long long window;

    if (std::holds_alternative<unsigned long long>(this->value_)) {
      window = std::get<unsigned long long>(this->value_);
    } else if (std::holds_alternative<std::nullptr_t>(this->value_)) {
      window = 200000;
    } else {
      throw std::invalid_argument(
          std::format("invalid argument type for --context-window, expected number"));
    }

    static constexpr std::array valid_windows = {
        8192ULL, 16384ULL, 32768ULL, 65536ULL, 100000ULL, 200000ULL
    };

    const auto it = std::find(valid_windows.begin(), valid_windows.end(), window);
    if (it == valid_windows.end()) {
      throw std::invalid_argument(
          std::format("--context-window {} is not a valid size. Valid sizes: 8192, 16384, 32768, 65536, 100000, 200000", window));
    }

    return window;
  }

  // ─────────────────────────────────────────────────────────────────────────────
  // BOOLEAN SWITCH OPTIONS
  // ─────────────────────────────────────────────────────────────────────────────

  [[nodiscard]] bool stream() const {
    bool value;

    if (std::holds_alternative<bool>(this->value_)) {
      value = std::get<bool>(this->value_);
    } else if (std::holds_alternative<std::nullptr_t>(this->value_)) {
      value = false;
    } else {
      throw std::invalid_argument(
          std::format("--stream is a simple switch that should omit the `=` sign."));
    }

    return value;
  }

  [[nodiscard]] bool disable_safety() const {
    bool value;

    if (std::holds_alternative<bool>(this->value_)) {
      value = std::get<bool>(this->value_);
    } else if (std::holds_alternative<std::nullptr_t>(this->value_)) {
      value = false;
    } else {
      throw std::invalid_argument(
          std::format("--disable-safety is a switch that should omit the `=` sign."));
    }

    return value;
  }

  [[nodiscard]] bool verbose() const {
    bool value;

    if (std::holds_alternative<bool>(this->value_)) {
      value = std::get<bool>(this->value_);
    } else if (std::holds_alternative<std::nullptr_t>(this->value_)) {
      value = false;
    } else {
      throw std::invalid_argument(
          std::format("--verbose is a simple switch that should omit the `=` sign."));
    }

    return value;
  }

  [[nodiscard]] bool dry_run() const {
    bool value;

    if (std::holds_alternative<bool>(this->value_)) {
      value = std::get<bool>(this->value_);
    } else if (std::holds_alternative<std::nullptr_t>(this->value_)) {
      value = false;
    } else {
      throw std::invalid_argument(
          std::format("--dry-run is a simple switch that should omit the `=` sign."));
    }

    return value;
  }

  [[nodiscard]] bool enable_cache() const {
    bool value;

    if (std::holds_alternative<bool>(this->value_)) {
      value = std::get<bool>(this->value_);
    } else if (std::holds_alternative<std::nullptr_t>(this->value_)) {
      value = true; // Cache enabled by default
    } else {
      throw std::invalid_argument(
          std::format("--enable-cache is a switch that should omit the `=` sign."));
    }

    return value;
  }

  [[nodiscard]] bool disable_cache() const {
    bool value;

    if (std::holds_alternative<bool>(this->value_)) {
      value = std::get<bool>(this->value_);
    } else if (std::holds_alternative<std::nullptr_t>(this->value_)) {
      value = false;
    } else {
      throw std::invalid_argument(
          std::format("--disable-cache is a switch that should omit the `=` sign."));
    }

    return value;
  }

  // ─────────────────────────────────────────────────────────────────────────────
  // FILE PATH OPTIONS
  // ─────────────────────────────────────────────────────────────────────────────

  [[nodiscard]] std::filesystem::path config_file() const {
    std::string raw_path;

    if (std::holds_alternative<std::string>(this->value_)) {
      raw_path = std::get<std::string>(this->value_);
    } else if (std::holds_alternative<std::nullptr_t>(this->value_)) {
      raw_path = "";
    } else {
      throw std::invalid_argument(
          std::format("invalid argument type for --config-file, expected string"));
    }

    if (raw_path.empty()) {
      return {};
    }

    std::filesystem::path path(raw_path);

    if (!path.is_absolute()) {
      path = std::filesystem::absolute(path);
    }

    if (!std::filesystem::exists(path)) {
      throw std::runtime_error(
          std::format("--config-file path '{}' does not exist", path.string()));
    }

    if (!std::filesystem::is_regular_file(path)) {
      throw std::runtime_error(
          std::format("--config-file path '{}' is not a regular file", path.string()));
    }

    // Validate file extension
    auto ext = path.extension().string();
    if (ext != ".json" && ext != ".yaml" && ext != ".yml" && ext != ".toml") {
      throw std::invalid_argument(
          std::format("--config-file must be a .json, .yaml, .yml, or .toml file, got '{}'", ext));
    }

    return path;
  }

  [[nodiscard]] std::filesystem::path output_dir() const {
    std::string raw_path;

    if (std::holds_alternative<std::string>(this->value_)) {
      raw_path = std::get<std::string>(this->value_);
    } else if (std::holds_alternative<std::nullptr_t>(this->value_)) {
      raw_path = ".";
    } else {
      throw std::invalid_argument(
          std::format("invalid argument type for --output-dir, expected string"));
    }

    std::filesystem::path path(raw_path);

    if (!path.is_absolute()) {
      path = std::filesystem::absolute(path);
    }

    if (!std::filesystem::exists(path)) {
      throw std::runtime_error(
          std::format("--output-dir path '{}' does not exist", path.string()));
    }

    if (!std::filesystem::is_directory(path)) {
      throw std::runtime_error(
          std::format("--output-dir path '{}' is not a directory", path.string()));
    }

    return path;
  }

  [[nodiscard]] std::filesystem::path input_file() const {
    std::string raw_path;

    if (std::holds_alternative<std::string>(this->value_)) {
      raw_path = std::get<std::string>(this->value_);
    } else if (std::holds_alternative<std::nullptr_t>(this->value_)) {
      raw_path = "";
    } else {
      throw std::invalid_argument(
          std::format("invalid argument type for --input-file, expected string"));
    }

    if (raw_path.empty()) {
      return {};
    }

    std::filesystem::path path(raw_path);

    if (!path.is_absolute()) {
      path = std::filesystem::absolute(path);
    }

    if (!std::filesystem::exists(path)) {
      throw std::runtime_error(
          std::format("--input-file path '{}' does not exist", path.string()));
    }

    if (!std::filesystem::is_regular_file(path)) {
      throw std::runtime_error(
          std::format("--input-file path '{}' is not a regular file", path.string()));
    }

    return path;
  }

  [[nodiscard]] std::filesystem::path log_file() const {
    std::string raw_path;

    if (std::holds_alternative<std::string>(this->value_)) {
      raw_path = std::get<std::string>(this->value_);
    } else if (std::holds_alternative<std::nullptr_t>(this->value_)) {
      raw_path = "";
    } else {
      throw std::invalid_argument(
          std::format("invalid argument type for --log-file, expected string"));
    }

    if (raw_path.empty()) {
      return {};
    }

    std::filesystem::path path(raw_path);

    if (!path.is_absolute()) {
      path = std::filesystem::absolute(path);
    }

    // Check parent directory exists
    auto parent = path.parent_path();
    if (!parent.empty() && !std::filesystem::exists(parent)) {
      throw std::runtime_error(
          std::format("--log-file parent directory '{}' does not exist", parent.string()));
    }

    return path;
  }

private:
  args_key_value_t_ value_;
};

} // namespace nutsloop::claude_impl
