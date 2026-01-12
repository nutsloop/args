#pragma once

namespace nutsloop::claude_impl::chelp {

// MARK (CLAUDE_HELP) API_KEY OPTION constexpr variables.
static constexpr auto API_KEY_NAME_ = "--API-KEY=<STRING> OPTION\n\n";
static constexpr auto API_KEY_ =
    "SYNOPSIS\n"
    "  --api-key=<key>\n"
    "\n"
    "DESCRIPTION\n"
    "  Your Anthropic API key for authentication.\n"
    "  Required for making API calls to Claude models.\n"
    "\n"
    "KEY FORMAT\n"
    "  API keys must start with 'sk-ant-' prefix.\n"
    "  Example: sk-ant-api03-xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n"
    "\n"
    "OBTAINING AN API KEY\n"
    "  1. Visit https://console.anthropic.com\n"
    "  2. Sign in or create an account\n"
    "  3. Navigate to API Keys section\n"
    "  4. Create a new API key\n"
    "\n"
    "ALTERNATIVE (ENVIRONMENT VARIABLE)\n"
    "  Instead of passing via command line, you can set:\n"
    "    export ANTHROPIC_API_KEY=sk-ant-...\n"
    "  The CLI will automatically use this if --api-key is not provided.\n"
    "\n"
    "SECURITY NOTE\n"
    "  Avoid passing API keys directly on the command line in shared\n"
    "  environments as they may be visible in process listings.\n"
    "  Prefer using the environment variable method.\n"
    "\n"
    "EXAMPLE\n"
    "  claude-impl --api-key=sk-ant-api03-xxxxx --model=claude-sonnet-4-20250514\n";

} // namespace nutsloop::claude_impl::chelp
