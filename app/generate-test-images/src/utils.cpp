#include "utils.h"

namespace App::Utils {
ShapeAndImage addNoise(const DigitalSet &dsIn, NoiseFunction nf, double noiseRatio) {
  using namespace DGtal::Z2i;

  const Domain &domain = dsIn.domain();

  Point dims = domain.upperBound() - domain.lowerBound() + Point(1, 1);
  cv::Mat cvImg = cv::Mat::zeros(dims[1], dims[0], CV_8UC1);
  DIPaCUS::Representation::digitalSetToCVMat(cvImg, dsIn);

  cv::Mat cvImgNoise = cv::Mat::zeros(dims[1], dims[0], CV_8UC1);
  cvImg.copyTo(cvImgNoise);
  nf(cvImgNoise, cvImg, noiseRatio);

  return ShapeAndImage(dsIn, cvImgNoise);
}

void rotate(cv::Mat &cvOut, const cv::Mat &cvIn, Point center) {
  std::random_device rd;
  std::uniform_int_distribution dAngle(0, 359);

  int angle = dAngle(rd);

  cv::Mat R = cv::getRotationMatrix2D(cv::Point2f(center[0], center[1]), angle, 1.0);
  cv::warpAffine(cvIn, cvOut, R, cvIn.size());
}

DigitalSet rotate(const DigitalSet &dsIn) {
  Point dims = dsIn.domain().upperBound() - dsIn.domain().lowerBound() + Point(1, 1);

  cv::Mat cvImg = cv::Mat::zeros(dims[1], dims[0], CV_8UC1);
  DIPaCUS::Representation::digitalSetToCVMat(cvImg, dsIn);

  DGtal::PointVector<2, double> center(0, 0);
  for (auto p:dsIn) center += p;
  center /= ((double) dsIn.size());

  cv::Mat cvRotated = cv::Mat::zeros(dims[1], dims[0], CV_8UC1);
  center[1] = cvRotated.rows - 1 - center[1];
  rotate(cvRotated, cvImg, Point(floor(center[0]), floor(center[1])));

  DigitalSet dsOut(dsIn.domain());
  DIPaCUS::Representation::CVMatToDigitalSet(dsOut, cvRotated);
  return dsOut;
}

void randomNoise(cv::Mat &cvOut, const cv::Mat &cvIn, double ratio) {
  int nr = cvIn.rows;
  int nc = cvIn.cols;
  int n = nr*nc*ratio;

  std::random_device rd;
  std::uniform_int_distribution dRows(0, nr - 1);
  std::uniform_int_distribution dCols(0, nc - 1);
  std::uniform_int_distribution dGray(0, 255);

  while (n > 0) {
    int r = dRows(rd);
    int c = dCols(rd);
    int g = dGray(rd);

    cvOut.at<unsigned char>(r, c) = g;
    --n;
  }
}

DigitalSet disturbContour(const DigitalSet &dsIn, int damagePoints) {
  DigitalSet contourDS(dsIn.domain());
  DIPaCUS::Misc::digitalBoundary<DIPaCUS::Neighborhood::FourNeighborhoodPredicate>(contourDS, dsIn, 1);

  std::vector<Point> vP;
  vP.reserve(contourDS.size());
  vP.insert(vP.end(), contourDS.begin(), contourDS.end());

  std::random_device rd;
  std::uniform_int_distribution dContourPoint(0, ((int) vP.size()));

  DigitalSet ball = DIPaCUS::Shapes::ball(1.0, 0, 0, 3);
  DigitalSet dsOut = dsIn;
  while (damagePoints > 0) {
    Point p = vP[dContourPoint(rd)];
    for (auto pB:ball)dsOut.erase(pB + p);

    damagePoints--;
  }

  return dsOut;
}
}