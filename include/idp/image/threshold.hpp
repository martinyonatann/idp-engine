#pragma once
#include <opencv2/core/mat.hpp>

namespace idp::image {
class Threshold {
public:
  cv::Mat Process(const cv::Mat &image) const;
};
} // namespace idp::image