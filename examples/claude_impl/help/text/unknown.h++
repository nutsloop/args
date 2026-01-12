#pragma once

namespace nutsloop::claude_impl::chelp {

// MARK (CLAUDE_HELP) UNKNOWN OPTION constexpr variables.
static constexpr auto UNKNOWN_NAME_ = "--UNKNOWN OPTION\n\n";
static constexpr auto UNKNOWN_ =
    "ERROR\n"
    "  The specified help topic was not found.\n"
    "\n"
    "SUGGESTION\n"
    "  Run `--help` without arguments to see all available options.\n"
    "  Available help topics include:\n"
    "    model, temperature, max-tokens, top-p, top-k, context-window,\n"
    "    stream, output-format, output-dir, api-key, endpoint, timeout,\n"
    "    retry-count, verbose, dry-run, disable-safety, enable-cache,\n"
    "    disable-cache, config-file, input-file, log-file, log-level,\n"
    "    system-prompt, version, help\n";

} // namespace nutsloop::claude_impl::chelp
