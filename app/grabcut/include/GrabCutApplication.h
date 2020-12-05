#ifndef GRAPH_FLOW_GRABCUT_GRABCUT_APPLICATION
#define GRAPH_FLOW_GRABCUT_GRABCUT_APPLICATION
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "GrabCutOutput.h"

namespace GrabCut {
class GrabCutApplication {
 private:
 public:
  GrabCutApplication(const cv::Mat& cvImg);

  void setFGMask(const std::string& fgMaskPath);
  void setPBFGMask(const std::string& lastSegmentationMask);
  void setBGMask(const std::string& bgMaskPath);
  void setUnknownMask(const std::string& uknMaskPath);

  GrabCutOutput run(const int iterations);

 private:
  const cv::Mat& cvImg;
  cv::Mat fgMask, bgMask, unknownMask, pbFgMask;
};
}  // namespace GrabCut
#endif