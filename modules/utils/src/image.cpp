#include "graph-flow/utils/image.h"

namespace GraphFlow::Utils::Image {
void setHighlightMask(cv::Mat &outputImage, const cv::Mat &baseImage,
                      const cv::Mat &mask, cv::Vec3b color) {
  using namespace DGtal::Z2i;
  cv::Mat bwImage8UC1 = cv::Mat::zeros(baseImage.size(), CV_8UC1);
  cv::cvtColor(baseImage, bwImage8UC1, cv::COLOR_RGB2GRAY);

  cv::Mat bwImageInputType = cv::Mat::zeros(baseImage.size(), CV_8UC1);
  cv::cvtColor(bwImage8UC1, bwImageInputType, cv::COLOR_GRAY2RGB);

  outputImage = cv::Mat::zeros(baseImage.size(), baseImage.type());

  bwImageInputType.copyTo(outputImage);
  baseImage.copyTo(outputImage, mask);

  DigitalSet dsMask(
      Domain(Point(0, 0), Point(baseImage.cols - 1, baseImage.rows - 1)));
  DigitalSet dsContour(dsMask.domain());
  cv::Mat contourMask = cv::Mat::zeros(baseImage.size(), CV_8UC1);

  DIPaCUS::Representation::CVMatToDigitalSet(dsMask, mask, 1);
  DIPaCUS::Misc::digitalBoundary<
      DIPaCUS::Neighborhood::FourNeighborhoodPredicate>(dsContour, dsMask, 2);
  DIPaCUS::Representation::digitalSetToCVMat(contourMask, dsContour);

  outputImage.setTo(color, contourMask);
}
}  // namespace GraphFlow::Utils::Image