#ifndef GRAPH_FLOW_APP_INPUTDATA_H
#define GRAPH_FLOW_APP_INPUTDATA_H

#include <string>

struct InputData
{
  enum EnergyType{Elastica,SElastica};

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

    energy=Elastica;

    nThreads=4;
    neighborhoodSize=2;

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

  EnergyType  energy;

  int nThreads;
  int neighborhoodSize;

  std::string outputFolder;
  std::string pixelMaskFilepath;

  bool printEnergyValue;
  bool saveAllFigures;
  bool displayFlow;
};

#endif //GRAPH_FLOW_APP_INPUTDATA_H
