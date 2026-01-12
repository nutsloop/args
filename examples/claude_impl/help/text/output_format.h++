#pragma once

namespace nutsloop::claude_impl::chelp {

// MARK (CLAUDE_HELP) OUTPUT_FORMAT OPTION constexpr variables.
static constexpr auto OUTPUT_FORMAT_NAME_ = "--OUTPUT-FORMAT=<STRING> OPTION\n\n";
static constexpr auto OUTPUT_FORMAT_ =
    "SYNOPSIS\n"
    "  --output-format=<format>\n"
    "\n"
    "DESCRIPTION\n"
    "  Specify the output format for the CLI response.\n"
    "\n"
    "AVAILABLE FORMATS\n"
    "  json       JSON format with metadata (default)\n"
    "             Includes model, tokens used, timing info\n"
    "\n"
    "  text       Plain text, content only\n"
    "             No metadata, just the response\n"
    "\n"
    "  markdown   Markdown-formatted output\n"
    "             Preserves code blocks, headers, lists\n"
    "\n"
    "  xml        XML format with structured tags\n"
    "             Useful for programmatic parsing\n"
    "\n"
    "DEFAULT\n"
    "  json\n"
    "\n"
    "EXAMPLES\n"
    "  claude-impl --output-format=json     # Full response with metadata\n"
    "  claude-impl --output-format=text     # Just the content\n"
    "  claude-impl --output-format=markdown # Formatted for display\n";

} // namespace nutsloop::claude_impl::chelp
