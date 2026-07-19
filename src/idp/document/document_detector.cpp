#include "idp/document/document_detector.hpp"

#include "idp/document/contour_detector.hpp"
#include "idp/document/edge_detector.hpp"
#include "idp/document/polygon_approximator.hpp"

#include <fmt/core.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

namespace idp::document {

Result DocumentDetector::Detect(const cv::Mat &image) const {
  constexpr double kMinimumDocumentAreaRatio = 0.20;

  EdgeDetector edgeDetector;
  ContourDetector contourDetector;
  PolygonApproximator approximator;

  // Detect edges
  cv::Mat edges = edgeDetector.Detect(image);
  cv::imwrite("../output/edges.jpg", edges);

  // Find contours
  Contours contours = contourDetector.Detect(edges);

  fmt::print("Contours found: {}\n", contours.size());

  // Select largest contours
  Contours candidates = contourDetector.SelectLargest(contours);

  fmt::print("Largest candidates: {}\n", candidates.size());

  const double imageArea = static_cast<double>(image.cols) * image.rows;

  const double minimumArea = imageArea * kMinimumDocumentAreaRatio;

  fmt::print("Image area   : {:.0f}\n", imageArea);
  fmt::print("Minimum area : {:.0f}\n", minimumArea);

  for (std::size_t i = 0; i < candidates.size(); ++i) {
    const auto &contour = candidates[i];

    Contour polygon = approximator.Approximate(contour);

    double area = cv::contourArea(polygon);
    bool convex = cv::isContourConvex(polygon);

    fmt::print("---------------------------------\n");
    fmt::print("Candidate {}\n", i + 1);
    fmt::print("Original Points : {}\n", contour.size());
    fmt::print("Polygon Points  : {}\n", polygon.size());
    fmt::print("Area            : {:.0f}\n", area);
    fmt::print("Convex          : {}\n", convex ? "YES" : "NO");

    // Draw candidate for debugging
    cv::Mat debug = image.clone();

    cv::polylines(debug, std::vector<Contour>{polygon}, true,
                  cv::Scalar(0, 255, 0), 3);

    cv::imwrite(fmt::format("../output/candidate_{}.jpg", i + 1), debug);

    if (polygon.size() != 4) {
      fmt::print("Rejected: polygon is not a quadrilateral\n");
      continue;
    }

    if (!convex) {
      fmt::print("Rejected: polygon is not convex\n");
      continue;
    }

    if (area < minimumArea) {
      fmt::print("Rejected: polygon area is too small\n");
      continue;
    }

    fmt::print("Document detected!\n");

    return {
        true,
        polygon,
    };
  }

  fmt::print("No valid document found.\n");

  return {};
}

} // namespace idp::document