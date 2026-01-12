#pragma once

namespace nutsloop::claude_impl::chelp {

// MARK (CLAUDE_HELP) TOP_K OPTION constexpr variables.
static constexpr auto TOP_K_NAME_ = "--TOP-K=<NUMBER> OPTION\n\n";
static constexpr auto TOP_K_ =
    "SYNOPSIS\n"
    "  --top-k=<number>\n"
    "\n"
    "DESCRIPTION\n"
    "  Limits the model to consider only the top K most likely tokens\n"
    "  at each step of generation.\n"
    "  - Lower values: More deterministic, focused output\n"
    "  - Higher values: More diverse possibilities considered\n"
    "\n"
    "VALID RANGE\n"
    "  1 to 500\n"
    "\n"
    "DEFAULT\n"
    "  40\n"
    "\n"
    "COMMON VALUES\n"
    "  10    Very focused, predictable\n"
    "  40    Balanced (default)\n"
    "  100   More varied output\n"
    "  500   Maximum diversity\n"
    "\n"
    "NOTE\n"
    "  Top-k can be combined with top-p for fine-grained control.\n"
    "\n"
    "EXAMPLE\n"
    "  claude-impl --top-k=50 --top-p=0.9\n";

} // namespace nutsloop::claude_impl::chelp
