#pragma once
#include <string>

namespace idp::quality {
enum class Status {
  Pass,
  Warning,
  Fail,
};

std::string ToString(Status status);

} // namespace idp::quality