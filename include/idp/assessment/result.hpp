#pragma once
#include "idp/assessment/status.hpp"
#include <string>

namespace idp::assessment {
struct Result {
  double value;
  Status status;
  std::string message;
};
} // namespace idp::assessment