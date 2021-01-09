#ifndef GRAPHFLOW_UTILS_DIGITAL_CONTOUR_H
#define GRAPHFLOW_UTILS_DIGITAL_CONTOUR_H

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/images/SimpleThresholdForegroundPredicate.h>
#include <DGtal/kernel/sets/DigitalSetInserter.h>
#include <DGtal/topology/helpers/Surfaces.h>

#include "types/Neighborhood.h"

namespace GraphFlow::Utils::Digital::Contour {

typedef DGtal::Z2i::DigitalSet DigitalSet;
typedef DGtal::Z2i::Curve Curve;

/**
 * \brief Computes the pixel digital boundary of digital set
 * dsIn accordingly with neighborhood type (four or eight
 * connected ).
 *
 * @tparam TNeighborhood Connectedeness predicate. \refitem Neighborhood
 * @param dsOut Pixel boundary output
 * @param dsIn Digital set input\
 * @param t Thickness of contour
 */
template <typename TNeighborhood>
void digitalBoundary(DigitalSet& dsOut, const DigitalSet& dsIn, size_t t = 1);

/**
 * \brief Compute linel boundary for a given digital set
 *
 * @param boundOut Linel boundary as a DGtal::Z2i::Curve
 * @param dsIn Digital set input
 */
void computeBoundaryCurve(Curve& boundOut, const DigitalSet& dsIn);

}  // namespace GraphFlow::Utils::Digital::Contour

#include "contour.hpp"

#endif