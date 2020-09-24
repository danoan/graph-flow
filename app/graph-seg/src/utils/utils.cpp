#include "utils/utils.h"

namespace App::Utils {
void writeEnergyData(const GraphSegIteration &gsIteration, std::ostream &os) {
  using namespace GraphFlow::Utils;
  int colLength = 20;

  os << String::fixedStrLength(colLength, gsIteration.iteration)
     << String::fixedStrLength(colLength, gsIteration.value) << "\n";
}

double evaluateEnergy(const InputData &id, const DigitalSet &ds) {
  using namespace GraphFlow::Utils;
  return Energy::elastica(ds, id.radius, id.h, id.alpha, id.curvatureTermWeight);
}

void outputImages(const GrabCutObject &gco,
                  const cv::Mat &segResultImg,
                  const DigitalSet &outputDS,
                  const std::string &outputFolder) {
  const cv::Mat &inputImage = gco.inputImage;

  cv::Mat foregroundMask = cv::Mat::zeros(inputImage.size(),
                                          CV_8UC1);
  DIPaCUS::Representation::digitalSetToCVMat(foregroundMask, outputDS);

  cv::Mat imgOutput = cv::Mat::zeros(inputImage.size(), CV_8UC3);

  BTools::Utils::setHighlightMask(imgOutput, inputImage, foregroundMask);

  std::string graphCutSegFilepath = outputFolder + "/gc-seg.png";
  std::string correctedSegFilepath = outputFolder + "/corrected-seg.png";
  std::string seedsFilepath = outputFolder + "/seeds.png";

  cv::Mat gcSegImg = cv::Mat::zeros(inputImage.size(), inputImage.type());

  cv::Mat segResultMask = cv::Mat::zeros(segResultImg.size(), CV_8UC1);
  cv::cvtColor(segResultImg, segResultMask, CV_RGB2GRAY);
  BTools::Utils::setHighlightMask(gcSegImg, inputImage, segResultMask);

  cv::imwrite(graphCutSegFilepath, gcSegImg);
  cv::imwrite(correctedSegFilepath, imgOutput);
  cv::imwrite(seedsFilepath, gco.seeds);
}
}