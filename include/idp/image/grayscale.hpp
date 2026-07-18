#pragma once

#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>

namespace idp::image {
class Grayscale {
public:
  cv::Mat Process(const cv::Mat &image) const;
};
} // namespace idp::image