#include <DGtal/io/readers/GenericReader.h>
#include <DGtal/io/writers/GenericWriter.h>

#include <boost/filesystem.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "catch.hpp"
#include "graph-flow/utils/digital/representation.h"
#include "graph-flow/utils/digital/shapes.h"

using namespace GraphFlow::Utils::Digital::Representation;

namespace Intern {
using namespace DGtal::Z2i;
typedef DGtal::ImageContainerBySTLVector<DGtal::Z2i::Domain, unsigned char>
    Image2D;

struct BoundingBox {
  Point lb;
  Point ub;

  bool operator==(const BoundingBox& other) const {
    return (this->lb == other.lb && this->ub == other.ub);
  }
};

bool digitalPointsMapsImagePoints(const DigitalSet& ds, const cv::Mat& cvImg,
                                  const Point& translation) {
  const int rows = cvImg.rows - 1;
  bool flag_ds_assert = true;
  std::for_each(
      ds.domain().begin(), ds.domain().end(),
      [&flag_ds_assert, &ds, &cvImg, &translation, &rows](Point _p) mutable {
        Point p = _p + translation;
        if (ds(_p))
          flag_ds_assert =
              flag_ds_assert && cvImg.at<unsigned char>(rows - p(1), p(0)) > 0;
        else
          flag_ds_assert =
              flag_ds_assert && cvImg.at<unsigned char>(rows - p(1), p(0)) == 0;
      });

  return flag_ds_assert;
}

bool digitalPointsMapsImagePoints(const DigitalSet& ds, const Image2D& image,
                                  const Point& translation) {
  bool flag_ds_assert = true;
  std::for_each(ds.domain().begin(), ds.domain().end(),
                [&flag_ds_assert, &ds, &image, &translation](Point _p) mutable {
                  Point p = _p + translation;
                  if (ds(_p))
                    flag_ds_assert = flag_ds_assert && image(p) > 0;
                  else
                    flag_ds_assert = flag_ds_assert && image(p) == 0;
                });

  return flag_ds_assert;
}

void boundingBox(BoundingBox& bb, const Image2D& img) {
  DigitalSet ds(img.domain());
  imageAsDigitalSet(ds, img);
  ds.computeBoundingBox(bb.lb, bb.ub);
}

void boundingBox(BoundingBox& bb, const cv::Mat& cvImg) {
  Domain domain(Point(0, 0), Point(cvImg.cols + 1, cvImg.rows + 1));
  DigitalSet ds(domain);

  CVMatToDigitalSet(ds, cvImg);
  ds.computeBoundingBox(bb.lb, bb.ub);
}
}  // namespace Intern

TEST_CASE("conversion between representations", "[digital]") {
  using namespace DGtal::Z2i;
  const int GRAYSCALE_IMAGE_TYPE = CV_8UC1;

  DigitalSet square = GraphFlow::Utils::Digital::Shapes::square();
  std::string tempOutputFolder = MY_MAIN_DIR;
  tempOutputFolder += "/tempDigitalRepresentation";

  boost::filesystem::create_directories(tempOutputFolder);
  std::string imagePath = tempOutputFolder + "/square.pgm";

  SECTION("digitalSetToImage") {
    Image2D image(square.domain());
    digitalSetToImage(image, square);

    Intern::BoundingBox bbImage;
    Intern::boundingBox(bbImage, image);

    Intern::BoundingBox bbDs;
    square.computeBoundingBox(bbDs.lb, bbDs.ub);

    DGtal::GenericWriter<Image2D>::exportFile(imagePath, image);

    REQUIRE(bbImage == bbDs);
    REQUIRE(Intern::digitalPointsMapsImagePoints(square, image, Point(0, 0)));
  }

  SECTION("imageAsDigitalSet") {
    Image2D image = DGtal::GenericReader<Image2D>::import(imagePath);
    DigitalSet ds(image.domain());
    imageAsDigitalSet(ds, image);

    Intern::BoundingBox bbImage;
    Intern::boundingBox(bbImage, image);

    Intern::BoundingBox bbDs;
    ds.computeBoundingBox(bbDs.lb, bbDs.ub);

    REQUIRE(bbDs == bbImage);
    REQUIRE(Intern::digitalPointsMapsImagePoints(ds, image, Point(0, 0)));
  }

  SECTION("digitalSetToCVMat") {
    const Domain& domain = square.domain();
    Point dLB = domain.lowerBound();
    Point dimSize = domain.upperBound() - domain.lowerBound() + Point(1, 1);

    cv::Mat cvImg =
        cv::Mat::zeros(dimSize(1), dimSize(0), GRAYSCALE_IMAGE_TYPE);

    digitalSetToCVMat(cvImg, square);

    Intern::BoundingBox bbDS, bbCV;
    square.computeBoundingBox(bbDS.lb, bbDS.ub);
    Intern::boundingBox(bbCV, cvImg);

    Point translation = Point(0, 0) - dLB;

    REQUIRE(bbCV.ub == bbDS.ub + translation);
    REQUIRE(Intern::digitalPointsMapsImagePoints(square, cvImg, translation));
  }

  SECTION("CVMatToDigitalSet") {
    cv::Mat cvImg = cv::imread(imagePath, GRAYSCALE_IMAGE_TYPE);
    Domain domain(Point(0, 0), Point(cvImg.cols - 1, cvImg.rows - 1));

    DigitalSet ds(domain);
    CVMatToDigitalSet(ds, cvImg);

    Intern::BoundingBox bbCvImg;
    Intern::boundingBox(bbCvImg, cvImg);

    Intern::BoundingBox bbDs;
    ds.computeBoundingBox(bbDs.lb, bbDs.ub);

    REQUIRE(bbDs == bbCvImg);
    REQUIRE(Intern::digitalPointsMapsImagePoints(ds, cvImg, Point(0, 0)));
  }

  SECTION("imageToCVMat") {
    Image2D image = DGtal::GenericReader<Image2D>::import(imagePath);

    const Domain& domain = image.domain();
    Point dimSize = domain.upperBound() - domain.lowerBound() + Point(1, 1);

    cv::Mat cvImg =
        cv::Mat::zeros(dimSize(1), dimSize(0), GRAYSCALE_IMAGE_TYPE);
    imageToCVMat(cvImg, image);

    Intern::BoundingBox bbImg, bbCV;
    Intern::boundingBox(bbImg, image);
    Intern::boundingBox(bbCV, cvImg);

    //If put outside sections, it executes once for each section.
    boost::filesystem::remove_all(tempOutputFolder);
    REQUIRE(bbCV.ub == bbImg.ub);
  }
}
