#pragma once

namespace nutsloop::claude_impl::chelp {

// MARK (CLAUDE_HELP) SYSTEM_PROMPT OPTION constexpr variables.
static constexpr auto SYSTEM_PROMPT_NAME_ = "--SYSTEM-PROMPT=<STRING> OPTION\n\n";
static constexpr auto SYSTEM_PROMPT_ =
    "SYNOPSIS\n"
    "  --system-prompt=<text>\n"
    "\n"
    "DESCRIPTION\n"
    "  Set the system prompt that defines the AI's behavior,\n"
    "  personality, or context for the conversation.\n"
    "\n"
    "PURPOSE\n"
    "  - Define the assistant's role or expertise\n"
    "  - Set output format requirements\n"
    "  - Provide context about the task\n"
    "  - Establish behavioral guidelines\n"
    "\n"
    "LIMITS\n"
    "  - Maximum recommended length: 10,000 characters\n"
    "  - Counts against the context window\n"
    "\n"
    "BEST PRACTICES\n"
    "  - Be specific about the desired behavior\n"
    "  - Include example formats if needed\n"
    "  - Keep prompts focused and clear\n"
    "\n"
    "DEFAULT\n"
    "  Empty (no system prompt)\n"
    "\n"
    "EXAMPLES\n"
    "  claude-impl --system-prompt=\"You are a helpful coding assistant.\"\n"
    "  claude-impl --system-prompt=\"Respond only in JSON format.\"\n"
    "  claude-impl --system-prompt=\"You are an expert in C++ and Rust.\"\n";

} // namespace nutsloop::claude_impl::chelp
