#pragma once
#include "idp/quality/status.hpp"
#include <string>

namespace idp::quality {
struct Result {
  double value;
  Status status;
  std::string message;
};
} // namespace idp::quality