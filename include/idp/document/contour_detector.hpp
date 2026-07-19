#pragma once
#include "idp/document/types.hpp"
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>

namespace idp::document {
class ContourDetector {
public:
  Contours Detect(const cv::Mat &edgeImage) const;
  Contours SelectLargest(const Contours &contours,
                         std::size_t maxCandidates = 5) const;
};
} // namespace idp::document