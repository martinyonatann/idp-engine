#include "idp/image/sharpen.hpp"

#include <opencv2/imgproc.hpp>

namespace idp::image {
cv::Mat Sharpen::Process(const cv::Mat &image) const {
  cv::Mat output;

  cv::Mat kernel = (cv::Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);

  cv::filter2D(image, output, -1, kernel);

  return output;
}

} // namespace idp::image