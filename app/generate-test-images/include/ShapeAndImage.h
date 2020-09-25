#ifndef GRAPH_FLOW_APP_GENERATE_TEST_IMAGES_SHAPEANDIMAGE_H_
#define GRAPH_FLOW_APP_GENERATE_TEST_IMAGES_SHAPEANDIMAGE_H_

#include <DGtal/helpers/StdDefs.h>
#include <opencv2/core.hpp>

namespace App{
struct ShapeAndImage{
  using DigitalSet=DGtal::Z2i::DigitalSet;

  ShapeAndImage(const DigitalSet& ds, const cv::Mat& cvImg):ds(ds),cvImg(cvImg){}
  DigitalSet ds;
  cv::Mat cvImg;
};
}

#endif //GRAPH_FLOW_APP_GENERATE_TEST_IMAGES_SHAPEANDIMAGE_H_
