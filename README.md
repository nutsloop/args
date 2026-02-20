# nutsloop/args

nutsloop/args is a small, header-mostly C++23 library for parsing command-line arguments into typed values and handing them to your own validation and help classes. The library favors an explicit `--key=value` style, clear errors, and a minimal API surface.

**Goals**
- Provide a predictable parser for string, unsigned integer, and boolean switches.
- Keep the core API small and easy to integrate.
- Let applications implement their own validation and help logic.

**Non-goals**
- No positional argument parsing beyond an optional leading command token.
- No `--key value` parsing, no bundled short flags, no `--` terminator.
- No built-in defaults, environment variable lookup, or help text formatting.

**Requirements**
- C++23 compatible compiler.
- Standard library support for `std::format`.
- Meson build system.

**Build**
```bash
meson setup build
meson compile -C build
```

**Install**
```bash
meson install -C build
```

**Quick Start**
```c++
#include "args.h++"

namespace myapp {

class check {
public:
  explicit check(nutsloop::args::args_key_value_t_ value = nullptr)
      : value_(std::move(value)) {}

  [[nodiscard]] std::string model() const {
    if (auto s = std::get_if<std::string>(&value_)) {
      return *s;
    }
    return "default";
  }

  [[nodiscard]] unsigned long long max_tokens() const {
    if (auto n = std::get_if<unsigned long long>(&value_)) {
      return *n;
    }
    return 0;
  }

  [[nodiscard]] bool stream() const {
    if (auto b = std::get_if<bool>(&value_)) {
      return *b;
    }
    return false;
  }

private:
  nutsloop::args::args_key_value_t_ value_;
};

class help {
public:
  explicit help(std::string topic, nutsloop::args::version_t version)
      : topic_(std::move(topic)), version_(version) {}

  [[nodiscard]] int print() const {
    std::cout << to_string();
    return 0;
  }

  [[nodiscard]] std::string to_string() const {
    if (topic_ == "version") {
      return std::format("v{}.{}.{}\n", version_[0], version_[1], version_[2]);
    }
    return "Usage: myapp [options]\n";
  }

private:
  std::string topic_;
  nutsloop::args::version_t version_;
};

} // namespace myapp

int main(int argc, char *argv[]) {
  nutsloop::args::sequencer<myapp::check, myapp::help> parser(argc, argv);

  if (parser.has("verbose")) {
    // --verbose was passed
  }

  auto model = parser.get_option_string("model").model();
  auto max_tokens = parser.get_option_uint("max-tokens").max_tokens();
  auto stream = parser.get_option_bool("stream").stream();

  if (parser.has("help")) {
    auto topic = parser.get_arg<std::string>("help").value_or("help");
    return parser.get_help(topic).print();
  }

  return 0;
}
```

**Core API**
- `sequencer<CheckerClass, HelperClass>`
- `CheckerClass` must be constructible from `args_key_value_t_`.
- `HelperClass` is optional. If provided, it must be constructible from `std::string` and `version_t`.
- Use `sequencer<CheckerClass>` when you do not need help integration. `get_help` is only available when a helper is provided.
- `get_option_string`, `get_option_uint`, `get_option_bool`, `get_option_addr`
- `get_arg<T>` for `T` in `std::string`, `unsigned long long`, `bool`
- `has`, `get_args`, `get_command`, `get_some_args`

**Public Types**
- `args_key_value_t_` variant for individual values.
- `args_t` unordered map of parsed arguments.
- `args_list_t` and `args_list_command_t` unordered-set aliases.
- `args_command_t` string alias for the optional leading command.
- `skip_digit_check_t` optional set of keys that should remain strings.
- `version_t` and `version_opt_t` for `{major, minor, patch}` versioning.

**Type Utilities**
- `nutsloop::OptionTypes` concept for `std::string`, `unsigned long long`, and `bool`.
- `option_type_name_t<T>::get()` returns the type name as a `std::string_view`.

**Constructor**
```c++
nutsloop::args::sequencer<CheckerClass, HelperClass> parser(
    argc,
    argv,
    skip_digit_check, // optional
    version           // optional
);
```
- `skip_digit_check` is a `skip_digit_check_t` (optional set of keys).
- `version` is a `version_opt_t` (array `{major, minor, patch}`), default `0.0.1`.
- Parsing happens in the constructor and may throw `std::invalid_argument`.

**Parsing Rules**
- Options must start with `-` or `--`.
- Key-value options must use `=`. Example: `--model=claude`.
- Boolean switches are set by presence only. Example: `--verbose` sets `verbose=true`.
- `--enable-foo` sets `enable-foo=true` and `--disable-foo` sets `disable-foo=false`.
- A single-dash key like `-v` is supported. Bundled flags like `-abc` are treated as a single key.
- If the first argument does not start with `-`, it is stored as the command and removed from parsing.
- Any non-flag token after the optional command raises `std::invalid_argument`.
- Help is triggered when the key is `help` (for example `--help` or `-help`) or when the key starts with `?` (for example `--?`, `--?topic`, `-?`, or `-?topic`). With `=`, `--help=topic`, `-h=topic`, `--?=topic`, or `-?=topic` set the topic. Help stops parsing.
- `--version` or `-v` set the `version` key to a `major.minor.patch` string and stop parsing.
- A trailing `=` is rejected. Example: `--key=` throws.
- Providing no arguments (besides the program name) throws `std::invalid_argument`.
- Later values with the same key overwrite earlier ones.

**Type Conversion Rules**
- Values containing only digits and fitting in `unsigned long long` are stored as `unsigned long long`.
- All other values are stored as `std::string`.
- Negative numbers and floats are stored as `std::string`.
- If a key is in `skip_digit_check`, its value is always stored as `std::string`.

**Errors**
- Invalid input triggers `std::invalid_argument` exceptions from the parser or accessors.
- `nutsloop::args::error` is available for custom conflict reporting.

**Utilities**
- `sequencer::argv_to_string_` joins `argv` values with `|`.
- `sequencer::argv_to_string_ranges_` uses C++ ranges to join with a custom separator.
- `join` fills a destination string from a `char*` buffer with a custom separator.

**Project Layout**
- `include/args.h++` main public header.
- `include/args/inline/` inline implementations.
- `include/args/types/` public type aliases.
- `src/args/args_stub.c++` stub source for building a library target.
- `meson.build` Meson build definition.

**License**
Apache 2.0. See `LICENSE`.
