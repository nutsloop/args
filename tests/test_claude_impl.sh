#!/usr/bin/env bash
# Test script for claude-impl example
# Tests various command-line argument parsing scenarios

set -e  # Exit on error

CLAUDE_IMPL="$1"
TEST_NAME="$2"

if [ -z "$CLAUDE_IMPL" ] || [ -z "$TEST_NAME" ]; then
    echo "Usage: $0 <path-to-claude-impl> <test-name>"
    exit 1
fi

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

pass() {
    echo -e "${GREEN}✓${NC} $1"
}

fail() {
    echo -e "${RED}✗${NC} $1"
    exit 1
}

info() {
    echo -e "${YELLOW}→${NC} $1"
}

# ─────────────────────────────────────────────────────────────────────────────
# Test Cases
# ─────────────────────────────────────────────────────────────────────────────

test_no_args() {
    info "Testing: no arguments (should show version info)"
    output=$("$CLAUDE_IMPL" 2>&1 || true)
    if echo "$output" | grep -q "claude-impl - AI Model Configuration CLI"; then
        pass "Shows version banner"
    else
        fail "Should show version banner"
    fi
}

test_help() {
    info "Testing: --help (should show help text)"
    output=$("$CLAUDE_IMPL" --help 2>&1 || true)
    if echo "$output" | grep -q "AVAILABLE OPTIONS"; then
        pass "Help text displayed"
    else
        fail "Help text not displayed"
    fi
}

test_help_topic() {
    info "Testing: --help=model (should show model-specific help)"
    output=$("$CLAUDE_IMPL" --help=model 2>&1 || true)
    if echo "$output" | grep -q "model" || echo "$output" | grep -q "MODEL"; then
        pass "Model help displayed"
    else
        fail "Model help not displayed"
    fi
}

test_valid_model() {
    info "Testing: valid model with dry-run"
    output=$("$CLAUDE_IMPL" --model=claude-opus-4-5-20251101 --dry-run 2>&1 || true)
    if echo "$output" | grep -q "claude-opus-4-5-20251101"; then
        pass "Valid model accepted"
    else
        fail "Valid model should be accepted"
    fi
}

test_invalid_model() {
    info "Testing: invalid model (should fail)"
    output=$("$CLAUDE_IMPL" --model=invalid-model-name 2>&1 || true)
    if echo "$output" | grep -q "error" || echo "$output" | grep -q "invalid" || echo "$output" | grep -q "not a valid model"; then
        pass "Invalid model rejected"
    else
        fail "Invalid model should be rejected"
    fi
}

test_max_tokens() {
    info "Testing: --max-tokens with valid value"
    output=$("$CLAUDE_IMPL" --max-tokens=8192 --dry-run 2>&1 || true)
    if echo "$output" | grep -q "8192"; then
        pass "Max tokens accepted"
    else
        fail "Max tokens should be accepted"
    fi
}

test_max_tokens_invalid() {
    info "Testing: --max-tokens with invalid value (should fail)"
    output=$("$CLAUDE_IMPL" --max-tokens=999999999 2>&1 || true)
    if echo "$output" | grep -q "error" || echo "$output" | grep -q "exceeds"; then
        pass "Invalid max-tokens rejected"
    else
        fail "Invalid max-tokens should be rejected"
    fi
}

test_temperature() {
    info "Testing: --temperature with valid decimal"
    output=$("$CLAUDE_IMPL" --temperature=0.7 --dry-run 2>&1 || true)
    if echo "$output" | grep -q "0.7"; then
        pass "Temperature accepted"
    else
        fail "Temperature should be accepted"
    fi
}

test_temperature_out_of_range() {
    info "Testing: --temperature out of range (should fail)"
    output=$("$CLAUDE_IMPL" --temperature=3.0 2>&1 || true)
    if echo "$output" | grep -q "error" || echo "$output" | grep -q "out of range"; then
        pass "Out-of-range temperature rejected"
    else
        fail "Out-of-range temperature should be rejected"
    fi
}

