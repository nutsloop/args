#pragma once

namespace nutsloop::claude_impl::chelp {

// MARK (CLAUDE_HELP) OUTPUT_DIR OPTION constexpr variables.
static constexpr auto OUTPUT_DIR_NAME_ = "--OUTPUT-DIR=<PATH> OPTION\n\n";
static constexpr auto OUTPUT_DIR_ =
    "SYNOPSIS\n"
    "  --output-dir=<directory-path>\n"
    "\n"
    "DESCRIPTION\n"
    "  Specify the directory where output files will be saved.\n"
    "  The directory must exist and be writable.\n"
    "\n"
    "PATH HANDLING\n"
    "  - Relative paths are resolved from the current working directory\n"
    "  - Absolute paths are used as-is\n"
    "  - The path must be an existing directory\n"
    "\n"
    "DEFAULT\n"
    "  Current working directory (.)\n"
    "\n"
    "EXAMPLES\n"
    "  claude-impl --output-dir=./results\n"
    "  claude-impl --output-dir=/tmp/claude-output\n"
    "  claude-impl --output-dir=~/Documents/claude\n";

} // namespace nutsloop::claude_impl::chelp
