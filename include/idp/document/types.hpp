#pragma once

#include <opencv2/core.hpp>

namespace idp::document {
using Contour = std::vector<cv::Point>;
using Contours = std::vector<Contour>;
} // namespace idp::document