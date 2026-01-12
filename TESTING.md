# Testing Documentation

## Test Suite Overview

The nutsloop/args library includes a comprehensive integration test suite that validates functionality using the `claude-impl` example application.

## Test Results

```
Ok:                17
Fail:              0
```

**Status: ✓ All tests passing**

## Test Coverage

### Basic Functionality (3 tests)
- ✓ **no_args** - Shows version banner when no arguments provided
- ✓ **help** - Displays comprehensive help text with --help
- ✓ **help_topic** - Shows topic-specific help (e.g., --help=model)

### String Argument Parsing (5 tests)
- ✓ **valid_model** - Accepts valid model names from allowed list
- ✓ **invalid_model** - Rejects invalid model names with error message
- ✓ **output_format** - Validates and accepts output format (json, text, markdown, xml)
- ✓ **output_format_invalid** - Rejects invalid output formats
- ✓ **log_level** - Validates log level values (debug, info, warn, error, none)

### Numeric Argument Parsing (6 tests)
- ✓ **max_tokens** - Parses integer values correctly
- ✓ **max_tokens_invalid** - Rejects out-of-range values (>200000)
- ✓ **temperature** - Handles decimal numbers as strings (via skip_digit_check)
- ✓ **temperature_out_of_range** - Validates range constraints (0.0-2.0)
- ✓ **context_window_valid** - Accepts valid enumerated values
- ✓ **context_window_invalid** - Rejects values not in allowed set

### Boolean Switch Handling (2 tests)
- ✓ **boolean_switches** - Multiple switches work together (--verbose, --stream, --dry-run)
- ✓ **enable_disable_cache** - Parses disable-* switches correctly

### Complex Scenarios (1 test)
- ✓ **multiple_options** - Multiple options of different types work together

## Running Tests

### Quick Start
```bash
# Configure with examples enabled
meson setup build -Dbuild_demo=true

# Run all tests
meson test -C build

# Results summary
Ok:                17
Fail:              0
```

### Detailed Output
```bash
# Verbose output showing each test
meson test -C build --verbose

# List all available tests
meson test -C build --list

# Run specific test
meson test -C build claude_impl_valid_model

# Run only integration suite
meson test -C build --suite integration
```

### CI Integration

Tests run automatically in CI on:
- Ubuntu 24.04 with GCC 13, 14 and Clang 16, 17, 18
- macOS 13, 14 with Apple Clang

See `.github/workflows/ci.yml` for details.

## Test Implementation

Tests are implemented as bash scripts that:
1. Execute `claude-impl` with various arguments
2. Capture stdout/stderr output
3. Verify expected behavior using pattern matching
4. Provide color-coded output (✓ pass, ✗ fail, → info)

### Test Script
- Location: `tests/test_claude_impl.sh`
- Language: Bash
- Timeout: 30 seconds per test
- Exit codes: 0 = pass, 1 = fail

### Test Registration
Tests are registered in `examples/meson.build`:
```meson
test(
  'claude_impl_<test_name>',
  test_script,
  args: [claude_impl_exe.full_path(), test_case],
  suite: 'integration',
  timeout: 30,
)
```

## Features Validated

The test suite validates:
- ✓ **Argument parsing** - Keys, values, switches
- ✓ **Type conversion** - String, numeric, boolean
- ✓ **Validation** - Custom checker class logic
- ✓ **Error handling** - Invalid inputs rejected gracefully
- ✓ **Help system** - General and topic-specific help
- ✓ **Default values** - Fallbacks when arguments omitted
- ✓ **Range checking** - Numeric bounds validation
- ✓ **Enum validation** - Allowed value lists
- ✓ **Multiple options** - Complex argument combinations

## Adding New Tests

1. **Add test function** to `tests/test_claude_impl.sh`:
```bash
test_my_feature() {
    info "Testing: my new feature"
    output=$("$CLAUDE_IMPL" --my-flag 2>&1 || true)
    if echo "$output" | grep -q "expected text"; then
        pass "Test passed"
    else
        fail "Test failed"
    fi
}
```

2. **Register test case** in `examples/meson.build`:
```meson
test_cases = [
  'no_args',
  'help',
  # ... existing tests ...
  'my_feature',  # Add here
]
```

3. **Add case handler** in test script:
```bash
case "$TEST_NAME" in
    # ... existing cases ...
    my_feature)
        test_my_feature
        ;;
esac
```

4. **Run new test**:
```bash
meson test -C build claude_impl_my_feature
```

## Test Maintenance

- Keep tests focused on single functionality
- Use descriptive test names
- Include both positive and negative test cases
- Update tests when adding new features
- Maintain 100% pass rate for releases

## Beta Readiness

**Test Coverage: ✓ Excellent**

- 17 integration tests covering all major features
- Validates core library functionality through real usage
- Tests error handling and edge cases
- CI runs tests on multiple platforms and compilers

The test suite provides sufficient coverage for a beta release.
