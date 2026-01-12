#pragma once

namespace nutsloop::claude_impl::chelp {

// MARK (CLAUDE_HELP) DRY_RUN OPTION constexpr variables.
static constexpr auto DRY_RUN_NAME_ = "--DRY-RUN OPTION\n\n";
static constexpr auto DRY_RUN_ =
    "SYNOPSIS\n"
    "  --dry-run\n"
    "\n"
    "DESCRIPTION\n"
    "  Simulate the API call without actually making a request.\n"
    "  Useful for validating configuration and estimating costs.\n"
    "\n"
    "OUTPUT\n"
    "  - Validated configuration settings\n"
    "  - Estimated token count for input\n"
    "  - Calculated request parameters\n"
    "  - Estimated API cost (if known)\n"
    "\n"
    "USE CASES\n"
    "  - Validating command line arguments\n"
    "  - Testing configuration before committing\n"
    "  - Debugging without incurring API costs\n"
    "  - CI/CD pipeline validation\n"
    "\n"
    "DEFAULT\n"
    "  Disabled (actual API calls made)\n"
    "\n"
    "NOTE\n"
    "  This is a boolean switch. Use --dry-run to enable.\n"
    "\n"
    "EXAMPLE\n"
    "  claude-impl --dry-run --model=claude-opus-4-5-20251101 --max-tokens=8192\n";

} // namespace nutsloop::claude_impl::chelp
