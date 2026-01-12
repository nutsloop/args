#pragma once

namespace nutsloop::claude_impl::chelp {

// MARK (CLAUDE_HELP) TIMEOUT OPTION constexpr variables.
static constexpr auto TIMEOUT_NAME_ = "--TIMEOUT=<SECONDS> OPTION\n\n";
static constexpr auto TIMEOUT_ =
    "SYNOPSIS\n"
    "  --timeout=<seconds>\n"
    "\n"
    "DESCRIPTION\n"
    "  Maximum time (in seconds) to wait for an API response.\n"
    "  If exceeded, the request is cancelled and an error is returned.\n"
    "\n"
    "VALID RANGE\n"
    "  1 to 3600 seconds (1 hour maximum)\n"
    "\n"
    "DEFAULT\n"
    "  120 seconds (2 minutes)\n"
    "\n"
    "RECOMMENDATIONS\n"
    "  Short responses (< 1000 tokens):  30-60 seconds\n"
    "  Medium responses (1000-4000):     60-120 seconds\n"
    "  Long responses (> 4000 tokens):   120-300 seconds\n"
    "  Very long with opus models:       300-600 seconds\n"
    "\n"
    "NOTE\n"
    "  Streaming mode may require longer timeouts for the initial\n"
    "  connection, but provides faster perceived response times.\n"
    "\n"
    "EXAMPLE\n"
    "  claude-impl --timeout=300 --max-tokens=16384\n";

} // namespace nutsloop::claude_impl::chelp
