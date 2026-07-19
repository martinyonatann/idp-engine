#pragma once
#include "idp/document/types.hpp"

namespace idp::document {
class PolygonApproximator {
public:
  Contour Approximate(const Contour &contour,
                      double epsilonFactor = 0.02) const;
};
} // namespace idp::document