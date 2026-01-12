#pragma once

namespace nutsloop::claude_impl::chelp {

// MARK (CLAUDE_HELP) CONFIG_FILE OPTION constexpr variables.
static constexpr auto CONFIG_FILE_NAME_ = "--CONFIG-FILE=<PATH> OPTION\n\n";
static constexpr auto CONFIG_FILE_ =
    "SYNOPSIS\n"
    "  --config-file=<file-path>\n"
    "\n"
    "DESCRIPTION\n"
    "  Load configuration from a file. Supports JSON, YAML, and TOML formats.\n"
    "  Command line arguments override values from the config file.\n"
    "\n"
    "SUPPORTED FORMATS\n"
    "  .json    JSON format\n"
    "  .yaml    YAML format\n"
    "  .yml     YAML format (alternate extension)\n"
    "  .toml    TOML format\n"
    "\n"
    "FILE REQUIREMENTS\n"
    "  - File must exist and be readable\n"
    "  - Must have a valid extension (.json, .yaml, .yml, .toml)\n"
    "  - Must be a regular file (not a directory)\n"
    "\n"
    "EXAMPLE CONFIG (JSON)\n"
    "  {\n"
    "    \"model\": \"claude-opus-4-5-20251101\",\n"
    "    \"max_tokens\": 4096,\n"
    "    \"temperature\": \"0.7\",\n"
    "    \"stream\": true\n"
    "  }\n"
    "\n"
    "EXAMPLE\n"
    "  claude-impl --config-file=./config.json --verbose\n";

} // namespace nutsloop::claude_impl::chelp
