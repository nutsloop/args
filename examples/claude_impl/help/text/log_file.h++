#pragma once

namespace nutsloop::claude_impl::chelp {

// MARK (CLAUDE_HELP) LOG_FILE OPTION constexpr variables.
static constexpr auto LOG_FILE_NAME_ = "--LOG-FILE=<PATH> OPTION\n\n";
static constexpr auto LOG_FILE_ =
    "SYNOPSIS\n"
    "  --log-file=<file-path>\n"
    "\n"
    "DESCRIPTION\n"
    "  Write log output to the specified file.\n"
    "  Use with --log-level to control verbosity.\n"
    "\n"
    "PATH HANDLING\n"
    "  - Relative paths resolved from current working directory\n"
    "  - Parent directory must exist\n"
    "  - File is created if it doesn't exist\n"
    "  - Existing file is appended to (not overwritten)\n"
    "\n"
    "LOG FORMAT\n"
    "  [TIMESTAMP] [LEVEL] Message\n"
    "  Example: [2025-01-10 14:30:45] [INFO] API request sent\n"
    "\n"
    "DEFAULT\n"
    "  No log file (logs to stderr only if --verbose is set)\n"
    "\n"
    "EXAMPLES\n"
    "  claude-impl --log-file=./claude.log --log-level=debug\n"
    "  claude-impl --log-file=/var/log/claude-impl.log\n";

} // namespace nutsloop::claude_impl::chelp
