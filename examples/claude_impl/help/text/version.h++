#pragma once

namespace nutsloop::claude_impl::chelp {

// MARK (CLAUDE_HELP) VERSION OPTION constexpr variables.
static constexpr auto VERSION_NAME_ = "--VERSION OPTION\n\n";
static constexpr auto VERSION_ =
    "SYNOPSIS\n"
    "  --version\n"
    "  --v\n"
    "\n"
    "DESCRIPTION\n"
    "  Display the version number of claude-impl.\n"
    "\n"
    "OUTPUT FORMAT\n"
    "  The version is displayed as: vMAJOR.MINOR.PATCH\n"
    "  Example: v1.0.0\n";

} // namespace nutsloop::claude_impl::chelp
