#include "graph-flow/utils/digital.h"

namespace GraphFlow::Utils::Digital
{
    DigitalSet resolveShape(const std::string& shape,double gridStep,double radius)
    {
        if(shape=="triangle") return DIPaCUS::Shapes::triangle(gridStep,0,0,radius);
        else if(shape=="square") return DIPaCUS::Shapes::square(gridStep,0,0,radius);
        else if(shape=="pentagon") return DIPaCUS::Shapes::NGon(gridStep,0,0,radius,5);
        else if(shape=="heptagon") return DIPaCUS::Shapes::NGon(gridStep,0,0,radius,7);
        else if(shape=="ball") return DIPaCUS::Shapes::ball(gridStep,0,0,radius);
        else if(shape=="flower") return DIPaCUS::Shapes::flower(gridStep,0,0,radius,radius/2.0,2);
        else if(shape=="ellipse") return DIPaCUS::Shapes::ellipse(gridStep,0,0,radius,radius/2);
        else if(shape=="wave") return DIPaCUS::Shapes::wave(gridStep,1200,radius*3,radius*6,0.01);
        else if(shape=="bean") return DIPaCUS::Shapes::bean(gridStep,0,0,0.1);
        else return DIPaCUS::Shapes::triangle(gridStep,0,0,radius);

    }

    DTL2 interiorDistanceTransform(const Domain& domain, const DigitalSet& original)
    {
        return DTL2(domain, original, DGtal::Z2i::l2Metric);
    }

    DTL2 exteriorDistanceTransform(const Domain& domain, const DigitalSet& original)
    {
        DigitalSet d(domain);
        d.assignFromComplement(original);

        return DTL2(domain, d, DGtal::Z2i::l2Metric);
    }

    DigitalSet level(const DTL2& dtL2, int lessThan, int greaterThan)
    {
        DigitalSet d(dtL2.domain());
        for(auto it=dtL2.domain().begin();it!=dtL2.domain().end();++it)
        {
            if(dtL2(*it)<=lessThan && dtL2(*it)>greaterThan) d.insert(*it);
        }

        return d;
    }

    DigitalSet dilate(const DigitalSet& ds,int size)
    {
        DigitalSet dilated(ds.domain());
        DIPaCUS::Morphology::dilate(dilated,ds,DIPaCUS::Morphology::StructuringElement(DIPaCUS::Morphology::StructuringElement::CIRCLE,size),1);
        return dilated;
    }

    DigitalSet erode(const DigitalSet& ds,int size)
    {
        DigitalSet eroded(ds.domain());
        DIPaCUS::Morphology::erode(eroded,ds,DIPaCUS::Morphology::StructuringElement(DIPaCUS::Morphology::StructuringElement::CIRCLE,size),1);
        return eroded;
    }
}