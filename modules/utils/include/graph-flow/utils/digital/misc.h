#ifndef GRAPHFLOW_UTILS_DIGITAL_MISC_H
#define GRAPHFLOW_UTILS_DIGITAL_MISC_H

#include <DGtal/geometry/volumes/distance/DistanceTransformation.h>
#include <DGtal/helpers/StdDefs.h>

namespace GraphFlow::Utils::Digital::Misc {

typedef DGtal::Z2i::DigitalSet DigitalSet;
typedef DGtal::Z2i::Domain Domain;
typedef DGtal::DistanceTransformation<DGtal::Z2i::Space, DigitalSet,
                                      DGtal::Z2i::L2Metric>
    DTL2;

DTL2 interiorDistanceTransform(const Domain& domain,
                               const DigitalSet& original);
DTL2 exteriorDistanceTransform(const Domain& domain,
                               const DigitalSet& original);

DigitalSet level(const DTL2& dtL2, int lessThan, int greaterThan);
}  // namespace GraphFlow::Utils::Digital::Misc

#endif