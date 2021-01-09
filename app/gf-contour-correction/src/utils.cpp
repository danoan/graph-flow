#include "utils.h"

namespace App::Utils {
void writeEnergyData(const GraphSegIteration &gsIteration, std::ostream &os) {
  using namespace GraphFlow::Utils;
  int colLength = 20;

  os << String::fixedStrLength(colLength, gsIteration.iteration)
     << String::fixedStrLength(colLength, gsIteration.value) << "\n";
}

void outputImages(const GrabCutObject &gco, const cv::Mat &segResultImg,
                  const DigitalSet &outputDS, const std::string &outputFolder) {
  const cv::Mat &inputImage = gco.inputImage;

  cv::Mat foregroundMask = cv::Mat::zeros(inputImage.size(), CV_8UC1);
  GraphFlow::Utils::Digital::Representation::digitalSetToCVMat(foregroundMask, outputDS);

  cv::Mat imgOutput = cv::Mat::zeros(inputImage.size(), CV_8UC3);

  GraphFlow::Utils::Image::setHighlightMask(imgOutput, inputImage,
                                            foregroundMask);

  std::string graphCutSegFilepath = outputFolder + "/gc-seg.png";
  std::string correctedSegFilepath = outputFolder + "/corrected-seg.png";
  std::string seedsFilepath = outputFolder + "/seeds.png";

  cv::Mat gcSegImg = cv::Mat::zeros(inputImage.size(), inputImage.type());

  cv::Mat segResultMask = cv::Mat::zeros(segResultImg.size(), CV_8UC1);
  cv::cvtColor(segResultImg, segResultMask, CV_RGB2GRAY);
  GraphFlow::Utils::Image::setHighlightMask(gcSegImg, inputImage,
                                            segResultMask);

  cv::imwrite(graphCutSegFilepath, gcSegImg);
  cv::imwrite(correctedSegFilepath, imgOutput);
  cv::imwrite(seedsFilepath, gco.seeds);
}
}  // namespace App::Utils