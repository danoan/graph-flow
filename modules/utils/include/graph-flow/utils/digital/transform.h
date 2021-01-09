#ifndef GRAPHFLOW_UTILS_DIGITAL_TRANSFORM_H
#define GRAPHFLOW_UTILS_DIGITAL_TRANSFORM_H

#include <DGtal/helpers/StdDefs.h>

namespace GraphFlow::Utils::Digital::Transform {
typedef DGtal::Z2i::DigitalSet DigitalSet;
typedef DGtal::Z2i::Point Point;

/**
 * \brief Changes the domain of a digital set.
 *
 * The new domain has its origin set at point (0,0) and
 * dimension Length(BoundingBox(ds))+2*border. The lower
 * bounding box of original set is set at distance border
 * from origin (0,0).
 *
 * @param ds Original digital set.
 * @param border Distance of lower bounding box point of
 * original digital set from origin (0,0).
 * @return
 */
DigitalSet bottomLeftBoundingBoxAtOrigin(const DigitalSet& ds,
                                         const Point border = Point(10, 10));
}  // namespace GraphFlow::Utils::Digital::Transform

#endif