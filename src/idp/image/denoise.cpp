#include "idp/image/denoise.hpp"
#include <opencv2/core/mat.hpp>
#include <opencv2/photo.hpp>

namespace idp::image {
cv::Mat Denoise::Process(const cv::Mat &image) const {
  cv::Mat output;

  cv::fastNlMeansDenoising(image, output);
  return output;
}
} // namespace idp::image