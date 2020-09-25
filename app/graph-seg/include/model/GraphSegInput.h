#ifndef GRAPH_FLOW_APP_GRAPH_SEG_GRAPHSEGINPUT_H
#define GRAPH_FLOW_APP_GRAPH_SEG_GRAPHSEGINPUT_H

#include <DGtal/helpers/StdDefs.h>
#include <opencv2/core.hpp>

#include "input/InputData.h"

namespace App {
struct GraphSegInput {
  typedef DGtal::Z2i::DigitalSet DigitalSet;

  GraphSegInput(const InputData &id, const DigitalSet &inputDS, const cv::Mat& cvImg) :
      inputData(id),
      inputDS(inputDS),
      cvImg(cvImg){}

  const InputData &inputData;
  const DigitalSet &inputDS;
  const cv::Mat& cvImg;
};
}
#endif //GRAPH_FLOW_APP_GRAPH_SEG_GRAPHSEGINPUT_H
