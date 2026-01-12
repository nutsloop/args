#include "../help.h++"
#include "../help/text/dry_run.h++"

namespace nutsloop::claude_impl {

std::string help::dry_run_() const { return std::string(DRY_RUN_NAME_) + DRY_RUN_; }

} // namespace nutsloop::claude_impl
