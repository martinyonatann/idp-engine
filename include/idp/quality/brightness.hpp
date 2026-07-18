#pragma once
#include "idp/quality/result.hpp"
#include <opencv2/core.hpp>

namespace idp::quality {

class Brightness {
public:
  Result Analyze(const cv::Mat &image) const;
};

} // namespace idp::quality