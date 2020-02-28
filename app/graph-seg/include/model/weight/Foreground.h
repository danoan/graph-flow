#ifndef GRAPH_FLOW_FOREGROUND_H
#define GRAPH_FLOW_FOREGROUND_H

#include <graph-flow/core/TerminalWeight.h>
#include "model/CVMatDistribution.h"

class Foreground:public GraphFlow::Core::TerminalWeight
{
public:
    Foreground(CVMatDistribution& frgDistr,double dataTermWeight):frgDistr(frgDistr)
    {}

    double operator()(const Point& p)
    {
        return -log( frgDistr(frgDistr.img.rows - p[1],p[0]) );
    }

    double weight() const { return 1; }
    bool normalize() const{ return true;}

    TerminalType type() const{ return TerminalType::Target; }

private:
    CVMatDistribution frgDistr;
};

#endif //GRAPH_FLOW_FOREGROUND_H
