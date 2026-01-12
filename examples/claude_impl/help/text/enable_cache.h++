#pragma once

namespace nutsloop::claude_impl::chelp {

// MARK (CLAUDE_HELP) ENABLE_CACHE OPTION constexpr variables.
static constexpr auto ENABLE_CACHE_NAME_ = "--ENABLE-CACHE OPTION\n\n";
static constexpr auto ENABLE_CACHE_ =
    "SYNOPSIS\n"
    "  --enable-cache\n"
    "\n"
    "DESCRIPTION\n"
    "  Enable response caching. When enabled, identical requests\n"
    "  may return cached responses instead of making new API calls.\n"
    "\n"
    "BENEFITS\n"
    "  - Reduced API costs for repeated requests\n"
    "  - Faster response times for cached content\n"
    "  - Consistent responses for identical inputs\n"
    "\n"
    "CACHE BEHAVIOR\n"
    "  - Cache key includes: model, prompt, temperature, max_tokens\n"
    "  - Cache is stored locally\n"
    "  - Cache entries expire based on TTL settings\n"
    "\n"
    "DEFAULT\n"
    "  Enabled\n"
    "\n"
    "NOTE\n"
    "  Use --disable-cache to override and force fresh API calls.\n"
    "\n"
    "EXAMPLE\n"
    "  claude-impl --enable-cache --model=claude-sonnet-4-20250514\n";

} // namespace nutsloop::claude_impl::chelp
