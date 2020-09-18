#ifndef GRAPH_FLOW_APP_GRAPH_SEG_CVMATDISTRIBUTION_H
#define GRAPH_FLOW_APP_GRAPH_SEG_CVMATDISTRIBUTION_H

#include <opencv2/core.hpp>
#include "GMM.h"

namespace App::Image {
class CVMatDistribution {
 public:
  typedef unsigned int Index;

  CVMatDistribution(const cv::Mat &img,
                    const GMM &gmm) : img(img),
                                      gmm(gmm) {}

  double operator()(Index row, Index col) const {
    double s = gmm(img.at<cv::Vec3b>(row, col)) + 1.0e-20;
    return s;
  }

 public:
  const cv::Mat &img;
  const GMM &gmm;

};
}

#endif //GRAPH_FLOW_APP_GRAPH_SEG_CVMATDISTRIBUTION_H
