#include <DGtal/helpers/StdDefs.h>
#include <DIPaCUS/base/Representation.h>
#include <DIPaCUS/components/Neighborhood.h>
#include <DIPaCUS/derivates/Misc.h>
#include <graph-flow/utils/image.h>

#include <opencv2/opencv.hpp>

#include "catch.hpp"

using namespace GraphFlow::Utils::Image;

TEST_CASE("set highlight mask", "[image]") {
  using namespace DGtal::Z2i;

  double h = 0.25;
  double R = 16;

  DigitalSet ball = DIPaCUS::Shapes::ball(h, 0, 0, R);
  const Domain& domain = ball.domain();

  Point size = domain.upperBound()-domain.lowerBound() + Point(1,1);
  cv::Mat ballImgGray = cv::Mat::zeros( size[1],size[0],CV_8UC1 );
  DIPaCUS::Representation::digitalSetToCVMat(ballImgGray, ball);

  cv::Mat ballImgColor = cv::Mat::zeros( size[1],size[0],CV_8UC3 );
  cv::cvtColor(ballImgGray, ballImgColor, cv::COLOR_GRAY2RGB);

  DigitalSet contour(ball.domain());
  DIPaCUS::Misc::digitalBoundary<
      DIPaCUS::Neighborhood::FourNeighborhoodPredicate>(contour, ball, 1);

  cv::Mat contourImg = cv::Mat::zeros(size[1],size[0],CV_8UC1);
  DIPaCUS::Representation::digitalSetToCVMat(contourImg, contour);

  cv::Vec3b contourColor(255,0,0);
  cv::Mat outImg = cv::Mat::zeros(size[1],size[0],CV_8UC3);
  setHighlightMask(outImg, ballImgColor, contourImg,contourColor);

  int count=0;
  for(int r=0;r<outImg.rows;++r){
    auto row = outImg.ptr<cv::Vec3b>(r);
    for(int c=0;c<outImg.cols;++c){
      if( row[c]==contourColor ) count++;
    }
  }

  REQUIRE(count == contour.size());
}