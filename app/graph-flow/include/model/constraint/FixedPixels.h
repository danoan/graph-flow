#ifndef GRAPH_FLOW_FIXEDPIXELS_H
#define GRAPH_FLOW_FIXEDPIXELS_H

#include <DGtal/helpers/StdDefs.h>

#include <DIPaCUS/derivates/Misc.h>

#include <graph-flow/core/HardConstraint.h>
#include <graph-flow/core/HardConstraintElement.h>

class FixedPixels:public GraphFlow::Core::HardConstraint
{
public:
    typedef DGtal::Z2i::DigitalSet DigitalSet;
    typedef GraphFlow::Core::HardConstraintElement HardConstraintElement;
    typedef HardConstraint::HardConstraintIterator HardConstraintIterator;

    FixedPixels(double radius, const DigitalSet& ds, const DigitalSet& pixelMask)
    {
        using namespace DGtal::Z2i;
        double maxPenal = pow( M_PI*pow(radius,2),2);

        Point neighborhood[4] = {Point(0,1),Point(1,0),Point(-1,0),Point(0,-1)};
        Curve curve;
        DIPaCUS::Misc::computeBoundaryCurve(curve,ds);

        const Domain& domain = ds.domain();
        KSpace kspace;
        kspace.init(domain.lowerBound(),domain.upperBound(),true);
        for(auto c:curve)
        {
            auto pixels = kspace.sUpperIncident(c);
            Point pOut,pInn;
            for(auto _p:pixels)
            {
                Point originalCoords = kspace.sCoords(_p);
                if(ds(originalCoords)) pInn=originalCoords;
                else pOut = originalCoords;
            }

            if(pixelMask(pInn))
            {
                arcPenVector.push_back( HardConstraintElement( HardConstraintElement::FromSource, pInn,pInn,maxPenal) );
                arcPenVector.push_back( HardConstraintElement( HardConstraintElement::ToTarget, pOut,pOut,maxPenal) );
            }

        }
    }

    HardConstraintIterator begin(){ return arcPenVector.begin(); }
    HardConstraintIterator end(){ return arcPenVector.end(); }

private:
    std::vector<HardConstraintElement> arcPenVector;
};

#endif //GRAPH_FLOW_FIXEDPIXELS_H
