# Test Suite

Integration tests for the nutsloop/args library using the `claude-impl` example.

## Test Coverage

The test suite verifies core argument parsing functionality:

### Basic Functionality
- **no_args** - Behavior when no arguments provided
- **help** - General help display
- **help_topic** - Topic-specific help (e.g., `--help=model`)

### String Arguments
- **valid_model** - Valid model name acceptance
- **invalid_model** - Invalid model name rejection
- **output_format** - Valid output format
- **output_format_invalid** - Invalid output format rejection
- **log_level** - Log level validation

### Numeric Arguments
- **max_tokens** - Valid numeric value parsing
- **max_tokens_invalid** - Out-of-range value rejection
- **temperature** - Decimal number parsing (treated as string in skip_digit_check)
- **temperature_out_of_range** - Range validation
- **context_window_valid** - Valid enumerated value
- **context_window_invalid** - Invalid enumerated value rejection

### Boolean Switches
- **boolean_switches** - Multiple switches (`--verbose`, `--stream`, `--dry-run`)
- **enable_disable_cache** - Enable/disable switch handling

### Complex Scenarios
- **multiple_options** - Multiple arguments working together

## Running Tests

### All tests
```bash
meson setup build -Dbuild_demo=true
meson test -C build
```

### Specific test suite
```bash
meson test -C build --suite integration
```

### Individual test
```bash
meson test -C build claude_impl_valid_model
```

### Verbose output
```bash
meson test -C build --verbose
```

### List available tests
```bash
meson test -C build --list
```

## Test Output

Tests use color-coded output:
- ✓ Green checkmark - Test passed
- ✗ Red cross - Test failed
- → Yellow arrow - Test info

## Adding New Tests

1. Add test function to `test_claude_impl.sh`
2. Add test case to `test_cases` array in `examples/meson.build`
3. Run `meson test -C build` to verify

## Test Statistics

- **Total Tests**: 17
- **Suite**: integration
- **Timeout**: 30 seconds per test
- **Coverage**: Argument parsing, validation, help system, error handling
