#ifndef GRAPH_FLOW_APP_GRAPH_FLOW_INPUTDATA_H
#define GRAPH_FLOW_APP_GRAPH_FLOW_INPUTDATA_H

#include <string>

namespace App{
struct InputData
{
  enum NeighborhoodType{Morphology,Random};

  InputData()
  {
    shapeName="square";

    iterations=10;
    radius=5;
    vradius=radius;
    h=0.25;
    alpha=0.01;
    beta=1.0;
    optBand=2;
    border=20;

    nThreads=4;
    neighborhoodSize=2;
    neighborhoodType=Morphology;

    outputFolder="";
    pixelMaskFilepath="";

    printEnergyValue=false;
    saveAllFigures=false;
    displayFlow=false;
  }

  std::string shapeName;

  int iterations;
  double radius;
  double vradius; //Validation radius
  double h;
  double alpha;
  double beta;

  int optBand;
  int border;

  int nThreads;
  int neighborhoodSize;
  NeighborhoodType neighborhoodType;

  std::string outputFolder;
  std::string pixelMaskFilepath;

  bool printEnergyValue;
  bool saveAllFigures;
  bool displayFlow;
};
}

#endif //GRAPH_FLOW_APP_GRAPH_FLOW_INPUTDATA_H
