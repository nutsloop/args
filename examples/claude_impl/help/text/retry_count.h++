#pragma once

namespace nutsloop::claude_impl::chelp {

// MARK (CLAUDE_HELP) RETRY_COUNT OPTION constexpr variables.
static constexpr auto RETRY_COUNT_NAME_ = "--RETRY-COUNT=<NUMBER> OPTION\n\n";
static constexpr auto RETRY_COUNT_ =
    "SYNOPSIS\n"
    "  --retry-count=<number>\n"
    "\n"
    "DESCRIPTION\n"
    "  Number of times to retry a failed API request before giving up.\n"
    "  Retries use exponential backoff to avoid overwhelming the API.\n"
    "\n"
    "VALID RANGE\n"
    "  0 to 10\n"
    "\n"
    "DEFAULT\n"
    "  3 retries\n"
    "\n"
    "RETRY BEHAVIOR\n"
    "  - Retries are attempted for transient errors (5xx, timeouts)\n"
    "  - Non-retryable errors (4xx, auth failures) fail immediately\n"
    "  - Backoff: 1s, 2s, 4s, 8s, ... (exponential)\n"
    "  - Set to 0 to disable retries\n"
    "\n"
    "EXAMPLES\n"
    "  claude-impl --retry-count=0    # No retries, fail fast\n"
    "  claude-impl --retry-count=5    # More resilient to transient errors\n";

} // namespace nutsloop::claude_impl::chelp
