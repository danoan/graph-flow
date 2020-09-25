#ifndef GRAPH_FLOW_APP_GRAPH_SEG_INPUTDATA_H
#define GRAPH_FLOW_APP_GRAPH_SEG_INPUTDATA_H

#include <string>

namespace App {
struct InputData {
  InputData() {
    iterations = 10;
    radius = 5;
    h = 0.25;
    alpha = 0.01;

    regionalTermWeight = 1;
    curvatureTermWeight = 0.5;

    regionalTermGraphWeight = 1;
    curvatureTermGraphWeight = 0.5;

    optBand = 2;

    nThreads = 4;
    neighborhoodSize = 2;

    outputFolder = "";
    inputImageFilepath = "";

    printEnergyValue = false;
    saveAllFigures = false;
    displayFlow = false;
  }

  int iterations;
  double radius;
  double h;

  double alpha;
  int optBand;

  double regionalTermWeight;
  double curvatureTermWeight;
  double regionalTermGraphWeight;
  double curvatureTermGraphWeight;

  int nThreads;
  int neighborhoodSize;

  std::string outputFolder;
  std::string inputImageFilepath;

  bool printEnergyValue;
  bool saveAllFigures;
  bool displayFlow;
};
}

#endif //GRAPH_FLOW_APP_GRAPH_SEG_INPUTDATA_H
