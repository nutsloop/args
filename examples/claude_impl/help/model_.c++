#include "../help.h++"
#include "../help/text/model.h++"

namespace nutsloop::claude_impl {

std::string help::model_() const { return std::string(MODEL_NAME_) + MODEL_; }

} // namespace nutsloop::claude_impl
