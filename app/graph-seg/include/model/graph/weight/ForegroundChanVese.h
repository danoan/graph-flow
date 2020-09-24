#ifndef GRAPH_FLOW_APP_GRAPH_SEG_FOREGROUNDCHANVESE_H
#define GRAPH_FLOW_APP_GRAPH_SEG_FOREGROUNDCHANVESE_H

#include <graph-flow/core/TerminalWeight.h>
#include "model/image/CVMatDistribution.h"

namespace App::Graph::Weight {
class ForegroundChanVese : public GraphFlow::Core::TerminalWeight {
 public:
  ForegroundChanVese(const cv::Mat& cvImg, const cv::Vec3d& avgColor, double regionalGraphWeight)
  : cvImg(cvImg),
  avgColor(avgColor),
    regionalGraphWeight(regionalGraphWeight){}

  double operator()(const Point &p) {

    int c = p[0];
    int r = cvImg.rows-1-p[1];

    cv::Vec3d color = cvImg.at<cv::Vec3b>(r,c)/255.0;
    cv::Vec3d diff = color-avgColor;
    double v = pow(diff[0],2)+pow(diff[1],2)+pow(diff[2],2);

    return 1e-10+200.0/(1+exp(5*v-2));
  }

  double weight() const { return regionalGraphWeight; }
  bool normalize() const { return true; }

  TerminalType type() const { return TerminalType::Source; }

 private:
  const cv::Mat& cvImg;
  const cv::Vec3d avgColor;

  double regionalGraphWeight;
};
}

#endif //GRAPH_FLOW_APP_GRAPH_SEG_FOREGROUNDCHANVESE_H
