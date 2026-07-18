#include "idp/document/contour_detector.hpp"
#include <algorithm>
#include <opencv2/imgproc.hpp>
#include <vector>

namespace idp::document {
Contours ContourDetector::Detect(const cv::Mat &edgeImage) const {
  Contours contours;

  cv::findContours(edgeImage, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

  return contours;
}

Contours ContourDetector::SelectLargest(const Contours &contours,
                                        std::size_t maxCandidates) const {
  auto sortedContours = contours;

  std::sort(sortedContours.begin(), sortedContours.end(),
            [](const auto &lhs, const auto &rhs) {
              return cv::contourArea(lhs) > cv::contourArea(rhs);
            });

  if (sortedContours.size() > maxCandidates) {
    sortedContours.resize(maxCandidates);
  }

  return sortedContours;
};

} // namespace idp::document