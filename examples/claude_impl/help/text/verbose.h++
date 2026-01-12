#pragma once

namespace nutsloop::claude_impl::chelp {

// MARK (CLAUDE_HELP) VERBOSE OPTION constexpr variables.
static constexpr auto VERBOSE_NAME_ = "--VERBOSE OPTION\n\n";
static constexpr auto VERBOSE_ =
    "SYNOPSIS\n"
    "  --verbose\n"
    "\n"
    "DESCRIPTION\n"
    "  Enable verbose output mode. Prints additional information\n"
    "  about the request and response processing.\n"
    "\n"
    "OUTPUT INCLUDES\n"
    "  - Request configuration details\n"
    "  - API call timing information\n"
    "  - Token usage breakdown\n"
    "  - Debug messages\n"
    "  - Response metadata\n"
    "\n"
    "DEFAULT\n"
    "  Disabled (quiet mode)\n"
    "\n"
    "NOTE\n"
    "  This is a boolean switch. Use --verbose to enable.\n"
    "  For logging to file, use --log-file and --log-level instead.\n"
    "\n"
    "EXAMPLE\n"
    "  claude-impl --verbose --model=claude-sonnet-4-20250514\n";

} // namespace nutsloop::claude_impl::chelp
