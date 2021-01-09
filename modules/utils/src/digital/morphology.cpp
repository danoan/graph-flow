#include "graph-flow/utils/digital/morphology.h"

namespace GraphFlow::Utils::Digital::Morphology {

void dilate(DigitalSet &dsOut, const DigitalSet &dsIn,
            const StructuringElement se, size_t it) {
  using namespace DGtal::Z2i;
  using namespace GraphFlow::Utils::Digital;

  Point lbIn, ubIn;
  dsIn.computeBoundingBox(lbIn, ubIn);

  Point dimIn =
      dsIn.domain().upperBound() - dsIn.domain().lowerBound() + Point(1, 1);
  int rIn = dimIn(1);
  int cIn = dimIn(0);

  Point lbOut, ubOut;
  lbOut = dsOut.domain().lowerBound();
  ubOut = dsOut.domain().upperBound();

  Point dimOut = ubOut - lbOut + Point(1, 1);
  int rOut = dimOut(1);
  int cOut = dimOut(0);

  assert(lbOut(0) <= lbIn(0) - se.size);
  assert(lbOut(1) <= lbIn(1) - se.size);

  assert(ubOut(0) >= ubIn(0) + se.size);
  assert(ubOut(1) >= ubIn(1) + se.size);

  Point shift = dsIn.domain().lowerBound();

  cv::Mat cvSrc(rOut, cOut, IMG_TYPE, cv::Scalar(0));
  cv::Mat dilation_dst(rOut, cOut, IMG_TYPE, cv::Scalar(0));

  Representation::digitalSetToCVMat(cvSrc, dsIn);

  cv::Mat element = cv::getStructuringElement(
      se.type, cv::Size(2 * se.size + 1, 2 * se.size + 1),
      cv::Point(se.size, se.size));

  cv::dilate(cvSrc, dilation_dst, element, cv::Point(-1, -1), it);

  Representation::CVMatToDigitalSet(dsOut, dilation_dst, 1, shift(0), shift(1));
}

void erode(DigitalSet &dsOut, const DigitalSet &dsIn,
           const StructuringElement se, size_t it) {
  using namespace DGtal::Z2i;
  using namespace GraphFlow::Utils::Digital;

  Point lbIn, ubIn;
  dsIn.computeBoundingBox(lbIn, ubIn);

  Point dimIn =
      dsIn.domain().upperBound() - dsIn.domain().lowerBound() + Point(1, 1);
  int rIn = dimIn(1);
  int cIn = dimIn(0);

  Point lbOut, ubOut;
  lbOut = dsOut.domain().lowerBound();
  ubOut = dsOut.domain().upperBound();

  Point dimOut = ubOut - lbOut + Point(1, 1);
  int rOut = dimOut(1);
  int cOut = dimOut(0);

  assert(lbOut(0) <= lbIn(0));
  assert(lbOut(1) <= lbIn(1));

  assert(ubOut(0) >= ubIn(0));
  assert(ubOut(1) >= ubIn(1));

  Point shift = dsIn.domain().lowerBound();

  cv::Mat cvSrc(rIn, cIn, IMG_TYPE, cv::Scalar(0));
  cv::Mat erosion_dst(rIn, cIn, IMG_TYPE, cv::Scalar(0));

  Representation::digitalSetToCVMat(cvSrc, dsIn);
  cv::Mat element = cv::getStructuringElement(
      se.type, cv::Size(2 * se.size + 1, 2 * se.size + 1),
      cv::Point(se.size, se.size));

  cv::erode(cvSrc, erosion_dst, element, cv::Point(-1, -1), it);
  Representation::CVMatToDigitalSet(dsOut, erosion_dst, 1, shift(0), shift(1));
}

void dilate(DigitalSet& dsOut, const DigitalSet &ds, size_t size) {
  dilate(dsOut, ds, StructuringElement(StructuringElement::CIRCLE, size), 1);
}

void erode(DigitalSet& dsOut, const DigitalSet &ds, size_t size) {
  erode(dsOut, ds, StructuringElement(StructuringElement::CIRCLE, size), 1);
}

}  // namespace GraphFlow::Utils::Digital::Morphology