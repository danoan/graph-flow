#ifndef GRAPH_FLOW_SUMMARY_FLOW_SUMMARY_FLOW_INPUTDATA_H
#define GRAPH_FLOW_SUMMARY_FLOW_SUMMARY_FLOW_INPUTDATA_H

#include <vector>

#include "summary-flow/model/ColorScheme.h"
#include "summary-flow/types.h"

namespace SummaryFlow {
struct InputData {
  InputData() {
    drawInterval = -1;

    drawCenterBall = false;
    radius = 5;
    h = 1.0;

    colorScheme = DefaultColorSchemes::Classic;

    pixelMaskPath = "";
    dirsMaskPath = "";

    flowImagesFolderPath = "";
    outputFilePath = "";
    imageExtension = ".pgm";

    iot = ImageOutputType::SVG;
  }

  int drawInterval;
  double radius;
  double h;
  bool drawCenterBall;

  ColorScheme colorScheme;

  std::string pixelMaskPath;
  std::string dirsMaskPath;
  std::string imageExtension;

  ImageOutputType iot;
  std::string flowImagesFolderPath;
  std::string outputFilePath;
};
}  // namespace SummaryFlow

#endif  // GRAPH_FLOW_SUMMARY_FLOW_SUMMARY_FLOW_INPUTDATA_H
