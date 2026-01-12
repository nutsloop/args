#pragma once

namespace nutsloop::claude_impl::chelp {

// MARK (CLAUDE_HELP) TOP_P OPTION constexpr variables.
static constexpr auto TOP_P_NAME_ = "--TOP-P=<DECIMAL> OPTION\n\n";
static constexpr auto TOP_P_ =
    "SYNOPSIS\n"
    "  --top-p=<decimal>\n"
    "\n"
    "DESCRIPTION\n"
    "  Nucleus sampling parameter. The model considers tokens with\n"
    "  cumulative probability mass up to this threshold.\n"
    "  - Lower values: More focused, predictable output\n"
    "  - Higher values: More diverse, creative output\n"
    "\n"
    "VALID RANGE\n"
    "  0.0 to 1.0 (inclusive)\n"
    "\n"
    "DEFAULT\n"
    "  0.9\n"
    "\n"
    "RECOMMENDATION\n"
    "  Generally, adjust either temperature OR top_p, not both.\n"
    "  Top-p is often preferred for maintaining coherence while\n"
    "  allowing some creativity.\n"
    "\n"
    "EXAMPLES\n"
    "  claude-impl --top-p=0.5    # Conservative, focused output\n"
    "  claude-impl --top-p=0.9    # Balanced (default)\n"
    "  claude-impl --top-p=0.95   # More varied vocabulary\n";

} // namespace nutsloop::claude_impl::chelp
