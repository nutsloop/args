#pragma once

namespace nutsloop::claude_impl::chelp {

// MARK (CLAUDE_HELP) DISABLE_CACHE OPTION constexpr variables.
static constexpr auto DISABLE_CACHE_NAME_ = "--DISABLE-CACHE OPTION\n\n";
static constexpr auto DISABLE_CACHE_ =
    "SYNOPSIS\n"
    "  --disable-cache\n"
    "\n"
    "DESCRIPTION\n"
    "  Disable response caching. Every request will make a fresh\n"
    "  API call, ignoring any cached responses.\n"
    "\n"
    "USE CASES\n"
    "  - When you need guaranteed fresh responses\n"
    "  - Testing model updates or behavior changes\n"
    "  - Debugging caching issues\n"
    "  - When randomness (temperature > 0) is important\n"
    "\n"
    "DEFAULT\n"
    "  Caching is enabled by default\n"
    "\n"
    "NOTE\n"
    "  This is a boolean switch. Use --disable-cache to disable caching.\n"
    "\n"
    "EXAMPLE\n"
    "  claude-impl --disable-cache --temperature=1.5\n";

} // namespace nutsloop::claude_impl::chelp
