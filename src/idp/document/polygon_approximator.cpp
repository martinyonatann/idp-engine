#include "idp/document/polygon_approximator.hpp"
#include "idp/document/types.hpp"
#include <opencv2/img_hash.hpp>
#include <opencv2/imgproc.hpp>

namespace idp::document {
Contour PolygonApproximator::Approximate(const Contour &contour,
                                         double epsilonFactor) const {
  Contour polygon;

  const double perimeter = cv::arcLength(contour, true);
  const double epsilon = perimeter * epsilonFactor;

  cv::approxPolyDP(contour, polygon, epsilon, true);

  return polygon;
};
} // namespace idp::document