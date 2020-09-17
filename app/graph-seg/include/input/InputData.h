#ifndef GRAPH_FLOW_APP_INPUTDATA_H
#define GRAPH_FLOW_APP_INPUTDATA_H

#include <string>

struct InputData
{
  InputData()
  {
    iterations=10;
    radius=5;
    h=0.25;
    alpha=0.01;

    regionalTermWeight=1;
    curvatureTermWeight=0.5;

    optBand=2;
    grabcutIterations=1;

    nThreads=4;
    neighborhoodSize=2;

    outputFolder="";
    pixelMaskFilepath="";
    gcoFilepath="";

    printEnergyValue=false;
    saveAllFigures=false;
    displayFlow=false;
  }

  int iterations;
  double radius;
  double h;

  double alpha;
  int optBand;
  int grabcutIterations;

  double regionalTermWeight;
  double curvatureTermWeight;
  int nThreads;
  int neighborhoodSize;

  std::string outputFolder;
  std::string pixelMaskFilepath;
  std::string gcoFilepath;

  bool printEnergyValue;
  bool saveAllFigures;
  bool displayFlow;
};

#endif //GRAPH_FLOW_APP_INPUTDATA_H
