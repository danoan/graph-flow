#ifndef GRAPH_FLOW_IMAGE_SEGMENTATION_DATADISTRIBUTION_H
#define GRAPH_FLOW_IMAGE_SEGMENTATION_DATADISTRIBUTION_H

#include <graph-flow/io/seed/GrabCutObject.h>
#include "graph-flow/contour-correction/model/image/CVMatDistribution.h"
#include "graph-flow/contour-correction/model/image/GMM.h"

namespace GraphFlow::ContourCorrection::Image {
struct DataDistribution {
  typedef GraphFlow::IO::Seed::GrabCutObject GrabCutObject;
  typedef DGtal::Z2i::Point Point;

  void rerunGrabcut(const GrabCutObject& _gco,int grabcutIterations) {
    cv::Mat fgMask, bgMask, pbfgMask;
    GraphFlow::IO::Seed::getSeedMasks(_gco, fgMask, bgMask, pbfgMask);

    gco.inputImage = _gco.inputImage;
    gco.seeds = _gco.seeds;

    gco.grabCutMask = cv::Mat::zeros(gco.inputImage.size(), CV_8UC1);
    if (pbfgMask.size.dims() > 0 && pbfgMask.size[0] > 0) {
      cv::Mat sureBGMask = cv::Mat::zeros(gco.inputImage.size(), CV_8UC1);
      cv::bitwise_not(pbfgMask, sureBGMask);

      gco.grabCutMask.setTo(cv::GrabCutClasses::GC_BGD, sureBGMask);
      gco.grabCutMask.setTo(cv::GrabCutClasses::GC_PR_BGD, pbfgMask);
    } else {
      gco.grabCutMask = cv::GrabCutClasses::GC_PR_BGD;
    }

    gco.grabCutMask.setTo(cv::GrabCutClasses::GC_BGD, bgMask);
    gco.grabCutMask.setTo(cv::GrabCutClasses::GC_FGD, fgMask);

    cv::Mat bgModel;
    cv::Mat fgModel;

    cv::grabCut(gco.inputImage, gco.grabCutMask, cv::Rect(), bgModel, fgModel,
                grabcutIterations, cv::GC_INIT_WITH_MASK);

    fgGMM = GMM(fgModel);
    bgGMM = GMM(bgModel);

    gco.segMask = cv::Mat::zeros(gco.inputImage.size(), CV_8UC1);

    cv::compare(gco.grabCutMask, cv::GC_PR_FGD, gco.segMask, cv::CMP_EQ);

    gco.segMask.setTo(255, fgMask);
    gco.inputImage.copyTo(segResultImg, gco.segMask);

    setSeeds(fgMask, bgMask);
  }

  void setSeeds(const cv::Mat &fgMask, const cv::Mat &bgMask) {
    for (int r = 0; r < fgMask.rows; ++r) {
      const unsigned char *Ri = fgMask.ptr<unsigned char>(r);
      for (int c = 0; c < fgMask.cols; ++c) {
        if (Ri[c] == 255) fgSeeds.insert(Point(c, fgMask.rows - r - 1));
      }
    }

    for (int r = 0; r < bgMask.rows; ++r) {
      const unsigned char *Ri = bgMask.ptr<unsigned char>(r);
      for (int c = 0; c < bgMask.cols; ++c) {
        if (Ri[c] == 255) bgSeeds.insert(Point(c, bgMask.rows - r - 1));
      }
    }
  }

  DataDistribution(const GrabCutObject& _gco, int grabcutIterations)
      : fgGMM(fgModel), bgGMM(bgModel) {
    rerunGrabcut(_gco,grabcutIterations);

    fgDistr = new CVMatDistribution(gco.inputImage, fgGMM);
    bgDistr = new CVMatDistribution(gco.inputImage, bgGMM);
  }

  GrabCutObject gco;
  cv::Mat segResultImg;

  cv::Mat fgModel, bgModel;
  GMM fgGMM, bgGMM;

  CVMatDistribution *fgDistr;
  CVMatDistribution *bgDistr;

  std::set<Point> fgSeeds;
  std::set<Point> bgSeeds;
};
}  // namespace GraphFlow::ContourCorrection::Image

#endif  // GRAPH_FLOW_IMAGE_SEGMENTATION_DATADISTRIBUTION_H
