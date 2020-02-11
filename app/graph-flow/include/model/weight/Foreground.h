#ifndef GRAPH_FLOW_FOREGROUND_H
#define GRAPH_FLOW_FOREGROUND_H

#include <DGtal/helpers/StdDefs.h>

#include <graph-flow/utils/digital.h>
#include <graph-flow/core/TerminalWeight.h>
#include <graph-flow/utils/digital.h>

class Foreground:public GraphFlow::Core::TerminalWeight
{
public:
    typedef DGtal::Z2i::DigitalSet DigitalSet;
    typedef GraphFlow::Utils::Digital::DTL2 DTL2;

    Foreground(const DTL2& dtl2, int optBand, double ballRadius):
    connectedToSource( GraphFlow::Utils::Digital::level(dtl2,optBand,optBand-1) ),
    maxPenal(M_PI*pow(ballRadius,2)*1024)
    {}

    double operator()(const Point& p)
    {
        if(connectedToSource(p)) return  maxPenal;
        else return 0;
    }

    TerminalType type(){ return TerminalType::Source; }

private:
    DigitalSet connectedToSource;
    double maxPenal;
};


#endif //GRAPH_FLOW_FOREGROUND_H
