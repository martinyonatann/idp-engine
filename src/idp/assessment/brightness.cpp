#include "idp/assessment/brightness.hpp"
#include "idp/assessment/result.hpp"

#include <opencv2/core.hpp>

namespace idp::assessment {

Result Brightness::Analyze(const cv::Mat &image) const {
  Result result{};
  result.value = cv::mean(image)[0];

  if (result.value < 60) {
    result.status = Status::Fail;
    result.message = "Image is too dark.";
  } else if (result.value > 200) {
    result.status = Status::Warning;
    result.message = "Image is too bright.";
  } else {
    result.status = Status::Pass;
    result.message = "Brightness is acceptable.";
  }

  return result;
}

} // namespace idp::assessment