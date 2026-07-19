#pragma once
#include "idp/assessment/result.hpp"
#include <opencv2/core.hpp>

namespace idp::assessment {

class Brightness {
public:
  Result Analyze(const cv::Mat &image) const;
};

} // namespace idp::assessment