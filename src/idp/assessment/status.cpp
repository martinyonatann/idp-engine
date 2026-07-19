#include "idp/assessment/status.hpp"

namespace idp::assessment {

std::string ToString(Status status) {
  switch (status) {
  case Status::Pass:
    return "PASS";

  case Status::Warning:
    return "WARNING";

  case Status::Fail:
    return "FAIL";
  }

  return "UNKNOWN";
}

} // namespace idp::assessment