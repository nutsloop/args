#include "../help.h++"

#include <utility>

namespace nutsloop::claude_impl {

help::help(std::string look_up_option, const args::version_t version)
    : look_up_option_{std::move(look_up_option)}, version_info_{version} {

  set_option_list_();
}

} // namespace nutsloop::claude_impl
