#pragma once

namespace nutsloop::claude_impl::chelp {

// MARK (CLAUDE_HELP) ENDPOINT OPTION constexpr variables.
static constexpr auto ENDPOINT_NAME_ = "--ENDPOINT=<URL> OPTION\n\n";
static constexpr auto ENDPOINT_ =
    "SYNOPSIS\n"
    "  --endpoint=<url>\n"
    "\n"
    "DESCRIPTION\n"
    "  Override the default Anthropic API endpoint URL.\n"
    "  Useful for proxies, testing, or alternative deployments.\n"
    "\n"
    "URL FORMAT\n"
    "  Must be a valid URL starting with http:// or https://\n"
    "\n"
    "DEFAULT\n"
    "  https://api.anthropic.com/v1/messages\n"
    "\n"
    "USE CASES\n"
    "  - Using a proxy server for API calls\n"
    "  - Testing with a mock server\n"
    "  - Routing through corporate gateways\n"
    "  - Using region-specific endpoints\n"
    "\n"
    "EXAMPLES\n"
    "  claude-impl --endpoint=https://proxy.company.com/anthropic\n"
    "  claude-impl --endpoint=http://localhost:8080/mock-api\n";

} // namespace nutsloop::claude_impl::chelp
