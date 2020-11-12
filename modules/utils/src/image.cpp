#include "graph-flow/utils/image.h"

namespace GraphFlow::Utils::Image {
void setHighlightMask(cv::Mat& outputImage, const cv::Mat& baseImage,
                      const cv::Mat& mask) {
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

  outputImage.setTo(cv::Vec3b(150, 250, 250), contourMask);
}

void exportImageFromDigitalSet(const DigitalSet& ds,
                               const std::string& outputFilepath) {
  Point lb, ub;
  ds.computeBoundingBox(lb, ub);
  lb += DGtal::Z2i::Point(-80, -80);
  ub += DGtal::Z2i::Point(80, 80);
  Image2D image(DGtal::Z2i::Domain(lb, ub));
  DIPaCUS::Representation::digitalSetToImage(image, ds);

  DGtal::GenericWriter<Image2D>::exportFile(outputFilepath, image);
}

void exportImageFromDigitalSet(const DigitalSet& ds, const Domain& domain,
                               const std::string& outputFilepath) {
  Image2D image(domain);
  DIPaCUS::Representation::digitalSetToImage(image, ds);

  DGtal::GenericWriter<Image2D>::exportFile(outputFilepath, image);
}
}  // namespace GraphFlow::Utils::Image