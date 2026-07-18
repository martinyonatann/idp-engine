#include "idp/quality/blur.hpp"
#include "idp/quality/result.hpp"
#include "idp/quality/status.hpp"
#include <opencv2/core.hpp>
#include <opencv2/core/hal/interface.h>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>

namespace idp::quality {
Result Blur::Analyze(const cv::Mat &image) const {
  cv::Mat gray;
  if (image.channels() == 3) {
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
  } else {
    gray = image;
  }

  cv::Mat laplacian;
  cv::Laplacian(gray, laplacian, CV_64F);

  cv::Scalar mean;
  cv::Scalar stddev;

  cv::meanStdDev(laplacian, mean, stddev);
  double score = stddev[0] * stddev[0];

  Result result{};
  result.value = score;

  if (score < 100.0) {
    result.status = Status::Fail;
    result.message = "Image is too blurry.";
  } else if (score < 300.0) {
    result.status = Status::Warning;
    result.message = "Image is slightly blurry.";
  } else {
    result.status = Status::Pass;
    result.message = "Image sharpness is acceptable.";
  }

  return result;
};
} // namespace idp::quality