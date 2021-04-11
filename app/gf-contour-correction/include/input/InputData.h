#ifndef GRAPH_FLOW_IMAGE_SEGMENTATION_INPUTDATA_H
#define GRAPH_FLOW_IMAGE_SEGMENTATION_INPUTDATA_H

#include <string>

namespace App {
struct InputData {
  enum NeighborhoodType { Morphology, Random };
  enum ValidationWeightMode {
    AutomaticCorrectionLengthData,
    AutomaticCorrectionLength,
    AutomaticCorrectionData,
    Manual
  };

  InputData() {
    iterations = 10;
    radius = 12;
    vradius = radius;
    alpha = 0.01;

    dataWeightCandidate = 0.5;
    dataWeightValidation = 2.0;

    curvatureWeightCandidate = 1.0;
    curvatureWeightValidation = 1.0;

    optBand = 2;
    grabcutIterations = 1;
    tolerance = -1;

    nThreads = 4;
    neighborhoodSize = 2;
    neighborhoodType = Morphology;

    validationWeightMode = AutomaticCorrectionLengthData;

    outputFolder = "";
    gcoFilepath = "";

    printEnergyValue = false;
    saveAllFigures = false;
    displayFlow = false;
  }

  int iterations;
  double radius;
  double vradius;  // Validation radius

  double alpha;
  int optBand;
  double tolerance;
  int grabcutIterations;

  double dataWeightCandidate;
  double dataWeightValidation;

  double curvatureWeightCandidate;
  double curvatureWeightValidation;

  int nThreads;
  int neighborhoodSize;
  NeighborhoodType neighborhoodType;

  ValidationWeightMode validationWeightMode;

  std::string outputFolder;
  std::string gcoFilepath;

  bool printEnergyValue;
  bool saveAllFigures;
  bool displayFlow;
};
}  // namespace App

#endif  // GRAPH_FLOW_IMAGE_SEGMENTATION_INPUTDATA_H
