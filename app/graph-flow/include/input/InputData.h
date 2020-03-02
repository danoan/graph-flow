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
        h=0.25;
        alpha=0.01;
        beta=1.0;
        optBand=2;

        energy=Elastica;

        nThreads=4;
        neighborhoodSize=2;

        outputFolder="";
        pixelMaskFilepath="";
    }

    std::string shapeName;

    int iterations;
    double radius;
    double h;
    double alpha;
    double beta;

    int optBand;

    EnergyType  energy;

    int nThreads;
    int neighborhoodSize;

    std::string outputFolder;
    std::string pixelMaskFilepath;
};

#endif //GRAPH_FLOW_APP_INPUTDATA_H
