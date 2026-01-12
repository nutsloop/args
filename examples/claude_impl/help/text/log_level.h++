#pragma once

namespace nutsloop::claude_impl::chelp {

// MARK (CLAUDE_HELP) LOG_LEVEL OPTION constexpr variables.
static constexpr auto LOG_LEVEL_NAME_ = "--LOG-LEVEL=<STRING> OPTION\n\n";
static constexpr auto LOG_LEVEL_ =
    "SYNOPSIS\n"
    "  --log-level=<level>\n"
    "\n"
    "DESCRIPTION\n"
    "  Set the minimum log level for output. Messages below this\n"
    "  level are not displayed or written to log files.\n"
    "\n"
    "AVAILABLE LEVELS (increasing verbosity)\n"
    "  none     No logging at all\n"
    "  error    Only error messages\n"
    "  warn     Warnings and errors\n"
    "  info     Information, warnings, and errors (default)\n"
    "  debug    All messages including debug details\n"
    "\n"
    "DEFAULT\n"
    "  info\n"
    "\n"
    "LEVEL DETAILS\n"
    "  debug    API request/response bodies, internal state\n"
    "  info     Request sent, response received, timing\n"
    "  warn     Rate limits approaching, deprecated features\n"
    "  error    Failed requests, validation errors\n"
    "\n"
    "EXAMPLES\n"
    "  claude-impl --log-level=debug --log-file=./debug.log\n"
    "  claude-impl --log-level=error  # Only show errors\n"
    "  claude-impl --log-level=none   # Silent mode\n";

} // namespace nutsloop::claude_impl::chelp
