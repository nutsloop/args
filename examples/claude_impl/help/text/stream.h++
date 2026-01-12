#pragma once

namespace nutsloop::claude_impl::chelp {

// MARK (CLAUDE_HELP) STREAM OPTION constexpr variables.
static constexpr auto STREAM_NAME_ = "--STREAM OPTION\n\n";
static constexpr auto STREAM_ =
    "SYNOPSIS\n"
    "  --stream\n"
    "\n"
    "DESCRIPTION\n"
    "  Enable streaming mode for responses. When enabled, the model's\n"
    "  response is delivered incrementally as it's generated, rather\n"
    "  than waiting for the complete response.\n"
    "\n"
    "BENEFITS\n"
    "  - Lower perceived latency (first token arrives faster)\n"
    "  - Real-time display of generation progress\n"
    "  - Can cancel generation mid-stream\n"
    "  - Better user experience for long responses\n"
    "\n"
    "DEFAULT\n"
    "  Disabled (non-streaming mode)\n"
    "\n"
    "NOTE\n"
    "  This is a boolean switch. Use --stream to enable.\n"
    "  Do not use --stream=true or --stream=false.\n"
    "\n"
    "EXAMPLE\n"
    "  claude-impl --stream --max-tokens=4096\n";

} // namespace nutsloop::claude_impl::chelp