test_boolean_switches() {
    info "Testing: boolean switches (--verbose --stream --dry-run)"
    output=$("$CLAUDE_IMPL" --verbose --stream --dry-run 2>&1 || true)
    if echo "$output" | grep -q "Verbose:.*yes" && echo "$output" | grep -q "Stream.*enabled" && echo "$output" | grep -q "Dry Run:.*yes"; then
        pass "Boolean switches work correctly"
    else
        fail "Boolean switches not working"
    fi
}

test_enable_disable_cache() {
    info "Testing: --disable-cache flag parsing"
    output=$("$CLAUDE_IMPL" --disable-cache --dry-run 2>&1 || true)
    # The disable-cache flag should be parsed without error
    if echo "$output" | grep -q "Configuration loaded successfully" || echo "$output" | grep -q "DRY RUN MODE"; then
        pass "Disable-cache flag parsed successfully"
    else
        fail "Disable-cache flag should be parsed"
    fi
}

test_output_format() {
    info "Testing: --output-format with valid value"
    output=$("$CLAUDE_IMPL" --output-format=json --dry-run 2>&1 || true)
    if echo "$output" | grep -q "json"; then
        pass "Output format accepted"
    else
        fail "Output format should be accepted"
    fi
}

test_output_format_invalid() {
    info "Testing: --output-format with invalid value (should fail)"
    output=$("$CLAUDE_IMPL" --output-format=invalid 2>&1 || true)
    if echo "$output" | grep -q "error" || echo "$output" | grep -q "invalid"; then
        pass "Invalid output format rejected"
    else
        fail "Invalid output format should be rejected"
    fi
}

test_log_level() {
    info "Testing: --log-level with valid value"
    output=$("$CLAUDE_IMPL" --log-level=debug --dry-run 2>&1 || true)
    if echo "$output" | grep -q "debug"; then
        pass "Log level accepted"
    else
        fail "Log level should be accepted"
    fi
}

test_multiple_options() {
    info "Testing: multiple options combined"
    output=$("$CLAUDE_IMPL" \
        --model=claude-sonnet-4-20250514 \
        --max-tokens=4096 \
        --temperature=0.8 \
        --top-k=50 \
        --stream \
        --verbose \
        --dry-run \
        2>&1 || true)

    if echo "$output" | grep -q "claude-sonnet-4-20250514" && \
       echo "$output" | grep -q "4096" && \
       echo "$output" | grep -q "0.8"; then
        pass "Multiple options work together"
    else
        fail "Multiple options should work together"
    fi
}

test_context_window_valid() {
    info "Testing: --context-window with valid value"
    output=$("$CLAUDE_IMPL" --context-window=200000 --dry-run 2>&1 || true)
    if echo "$output" | grep -q "200000"; then
        pass "Context window accepted"
    else
        fail "Context window should be accepted"
    fi
}

test_context_window_invalid() {
    info "Testing: --context-window with invalid value (should fail)"
    output=$("$CLAUDE_IMPL" --context-window=12345 2>&1 || true)
    if echo "$output" | grep -q "error" || echo "$output" | grep -q "not a valid size"; then
        pass "Invalid context window rejected"
    else
        fail "Invalid context window should be rejected"
    fi
}

# ─────────────────────────────────────────────────────────────────────────────
# Run the specified test
# ─────────────────────────────────────────────────────────────────────────────

case "$TEST_NAME" in
    no_args)
        test_no_args
        ;;
    help)
        test_help
        ;;
    help_topic)
        test_help_topic
        ;;
    valid_model)
        test_valid_model
        ;;
    invalid_model)
        test_invalid_model
        ;;
    max_tokens)
        test_max_tokens
        ;;
    max_tokens_invalid)
        test_max_tokens_invalid
        ;;
    temperature)
        test_temperature
        ;;
    temperature_out_of_range)
        test_temperature_out_of_range
        ;;
    boolean_switches)
        test_boolean_switches
        ;;
    enable_disable_cache)
        test_enable_disable_cache
        ;;
    output_format)
        test_output_format
        ;;
    output_format_invalid)
        test_output_format_invalid
        ;;
    log_level)
        test_log_level
        ;;
    multiple_options)
        test_multiple_options
        ;;
    context_window_valid)
        test_context_window_valid
        ;;
    context_window_invalid)
        test_context_window_invalid
        ;;
    *)
        echo "Unknown test: $TEST_NAME"
        exit 1
        ;;
esac

exit 0
