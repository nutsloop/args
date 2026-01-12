# nutsloop/args

A modern C++23 library for beautiful and type-safe command-line argument parsing.

## Features

- **Type-safe argument parsing** - String, numeric (unsigned long long), and boolean argument types
- **Custom validation** - Extensible checker classes for input validation
- **Comprehensive help system** - Built-in help generation with topic-specific documentation
- **Default values** - Support for default values and environment variable fallbacks
- **Switch handling** - Automatic `--enable-*` and `--disable-*` switch parsing
- **File path validation** - Built-in filesystem path validation and normalization
- **Concept-based design** - Uses C++20/23 concepts for type constraints
- **Header-mostly library** - Minimal compilation overhead with inline implementations

## Requirements

- C++23 compatible compiler (GCC 13+, Clang 16+, or Apple Clang with `-fexperimental-library`)
- Meson build system (>= 0.60)

## Building

```bash
meson setup build
meson compile -C build

# With examples
meson setup build -Dbuild_demo=true
meson compile -C build
```

## Quick Start

```c++
#include "args.h++"

int main(int argc, char* argv[]) {
    // Create parser with custom check and help classes
    nutsloop::args::sequencer<MyCheck, MyHelp> parser(argc, argv);

    // Check for flags
    if (parser.has("verbose")) {
        // --verbose was passed
    }

    // Get typed values with validation
    auto model = parser.get_option_string("model").model();
    auto max_tokens = parser.get_option_uint("max-tokens").max_tokens();
    auto stream = parser.get_option_bool("stream").stream();

    // Access raw arguments
    const auto& args = parser.get_args();

    return 0;
}
```

## Core API

### Creating a Parser

```c++
nutsloop::args::sequencer<CheckerClass, HelperClass> parser(
    argc,
    argv,
    skip_digit_check,  // Optional: keys to skip numeric conversion
    version            // Optional: version tuple {major, minor, patch}
);
```

### Checking for Arguments

```c++
bool has_flag = parser.has("verbose");
```

### Retrieving Arguments

```c++
// Get with custom validation (returns CheckerClass)
auto checked = parser.get_option_string("key");
auto value = checked.my_validation_method();

// Get raw typed value
auto str = parser.get_arg<std::string>("key");      // std::optional<std::string>
auto num = parser.get_arg<unsigned long long>("n"); // std::optional<unsigned long long>
auto flag = parser.get_arg<bool>("flag");           // std::optional<bool>
```

### Help System

```c++
if (parser.has("help")) {
    auto topic = parser.get_arg<std::string>("help").value_or("help");
    auto helper = parser.get_help(topic);
    return helper.print();
}
```

## Custom Validation

Create a checker class to implement custom validation logic:

```c++
namespace myapp {

class check {
public:
    explicit check(nutsloop::args::args_key_value_t_ value = nullptr)
        : value_(std::move(value)) {}

    [[nodiscard]] std::string port() const {
        if (std::holds_alternative<unsigned long long>(value_)) {
            auto p = std::get<unsigned long long>(value_);
            if (p < 1 || p > 65535) {
                throw std::out_of_range("port must be 1-65535");
            }
            return std::to_string(p);
        }
        return "8080"; // default
    }

    [[nodiscard]] bool verbose() const {
        if (std::holds_alternative<bool>(value_)) {
            return std::get<bool>(value_);
        }
        return false; // default
    }

private:
    nutsloop::args::args_key_value_t_ value_;
};

} // namespace myapp
```

## Custom Help System

Create a helper class for contextual help:

```c++
namespace myapp {

class help {
public:
    explicit help(std::string topic, nutsloop::args::version_t version)
        : topic_(std::move(topic)), version_(version) {}

    [[nodiscard]] int print() {
        std::cout << to_string();
        return 0;
    }

    [[nodiscard]] std::string to_string() {
        if (topic_ == "version") {
            return std::format("v{}.{}.{}\n",
                version_[0], version_[1], version_[2]);
        }
        return "Usage: myapp [options]\n";
    }

private:
    std::string topic_;
    nutsloop::args::version_t version_;
};

} // namespace myapp
```

## Argument Parsing Behavior

### Key-Value Arguments

```bash
--model=claude-sonnet-4-20250514    # String value
--max-tokens=8192                    # Numeric value
--temperature=0.7                    # Treated as string if in skip_digit_check
```

### Boolean Switches

```bash
--verbose        # Sets to true
--stream         # Sets to true
```

### Enable/Disable Switches

```bash
--enable-cache   # Sets enable-cache to true
--disable-cache  # Sets disable-cache to true
```

### Skip Digit Check

For arguments that look numeric but should remain strings:

```c++
static const nutsloop::args::skip_digit_check_t SKIP = {
    {"temperature", "top-p", "api-key"}
};

nutsloop::args::sequencer<MyCheck, MyHelp> parser(argc, argv, SKIP, VERSION);
```

## Example: AI Model CLI

See `examples/claude_impl.c++` for a comprehensive example implementing an AI model configuration CLI with:

- Model selection with validation
- Temperature and sampling parameters
- API configuration with environment variable fallback
- File path validation
- Verbose output and dry-run modes
- Complete help system

```bash
# Run with help
./claude-impl --help

# Get help for specific option
./claude-impl --help=model

# Configure and run
./claude-impl --model=claude-sonnet-4-20250514 --max-tokens=8192 --stream --verbose
```

## Project Structure

```
include/
  args.h++                    # Main header
  args/
    option_types.h++          # Option type traits
    types/                    # Type definitions
    inline/                   # Inline implementations
src/
  args/                       # Library implementation
examples/
  claude_impl.c++             # Example application
  claude_impl/
    check.h++                 # Custom validation
    help.h++                  # Custom help system
    help/text/                # Help text constants
```

## License

Licensed under the Apache License, Version 2.0. See [LICENSE](LICENSE) for the full license text.
