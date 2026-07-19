#pragma once
#include "idp/assessment/result.hpp"
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>

namespace idp::assessment {
class Resolution {
public:
  Result Analyze(const cv::Mat &image) const;
};
} // namespace idp::assessment