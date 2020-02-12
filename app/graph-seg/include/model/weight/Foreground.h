#ifndef GRAPH_FLOW_FOREGROUND_H
#define GRAPH_FLOW_FOREGROUND_H

#include <graph-flow/core/TerminalWeight.h>
#include "model/CVMatDistribution.h"

class Foreground:public GraphFlow::Core::TerminalWeight
{
public:
    Foreground(CVMatDistribution& frgDistr,double dataTermWeight):frgDistr(frgDistr),dataTermWeight(dataTermWeight)
    {}

    double operator()(const Point& p)
    {
        return -log( 1 - frgDistr(frgDistr.img.rows - p[1],p[0]) );
    }

    double weight() const { return dataTermWeight; }
    bool normalize() const{ return true;}

    TerminalType type() const{ return TerminalType::Source; }

private:
    CVMatDistribution frgDistr;
    double dataTermWeight;
};

#endif //GRAPH_FLOW_FOREGROUND_H
