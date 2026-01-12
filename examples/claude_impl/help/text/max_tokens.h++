#pragma once

namespace nutsloop::claude_impl::chelp {

// MARK (CLAUDE_HELP) MAX_TOKENS OPTION constexpr variables.
static constexpr auto MAX_TOKENS_NAME_ = "--MAX-TOKENS=<NUMBER> OPTION\n\n";
static constexpr auto MAX_TOKENS_ =
    "SYNOPSIS\n"
    "  --max-tokens=<number>\n"
    "\n"
    "DESCRIPTION\n"
    "  Maximum number of tokens the model can generate in its response.\n"
    "  One token is approximately 4 characters or 0.75 words in English.\n"
    "\n"
    "VALID RANGE\n"
    "  1 to 200000\n"
    "\n"
    "COMMON VALUES\n"
    "  256     Short responses, quick answers\n"
    "  1024    Standard responses\n"
    "  4096    Detailed explanations (default)\n"
    "  8192    Long-form content\n"
    "  16384   Extended analysis\n"
    "  200000  Maximum (full context utilization)\n"
    "\n"
    "DEFAULT\n"
    "  4096\n"
    "\n"
    "NOTE\n"
    "  Higher values increase response time and cost.\n"
    "  The actual response may be shorter if the model completes naturally.\n"
    "\n"
    "EXAMPLE\n"
    "  claude-impl --max-tokens=8192 --model=claude-opus-4-5-20251101\n";

} // namespace nutsloop::claude_impl::chelp
