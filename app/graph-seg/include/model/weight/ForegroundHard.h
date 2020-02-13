#ifndef GRAPH_SEG_FOREGROUND_HARD_H
#define GRAPH_SEG_FOREGROUND_HARD_H

#include <DGtal/helpers/StdDefs.h>

#include <graph-flow/utils/digital.h>
#include <graph-flow/core/TerminalWeight.h>
#include <graph-flow/utils/digital.h>

class ForegroundHard:public GraphFlow::Core::TerminalWeight
{
public:
    typedef DGtal::Z2i::DigitalSet DigitalSet;
    typedef GraphFlow::Utils::Digital::DTL2 DTL2;

    ForegroundHard(const DTL2& dtl2, int optBand, double ballRadius):
    connectedToSource( GraphFlow::Utils::Digital::level(dtl2,optBand,optBand-1) ),
    maxPenal(M_PI*pow(ballRadius,2)*1024)
    {}

    double operator()(const Point& p)
    {
        if(connectedToSource(p)) return  maxPenal;
        else return 0;
    }

    double weight() const { return 1.0; }
    bool normalize() const {return false;}

    TerminalType type() const{ return TerminalType::Source; }

private:
    DigitalSet connectedToSource;
    double maxPenal;
};


#endif //GRAPH_SEG_FOREGROUND_HARD_H
