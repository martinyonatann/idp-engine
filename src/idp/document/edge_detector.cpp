#include "idp/document/edge_detector.hpp"
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/img_hash.hpp>
#include <opencv2/imgproc.hpp>

namespace idp::document {
cv::Mat EdgeDetector::Detect(const cv::Mat &image) const {
  cv::Mat gray;

  if (image.channels() == 3) {
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
  } else {
    gray = image;
  }

  cv::Mat blurred;
  cv::GaussianBlur(gray, blurred, cv::Size(5, 5), 0);

  cv::Mat edges;
  cv::Canny(blurred, edges, 50, 150);

  return edges;
}
} // namespace idp::document