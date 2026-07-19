#include "idp/image/threshold.hpp"

#include <opencv2/imgproc.hpp>

namespace idp::image {

cv::Mat Threshold::Process(const cv::Mat &image) const {
  cv::Mat output;

  cv::adaptiveThreshold(image, output, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C,
                        cv::THRESH_BINARY, 11, 2);

  return output;
}

} // namespace idp::image