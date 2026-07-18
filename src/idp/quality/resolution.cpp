#include "idp/quality/resolution.hpp"
#include "idp/quality/status.hpp"
#include <opencv2/core/mat.hpp>

namespace idp::quality {
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
} // namespace idp::quality