#include "graph-flow/utils/digital/representation.h"

namespace GraphFlow::Utils::Digital::Representation {
void imageAsDigitalSet(DigitalSet &dsOut, const std::string &imgPath,
                       const ThresholdValue tv) {
  typedef DGtal::DigitalSetInserter<DigitalSet> DigitalSetInserter;
  Image2D image = DGtal::GenericReader<Image2D>::import(imgPath);

  assert(dsOut.domain().lowerBound() <= image.domain().lowerBound());
  assert(dsOut.domain().upperBound() >= image.domain().upperBound());

  DigitalSetInserter inserter(dsOut);
  DGtal::setFromImage(image, inserter, tv, 255);
}

void imageAsDigitalSet(DigitalSet &dsOut, const Image2D &imgIn,
                       const ThresholdValue tv) {
  typedef DGtal::DigitalSetInserter<DigitalSet> DigitalSetInserter;

  assert(dsOut.domain().lowerBound() <= imgIn.domain().lowerBound());
  assert(dsOut.domain().upperBound() >= imgIn.domain().upperBound());

  DigitalSetInserter inserter(dsOut);
  DGtal::setFromImage(imgIn, inserter, tv, 255);
}

void digitalSetToImage(Image2D &imgOut, const DigitalSet &dsIn) {
  typedef DGtal::Z2i::Point Point;

  assert(imgOut.domain().lowerBound() <= dsIn.domain().lowerBound());
  assert(imgOut.domain().upperBound() >= dsIn.domain().upperBound());

  int ubY = dsIn.domain().upperBound()[1];

  for (auto it = dsIn.begin(); it != dsIn.end(); ++it) {
    Point p = *it;
    unsigned char v = (unsigned char)(dsIn(*it)) ? 255 : 0;
    imgOut.setValue(*it, v);
  }
}

void imageToCVMat(cv::Mat &cvImgOut, const Image2D &imgIn) {
  typedef DGtal::Z2i::Point Point;
  typedef DGtal::Z2i::Domain Domain;

  assert(cvImgOut.type() == GRAYSCALE_IMG_TYPE);

  Domain domain = imgIn.domain();
  Point dimSize = domain.upperBound() - domain.lowerBound() + Point(1, 1);

  assert(dimSize > Point(0, 0));
  assert(cvImgOut.rows >= dimSize(1));
  assert(cvImgOut.cols >= dimSize(0));

  Point t = Point(0, 0) - domain.lowerBound();
  int ubY = cvImgOut.rows - 1;

  for (auto it = imgIn.domain().begin(); it != imgIn.domain().end(); ++it) {
    Point p = *it + t;
    unsigned char v(imgIn(*it));
    cvImgOut.at<unsigned char>((ubY - p[1]), p[0]) = v;
  }
}

void CVMatToImage(Image2D &imgOut, const cv::Mat &cvImgIn) {
  typedef DGtal::Z2i::Point Point;
  assert(cvImgIn.type() == GRAYSCALE_IMG_TYPE);
  Point dimSize =
      imgOut.domain().upperBound() - imgOut.domain().lowerBound() + Point(1, 1);

  assert(dimSize(1) >= cvImgIn.rows);
  assert(dimSize(0) >= cvImgIn.cols);

  Point t = imgOut.domain().lowerBound();

  int ubY = cvImgIn.rows - 1;
  for (int i = 0; i < cvImgIn.rows; i++) {
    for (int j = 0; j < cvImgIn.cols; j++) {
      unsigned char v(cvImgIn.at<unsigned char>(i, j));

      imgOut.setValue(Point(j + t(0), ubY - i + t(1)), v);
    }
  }
}

void digitalSetToCVMat(cv::Mat &cvImgOut, const DigitalSet &dsIn,
                       const ShiftValue sx, const ShiftValue sy) {
  typedef DGtal::Z2i::Point Point;
  typedef DGtal::Z2i::Domain Domain;

  assert(cvImgOut.type() == GRAYSCALE_IMG_TYPE);

  Domain domain = dsIn.domain();
  Point dimSize = domain.upperBound() - domain.lowerBound() + Point(1, 1);

  assert(dimSize > Point(0, 0));
  assert(cvImgOut.rows >= dimSize(1));
  assert(cvImgOut.cols >= dimSize(0));

  Point t = Point(0, 0) - domain.lowerBound();
  int ubY = cvImgOut.rows - 1;

  for (auto it = dsIn.begin(); it != dsIn.end(); ++it) {
    Point p = *it + t;
    unsigned char v = (unsigned char)(dsIn(*it)) ? 255 : 0;
    cvImgOut.at<unsigned char>((ubY - (p[1] + sy)), p[0] + sx) = v;
  }
}

void CVMatToDigitalSet(DigitalSet &dsOut, const cv::Mat &cvImgIn,
                       const ThresholdValue tv, const ShiftValue sx,
                       const ShiftValue sy) {
  typedef DGtal::Z2i::Point Point;
  assert(cvImgIn.type() == GRAYSCALE_IMG_TYPE);
  Point dimSize =
      dsOut.domain().upperBound() - dsOut.domain().lowerBound() + Point(1, 1);
  assert(dimSize(1) >= cvImgIn.rows);
  assert(dimSize(0) >= cvImgIn.cols);

  int ubY = cvImgIn.rows - 1;
  for (int i = 0; i < cvImgIn.rows; i++) {
    for (int j = 0; j < cvImgIn.cols; j++) {
      unsigned char v(cvImgIn.at<unsigned char>(i, j));
      if (v > tv) dsOut.insert(Point(j + sx, ubY - i + sy));
    }
  }
}
}  // namespace GraphFlow::Utils::Digital::Representation