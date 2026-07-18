#include "idp/quality/status.hpp"

namespace idp::quality {

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

} // namespace idp::quality