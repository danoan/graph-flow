#ifndef GRAPHFLOW_UTILS_DIGITAL_CONTOUR_H
#define GRAPHFLOW_UTILS_DIGITAL_CONTOUR_H

#include <vector>
#include <set>

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/images/SimpleThresholdForegroundPredicate.h>
#include <DGtal/kernel/sets/DigitalSetInserter.h>
#include <DGtal/topology/helpers/Surfaces.h>

#include "types/Neighborhood.h"

namespace GraphFlow::Utils::Digital::Contour {

typedef DGtal::Z2i::DigitalSet DigitalSet;
typedef DGtal::Z2i::Curve Curve;
typedef DGtal::Z2i::SCell SCell;
typedef DGtal::Z2i::KSpace KSpace;


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

/**
 * \brief Extracts all contours with bel points in the mask
 * 
 * @param aVectSCellContour2D Collection of found digital contours
 * @param KSpace Khalimsky space instance
 * @param aSurfelAdj Surfel adjacency model
 * @param mask Set which bel points are constrained to be
 * @param pp Digital set from where to extract the contours
 */
void extractAll2DSCellContoursFromMask(
    std::vector<std::vector<SCell> >& aVectSCellContour2D,
    const KSpace& aKSpace,
    const DGtal::SurfelAdjacency<KSpace::dimension>& aSurfelAdj,
    const DigitalSet& mask, const DigitalSet& pp);

}  // namespace GraphFlow::Utils::Digital::Contour

#include "contour.hpp"

#endif