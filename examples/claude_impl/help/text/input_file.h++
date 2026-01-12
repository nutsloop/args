#pragma once

namespace nutsloop::claude_impl::chelp {

// MARK (CLAUDE_HELP) INPUT_FILE OPTION constexpr variables.
static constexpr auto INPUT_FILE_NAME_ = "--INPUT-FILE=<PATH> OPTION\n\n";
static constexpr auto INPUT_FILE_ =
    "SYNOPSIS\n"
    "  --input-file=<file-path>\n"
    "\n"
    "DESCRIPTION\n"
    "  Read the prompt or input content from a file instead of\n"
    "  providing it directly via command line.\n"
    "\n"
    "FILE REQUIREMENTS\n"
    "  - File must exist\n"
    "  - File must be readable\n"
    "  - Must be a regular file\n"
    "\n"
    "CONTENT HANDLING\n"
    "  - The entire file content is used as the user message\n"
    "  - Binary files are not supported\n"
    "  - Large files may hit context window limits\n"
    "\n"
    "USE CASES\n"
    "  - Processing long prompts\n"
    "  - Batch processing files\n"
    "  - Analyzing code files\n"
    "  - Summarizing documents\n"
    "\n"
    "EXAMPLES\n"
    "  claude-impl --input-file=./prompt.txt\n"
    "  claude-impl --input-file=./code.py --system-prompt=\"Review this code\"\n";

} // namespace nutsloop::claude_impl::chelp
