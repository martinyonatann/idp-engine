#include "idp/assessment/blur.hpp"
#include "idp/assessment/brightness.hpp"
#include "idp/assessment/resolution.hpp"
#include "idp/assessment/status.hpp"
#include "idp/document/document_detector.hpp"

#include <cstdlib>
#include <fmt/core.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

int main(int argc, char *argv[]) {
  fmt::print("=====================================\n");
  fmt::print("             IDP ENGINE\n");
  fmt::print("=====================================\n");

  if (argc < 2) {
    fmt::print("Usage: idp-engine <image_path>\n");
    return EXIT_FAILURE;
  }

  cv::Mat image = cv::imread(argv[1]);

  if (image.empty()) {
    fmt::print("Failed to load image: {}\n", argv[1]);
    return EXIT_FAILURE;
  }

  // ----------------------------
  // Quality Analysis
  // ----------------------------
  fmt::print("[1/2] Quality Analysis\n");

  idp::assessment::Brightness brightness;
  auto brightnessResult = brightness.Analyze(image);

  fmt::print("  Brightness : {}\n",
             idp::assessment::ToString(brightnessResult.status));

  if (brightnessResult.status == idp::assessment::Status::Fail) {
    fmt::print("{}\n", brightnessResult.message);
    return EXIT_FAILURE;
  }

  idp::assessment::Blur blur;
  auto blurResult = blur.Analyze(image);

  fmt::print("  Blur       : {}\n",
             idp::assessment::ToString(blurResult.status));

  if (blurResult.status == idp::assessment::Status::Fail) {
    fmt::print("{}\n", blurResult.message);
    return EXIT_FAILURE;
  }

  idp::assessment::Resolution resolution;
  auto resolutionResult = resolution.Analyze(image);

  fmt::print("  Resolution : {}\n",
             idp::assessment::ToString(resolutionResult.status));

  if (resolutionResult.status == idp::assessment::Status::Fail) {
    fmt::print("{}\n", resolutionResult.message);
    return EXIT_FAILURE;
  }

  // ----------------------------
  // Document Detection
  // ----------------------------
  fmt::print("[2/2] Document Detection\n");

  idp::document::DocumentDetector detector;

  auto result = detector.Detect(image);

  if (!result.found) {
    fmt::print("  Document : NOT FOUND\n");
    return EXIT_FAILURE;
  }

  fmt::print("  Document : FOUND\n");

  // Draw detected polygon
  cv::Mat output = image.clone();

  cv::polylines(output, std::vector<idp::document::Contour>{result.polygon},
                true, cv::Scalar(0, 255, 0), 3);

  if (!cv::imwrite("../output/document_detected.jpg", output)) {
    fmt::print("Failed to save output image\n");
    return EXIT_FAILURE;
  }

  fmt::print("Saved: ../output/document_detected.jpg\n");

  fmt::print("\nCorners:\n");

  for (std::size_t i = 0; i < result.polygon.size(); ++i) {
    const auto &point = result.polygon[i];

    fmt::print("  {} -> ({}, {})\n", i + 1, point.x, point.y);
  }

  return EXIT_SUCCESS;
}