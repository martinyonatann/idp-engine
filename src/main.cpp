#include "idp/document/contour_detector.hpp"
#include "idp/document/edge_detector.hpp"
#include "idp/image/grayscale.hpp"
#include "idp/quality/blur.hpp"
#include "idp/quality/brightness.hpp"
#include "idp/quality/resolution.hpp"
#include "idp/quality/result.hpp"
#include "idp/quality/status.hpp"
#include <cstddef>
#include <cstdlib>
#include <fmt/core.h>
#include <opencv2/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <string>

constexpr char kOutputPath[] = "../output/copy.jpg";
constexpr char kGrayOutputPath[] = "../output/grayscale.jpg";

int main(int argc, char *argv[]) {
  fmt::print("=====================================\n");
  fmt::print("          IDP ENGINE                 \n");
  fmt::print("=====================================\n");
  if (argc < 2) {
    fmt::print("Usage: idp-engine <image_path>\n");
    return EXIT_FAILURE;
  }

  std::string imagePath = argv[1];

  // load image
  cv::Mat image = cv::imread(imagePath);
  if (image.empty()) {
    fmt::print("Failed to load image : {}\n", imagePath);
    return EXIT_FAILURE;
  }

  fmt::print("[on process] quality check\n");

  idp::quality::Brightness brightness;
  idp::quality::Result brightnessResult = brightness.Analyze(image);
  if (brightnessResult.status == idp::quality::Status::Fail) {
    fmt::print("- Brightness [{}] Reason : {}\n",
               idp::quality::ToString(brightnessResult.status),
               brightnessResult.message);

    return EXIT_FAILURE;
  }

  fmt::print("- Brightness    [{}]\n",
             idp::quality::ToString(brightnessResult.status));

  idp::quality::Blur blur;
  idp::quality::Result blurResult = blur.Analyze(image);
  if (blurResult.status == idp::quality::Status::Fail) {
    fmt::print("- Blur   [{}] Reason : {}\n",
               idp::quality::ToString(blurResult.status), blurResult.message);

    return EXIT_FAILURE;
  }

  fmt::print("- Blur          [{}]\n",
             idp::quality::ToString(blurResult.status));

  idp::quality::Resolution resolution;
  idp::quality::Result resolutionResult = resolution.Analyze(image);
  if (resolutionResult.status == idp::quality::Status::Fail) {
    fmt::print("- Resolution [{}] Reason : {}\n",
               idp::quality::ToString(resolutionResult.status),
               resolutionResult.message);

    return EXIT_FAILURE;
  }

  fmt::print("- Resolution    [{}]\n",
             idp::quality::ToString(resolutionResult.status));

  fmt::print("[done] quality check\n");

  if (!cv::imwrite(kOutputPath, image)) {
    fmt::print("Failed to save image\n");
    return EXIT_FAILURE;
  }

  idp::image::Grayscale grayscale;
  cv::Mat gray = grayscale.Process(image);

  idp::document::EdgeDetector detector;
  cv::Mat edges = detector.Detect(gray);
  if (!cv::imwrite(kGrayOutputPath, edges)) {
    fmt::print("Failed to save edges image\n");
    return EXIT_FAILURE;
  }

  idp::document::ContourDetector contourDetector;
  idp::document::Contours contours = contourDetector.Detect(edges);
  idp::document::Contours candidates = contourDetector.SelectLargest(contours);
  fmt::print("largest contour candidates: {}\n", candidates.size());

  for (std::size_t i = 0; i < candidates.size(); i++) {
    fmt::print("Candidate {} area {}\n", i + 1, cv::contourArea(candidates[i]));
  }

  return EXIT_SUCCESS;
}