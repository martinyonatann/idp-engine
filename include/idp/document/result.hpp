#pragma once

#include "idp/document/types.hpp"
namespace idp::document {
struct Result {
  bool found = false;
  Contour polygon;
};
} // namespace idp::document