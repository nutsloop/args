#pragma once

namespace nutsloop::claude_impl::chelp {

// MARK (CLAUDE_HELP) DISABLE_SAFETY OPTION constexpr variables.
static constexpr auto DISABLE_SAFETY_NAME_ = "--DISABLE-SAFETY OPTION\n\n";
static constexpr auto DISABLE_SAFETY_ =
    "SYNOPSIS\n"
    "  --disable-safety\n"
    "\n"
    "DESCRIPTION\n"
    "  Disable client-side safety validation checks.\n"
    "\n"
    "WARNING\n"
    "  This flag disables local safety checks only. The API server\n"
    "  still enforces its own safety policies. Use with caution.\n"
    "\n"
    "AFFECTED CHECKS\n"
    "  - Input length validation\n"
    "  - Content pre-screening\n"
    "  - Rate limit warnings\n"
    "\n"
    "DEFAULT\n"
    "  Safety checks enabled (this flag is off by default)\n"
    "\n"
    "NOTE\n"
    "  This is a boolean switch. Use --disable-safety to disable.\n"
    "\n"
    "EXAMPLE\n"
    "  claude-impl --disable-safety --max-tokens=200000\n";

} // namespace nutsloop::claude_impl::chelp
