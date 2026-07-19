#include "idp/assessment/blur.hpp"
#include "idp/assessment/brightness.hpp"
#include "idp/assessment/resolution.hpp"
#include "idp/assessment/status.hpp"
#include "idp/document/document_detector.hpp"
#include "idp/image/contrast.hpp"
#include "idp/image/denoise.hpp"
#include "idp/image/grayscale.hpp"
#include "idp/image/sharpen.hpp"
#include "idp/image/threshold.hpp"

#include <cstdlib>
#include <fmt/core.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

namespace {

constexpr char kDocumentDetected[] = "output/document_detected.jpg";
constexpr char kGrayImage[] = "output/01_gray.jpg";
constexpr char kDenoisedImage[] = "output/02_denoised.jpg";
constexpr char kContrastImage[] = "output/03_contrast.jpg";
constexpr char kThresholdImage[] = "output/04_threshold.jpg";
constexpr char kEnhancedImage[] = "output/05_enhanced.jpg";

} // namespace

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

  // -------------------------------------------------
  // [1/3] Quality Analysis
  // -------------------------------------------------
  fmt::print("[1/3] Quality Analysis\n");

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

  // -------------------------------------------------
  // [2/3] Document Detection
  // -------------------------------------------------
  fmt::print("[2/3] Document Detection\n");

  idp::document::DocumentDetector detector;
  auto result = detector.Detect(image);

  cv::Mat document = image;

  if (!result.found) {
    fmt::print("  Document : SKIPPED (already cropped)\n");
  } else {
    fmt::print("  Document : FOUND\n");

    cv::Mat output = image.clone();

    cv::polylines(output, std::vector<idp::document::Contour>{result.polygon},
                  true, cv::Scalar(0, 255, 0), 3);

    cv::imwrite(kDocumentDetected, output);

    fmt::print("  Saved      : {}\n", kDocumentDetected);

    // TODO:
    // document = PerspectiveTransformer().Transform(image, result.polygon);
  }

  // -------------------------------------------------
  // [3/3] Image Enhancement
  // -------------------------------------------------
  fmt::print("[3/3] Image Enhancement\n");

  idp::image::Grayscale grayscale;
  cv::Mat gray = grayscale.Process(document);

  idp::image::Denoise denoise;
  cv::Mat denoised = denoise.Process(gray);

  idp::image::Contrast contrast;
  cv::Mat contrasted = contrast.Process(denoised);

  idp::image::Threshold threshold;
  cv::Mat binary = threshold.Process(contrasted);

  idp::image::Sharpen sharpen;
  cv::Mat enhanced = sharpen.Process(binary);

  cv::imwrite(kGrayImage, gray);
  cv::imwrite(kDenoisedImage, denoised);
  cv::imwrite(kContrastImage, contrasted);
  cv::imwrite(kThresholdImage, binary);
  cv::imwrite(kEnhancedImage, enhanced);

  return EXIT_SUCCESS;
}