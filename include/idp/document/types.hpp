#pragma once

#include <opencv2/core/types.hpp>
#include <vector>

namespace idp::document {

using Point = cv::Point;
using Contour = std::vector<Point>;
using Contours = std::vector<Contour>;

} // namespace idp::document