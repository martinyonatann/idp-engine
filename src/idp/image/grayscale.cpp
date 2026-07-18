#include "idp/image/grayscale.hpp"
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>

namespace idp::image {

cv::Mat Grayscale::Process(const cv::Mat &image) const {
  cv::Mat gray;
  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
  return gray;
}

} // namespace idp::image