#pragma once
#include "idp/quality/result.hpp"
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>

namespace idp::quality {
class Resolution {
public:
  Result Analyze(const cv::Mat &image) const;
};
} // namespace idp::quality