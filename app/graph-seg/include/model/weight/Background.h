#ifndef GRAPH_FLOW_BACKGROUND_H
#define GRAPH_FLOW_BACKGROUND_H

#include <graph-flow/core/TerminalWeight.h>
#include "model/CVMatDistribution.h"

class Background:public GraphFlow::Core::TerminalWeight
{
public:
    Background(CVMatDistribution& bkgDistr,double dataTermWeight):bkgDistr(bkgDistr),dataTermWeight(dataTermWeight)
    {}

    double operator()(const Point& p)
    {
        return -log(1-bkgDistr(bkgDistr.img.rows-p[1],p[0]));
    }

    double weight() const { return dataTermWeight; }
    bool normalize() const{ return true;}

    TerminalType type() const{ return TerminalType::Target; }

private:
    CVMatDistribution bkgDistr;
    double dataTermWeight;
};

#endif //GRAPH_FLOW_BACKGROUND_H
