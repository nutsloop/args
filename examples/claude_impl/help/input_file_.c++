#include "../help.h++"
#include "../help/text/input_file.h++"

namespace nutsloop::claude_impl {

std::string help::input_file_() const { return std::string(INPUT_FILE_NAME_) + INPUT_FILE_; }

} // namespace nutsloop::claude_impl
