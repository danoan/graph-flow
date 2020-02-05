#ifndef GRAPH_FLOW_UTILS_DIGITAL_H
#define GRAPH_FLOW_UTILS_DIGITAL_H

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/geometry/volumes/distance/DistanceTransformation.h>

#include <DIPaCUS/base/Shapes.h>
#include <DIPaCUS/components/Morphology.h>

namespace GraphFlow::Utils::Digital
{
    typedef DGtal::Z2i::DigitalSet DigitalSet;
    typedef DGtal::Z2i::Domain Domain;
    typedef DGtal::DistanceTransformation<DGtal::Z2i::Space, DigitalSet, DGtal::Z2i::L2Metric> DTL2;


    DigitalSet resolveShape(const std::string& shape,double gridStep,double radius=20);

    DTL2 interiorDistanceTransform(const Domain& domain, const DigitalSet& original);
    DTL2 exteriorDistanceTransform(const Domain& domain, const DigitalSet& original);

    DigitalSet level(const DTL2& dtL2, int lessThan, int greaterThan);

    DigitalSet dilate(const DigitalSet& ds,int size=1);
    DigitalSet erode(const DigitalSet& ds,int size=1);
}

#endif //GRAPH_FLOW_UTILS_DIGITAL_H
