#pragma once
#include "idp/document/result.hpp"
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>

namespace idp::document {
class DocumentDetector {
public:
  Result Detect(const cv::Mat &image) const;
};
} // namespace idp::document