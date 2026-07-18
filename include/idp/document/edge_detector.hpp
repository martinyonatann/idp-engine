#pragma once

#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>

namespace idp::document {
class EdgeDetector {
public:
  cv::Mat Detect(const cv::Mat &image) const;
};
} // namespace idp::document