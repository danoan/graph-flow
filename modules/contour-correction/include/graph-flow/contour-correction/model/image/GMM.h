#ifndef GRAPH_FLOW_IMAGE_SEGMENTATION_GMM_H
#define GRAPH_FLOW_IMAGE_SEGMENTATION_GMM_H

#include <opencv2/core.hpp>

namespace GraphFlow::ContourCorrection::Image {
/*
 GMM - Gaussian Mixture Model
 as implemented in grabcut.cpp file in opencv
*/
class GMM {
 public:
  static const int componentsCount = 5;

  GMM(cv::Mat &_model);
  double operator()(const cv::Vec3d color) const;
  double operator()(int ci, const cv::Vec3d color) const;
  int whichComponent(const cv::Vec3d color) const;

  void initLearning();
  void addSample(int ci, const cv::Vec3d color);
  void endLearning();

  double sumAllContribs();

  double standardNormal(const cv::Vec3d color) const;

  double standardNormal(int ci, const cv::Vec3d color) const;

 private:
  void calcInverseCovAndDeterm(int ci, double singularFix);
  cv::Mat model;
  double *coefs;
  double *mean;
  double *cov;

  double inverseCovs[componentsCount][3][3];
  double covDeterms[componentsCount];

  double sums[componentsCount][3];
  double prods[componentsCount][3][3];
  int sampleCounts[componentsCount];
  int totalSampleCount;
};
}  // namespace GraphFlow::ContourCorrection::Image

#endif  // GRAPH_FLOW_IMAGE_SEGMENTATION_GMM_H
