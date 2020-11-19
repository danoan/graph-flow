#ifndef GRAPH_FLOW_IMAGE_SEGMENTATION_INPUTDATA_H
#define GRAPH_FLOW_IMAGE_SEGMENTATION_INPUTDATA_H

#include <string>

namespace App {
struct InputData {
  enum NeighborhoodType{Morphology,Random};
  
  InputData() {
    iterations = 10;
    radius = 5;
    vradius = radius;
    h = 0.25;
    alpha = 0.01;

    regionalTermWeight = 1;
    curvatureTermWeight = 0.5;

    optBand = 2;
    grabcutIterations = 1;
    tolerance=-1;

    nThreads = 4;
    neighborhoodSize = 2;
    neighborhoodType = Morphology;

    outputFolder = "";
    gcoFilepath = "";

    printEnergyValue = false;
    saveAllFigures = false;
    displayFlow = false;
  }

  int iterations;
  double radius;
  double vradius; //Validation radius
  double h;

  double alpha;
  int optBand;
  double tolerance;
  int grabcutIterations;

  double regionalTermWeight;
  double curvatureTermWeight;
  int nThreads;
  int neighborhoodSize;
  NeighborhoodType  neighborhoodType;

  std::string outputFolder;
  std::string gcoFilepath;

  bool printEnergyValue;
  bool saveAllFigures;
  bool displayFlow;
};
}

#endif //GRAPH_FLOW_IMAGE_SEGMENTATION_INPUTDATA_H
