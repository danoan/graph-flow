#include <graph-flow/io/seed/GrabCutObject.h>

#include <boost/filesystem.hpp>
#include <iostream>
#include <opencv2/highgui.hpp>

#include "GrabCutApplication.h"
#include "GrabCutOutput.h"
#include "InputData.h"

using namespace GrabCut;
using namespace GraphFlow::IO::Seed;

GrabCutOutput runGrabCut(const std::string& imgPath,
                         const std::string& unknownMask,
                         const std::string& fgSeedMask,
                         const std::string& bgSeedMask,
                         const std::string& lastSegmentationMask,
                         const int iterations) {
  cv::Mat cvImg = cv::imread(imgPath);
  GrabCutApplication gca(cvImg);

  gca.setUnknownMask(unknownMask);
  gca.setFGMask(fgSeedMask);
  gca.setPBFGMask(lastSegmentationMask);
  gca.setBGMask(bgSeedMask);

  return gca.run(iterations);
}

cv::Mat constructSeedMask(const std::string& inputImagePath,
                          const std::string& fgSeedMaskPath,
                          const std::string& bgSeedMaskPath,
                          const std::string& unknownMaskPath) {
  cv::Mat outImg = cv::imread(inputImagePath, cv::IMREAD_COLOR);
  cv::Mat fg = cv::imread(fgSeedMaskPath, CV_8UC1);
  cv::Mat bg = cv::imread(bgSeedMaskPath, CV_8UC1);

  outImg.setTo(FG_SEED_COLOR, fg);
  outImg.setTo(BG_SEED_COLOR, bg);
  if (unknownMaskPath != "") {
    cv::Mat pbfg = cv::imread(unknownMaskPath, CV_8UC1);
    std::vector<std::vector<cv::Point> > contours;
    cv::findContours(pbfg, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    cv::Rect r = cv::boundingRect(contours[0]);
    cv::rectangle(outImg, r, PBFG_SEED_COLOR, 4);
  }

  return outImg;
}

int main(int argc, char* argv[]) {
  InputData id = readInput(argc, argv);

  cv::Mat inputImg = cv::imread(id.imgPath);
  GrabCutOutput gco =
      runGrabCut(id.imgPath, id.unknownMask, id.fgSeedMask, id.bgSeedMask,
                 id.lastSegmentationMask, id.iterations);

  GrabCutObject gcObject;
  gcObject.grabCutMask = gco.grabCutMask;
  gcObject.segMask = gco.segMaskResult;
  gcObject.inputImage = inputImg;
  gcObject.seeds = constructSeedMask(id.imgPath, id.fgSeedMask, id.bgSeedMask,
                                     id.unknownMask);
  write(gcObject, id.outputObject);

  cv::Mat fg, bg, pbfg;
  getSeedMasks(gcObject, fg, bg, pbfg);

  cv::Mat segResultImg = cv::Mat::zeros(inputImg.size(), CV_8UC4);

  inputImg.copyTo(segResultImg, gco.segMaskResult);

  if (id.outputSegImage != "") {
    cv::imwrite(id.outputSegImage, segResultImg);
  }
  if (id.showSeg) {
    cv::namedWindow("GrabCut");
    cv::imshow("GrabCut", segResultImg);
    std::cout << "Press any key to continue...\n";
    cv::waitKey(0);
  }
}