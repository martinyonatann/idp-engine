#pragma once
#include "idp/assessment/result.hpp"
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>

namespace idp::assessment {
class Blur {
public:
  Result Analyze(const cv::Mat &image) const;
};
} // namespace idp::assessment