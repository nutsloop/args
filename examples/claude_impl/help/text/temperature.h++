#pragma once

namespace nutsloop::claude_impl::chelp {

// MARK (CLAUDE_HELP) TEMPERATURE OPTION constexpr variables.
static constexpr auto TEMPERATURE_NAME_ = "--TEMPERATURE=<DECIMAL> OPTION\n\n";
static constexpr auto TEMPERATURE_ =
    "SYNOPSIS\n"
    "  --temperature=<decimal>\n"
    "\n"
    "DESCRIPTION\n"
    "  Controls randomness in the model's output.\n"
    "  - Lower values (0.0-0.5): More focused, deterministic responses\n"
    "  - Medium values (0.5-1.0): Balanced creativity and coherence\n"
    "  - Higher values (1.0-2.0): More creative, varied responses\n"
    "\n"
    "VALID RANGE\n"
    "  0.0 to 2.0 (inclusive)\n"
    "\n"
    "DEFAULT\n"
    "  1.0\n"
    "\n"
    "EXAMPLES\n"
    "  claude-impl --temperature=0.3    # Precise, factual responses\n"
    "  claude-impl --temperature=0.7    # Balanced (recommended)\n"
    "  claude-impl --temperature=1.5    # Creative writing\n";

} // namespace nutsloop::claude_impl::chelp
