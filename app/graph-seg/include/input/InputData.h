#ifndef GRAPH_FLOW_APP_INPUTDATA_H
#define GRAPH_FLOW_APP_INPUTDATA_H

#include <string>

struct InputData
{
    enum EnergyType{Elastica,SElastica};

    InputData()
    {
        iterations=10;
        radius=5;
        h=0.25;
        alpha=0.01;
        dataTermWeight=0.5;

        optBand=2;

        energy=Elastica;

        nThreads=4;
        neighborhoodSize=2;

        outputFolder="";
        pixelMaskFilepath="";
        gcoFilepath="/home/dantu/GIT/PhD/graph-flow/input/gc-object.xml";
    }

    std::string shapeName;

    int iterations;
    double radius;
    double h;
    double alpha;
    int optBand;

    double dataTermWeight;
    EnergyType  energy;

    int nThreads;
    int neighborhoodSize;

    std::string outputFolder;
    std::string pixelMaskFilepath;
    std::string gcoFilepath;
};

#endif //GRAPH_FLOW_APP_INPUTDATA_H
