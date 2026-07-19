#include "idp/assessment/resolution.hpp"
#include "idp/assessment/status.hpp"
#include <opencv2/core/mat.hpp>

namespace idp::assessment {
Result Resolution::Analyze(const cv::Mat &image) const {
  constexpr int kMinimumShortestSide = 600;
  const int shortestSide = std::min(image.cols, image.rows);

  Result result{};
  result.value = shortestSide;
  result.status = Status::Pass;
  result.message = "Image resolution is acceptable.";

  if (shortestSide < kMinimumShortestSide) {
    result.status = Status::Fail;
    result.message = "Image resolution is too low.";
  }

  return result;
}
} // namespace idp::assessment