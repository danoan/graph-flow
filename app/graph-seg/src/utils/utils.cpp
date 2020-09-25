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

void outputImages(const cv::Mat cvImgIn,
                  const DigitalSet &outputDS,
                  const std::string &outputFolder) {
  cv::Mat foregroundMask = cv::Mat::zeros(cvImgIn.size(),
                                          CV_8UC1);
  DIPaCUS::Representation::digitalSetToCVMat(foregroundMask, outputDS);

  cv::Mat imgOutput = cv::Mat::zeros(cvImgIn.size(), CV_8UC3);
  BTools::Utils::setHighlightMask(imgOutput, cvImgIn, foregroundMask);


  std::string outputFilepath = outputFolder + "/seg-out.png";
  cv::imwrite(outputFilepath, imgOutput);
}
}