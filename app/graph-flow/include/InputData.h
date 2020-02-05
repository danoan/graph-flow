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
        optBand=2;

        energy=Elastica;

        nThreads=4;
        neighborhoodSize=2;

        outputFolder="";
    }

    std::string shapeName;

    int iterations;
    double radius;
    double h;
    double alpha;
    int optBand;

    EnergyType  energy;

    int nThreads;
    int neighborhoodSize;

    std::string outputFolder;
};

#endif //GRAPH_FLOW_APP_INPUTDATA_H
