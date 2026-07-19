#include "idp/image/contrast.hpp"

#include <opencv2/imgproc.hpp>

namespace idp::image {

cv::Mat Contrast::Process(const cv::Mat &image) const {
  cv::Mat output;

  cv::equalizeHist(image, output);

  return output;
}

} // namespace idp::image