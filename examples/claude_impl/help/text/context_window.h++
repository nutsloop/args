#pragma once

namespace nutsloop::claude_impl::chelp {

// MARK (CLAUDE_HELP) CONTEXT_WINDOW OPTION constexpr variables.
static constexpr auto CONTEXT_WINDOW_NAME_ = "--CONTEXT-WINDOW=<NUMBER> OPTION\n\n";
static constexpr auto CONTEXT_WINDOW_ =
    "SYNOPSIS\n"
    "  --context-window=<size>\n"
    "\n"
    "DESCRIPTION\n"
    "  Sets the context window size (in tokens) for the conversation.\n"
    "  This determines how much previous context the model can consider.\n"
    "\n"
    "VALID SIZES\n"
    "  8192     8K context  - Basic conversations\n"
    "  16384    16K context - Standard use\n"
    "  32768    32K context - Extended conversations\n"
    "  65536    64K context - Long documents\n"
    "  100000   100K context - Large codebases\n"
    "  200000   200K context - Maximum (full model capacity)\n"
    "\n"
    "DEFAULT\n"
    "  200000\n"
    "\n"
    "NOTE\n"
    "  Larger context windows may increase latency and cost.\n"
    "  Choose the smallest size that fits your use case.\n"
    "\n"
    "EXAMPLE\n"
    "  claude-impl --context-window=32768 --input-file=document.txt\n";

} // namespace nutsloop::claude_impl::chelp
