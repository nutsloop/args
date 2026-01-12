#pragma once

namespace nutsloop::claude_impl::chelp {

// MARK (CLAUDE_HELP) MODEL OPTION constexpr variables.
static constexpr auto MODEL_NAME_ = "--MODEL=<STRING> OPTION\n\n";
static constexpr auto MODEL_ =
    "SYNOPSIS\n"
    "  --model=<model-name>\n"
    "\n"
    "DESCRIPTION\n"
    "  Specify which Claude model to use for generation.\n"
    "\n"
    "AVAILABLE MODELS\n"
    "  claude-opus-4-5-20251101      Latest flagship model, best for complex tasks\n"
    "  claude-sonnet-4-20250514      Balanced performance and speed\n"
    "  claude-3-5-haiku-20241022     Fast, lightweight model\n"
    "  claude-3-opus-20240229        Previous generation flagship\n"
    "  claude-3-sonnet-20240229      Previous generation balanced\n"
    "  claude-3-haiku-20240307       Previous generation fast\n"
    "\n"
    "DEFAULT\n"
    "  claude-opus-4-5-20251101\n"
    "\n"
    "EXAMPLE\n"
    "  claude-impl --model=claude-sonnet-4-20250514 --max-tokens=1000\n";

} // namespace nutsloop::claude_impl::chelp
