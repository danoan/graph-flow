#ifndef GRAPHFLOW_UTILS_DIGITAL_SETOPERATIONS_H
#define GRAPHFLOW_UTILS_DIGITAL_SETOPERATIONS_H

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/kernel/sets/DigitalSetInserter.h>

#include "graph-flow/utils/digital/shapes.h"

/**
 * \brief Set operations on DGtal digital sets.
 *
 * \author Daniel Martins Antunes
 * \version 0.1
 * \date 2018/08/27
 */
namespace GraphFlow::Utils::Digital::SetOperations {

typedef DGtal::Z2i::DigitalSet DigitalSet;
typedef DGtal::Z2i::Domain Domain;
typedef DGtal::Z2i::Point Point;

/**
 * \brief Computes the difference set between two digital sets.
 * @param differenceSet Difference set A-B
 * @param A First set
 * @param B Second set
 */
void setDifference(DigitalSet &differenceSet, const DigitalSet &A,
                   const DigitalSet &B);

/**
 * \brief Computes the intersection set between two digital sets.
 * @param digitalIntersection Intersection set of A and B
 * @param A First set
 * @param B Second set
 */
template <class TPointSet>
void setIntersection(TPointSet &digitalIntersection, const DigitalSet &A,
                     const DigitalSet &B);

/**
 * \brief Computes the intersection set between two digital sets.
 * @param digitalIntersection Intersection set of A and B
 * @param A First set
 * @param B Second set
 * @param translation Every point of A will be translated of it
 */
template <class TPointSet>
void setIntersection(TPointSet &digitalIntersection, const DigitalSet &A,
                     const DigitalSet &B, const Point &translation);

/**
 * \brief Computes intersection of any digital object with a
 * given digital ball.
 */
class DigitalBallIntersection {
 public:
  typedef DGtal::Z2i::Space Space;
  typedef DGtal::Z2i::Domain Domain;

 private:
  /**
   * \brief Extends the domain of a digital set in order
   * to accomodate a ball around its original limits.
   *
   * During the intersection computation we need to construct
   * a digital set in which ball and intersectWith set are merged.
   * This function guarantees that such set has the proper domain.
   * @param ds DigitalSet to be extended
   * @param r Radius of the digital ball
   * @return
   */
  static DigitalSet extendDS(const DigitalSet &ds, size_t r);

  /**
   * \brief Extends the domain of a digital set in order
   * to accomodate a ball around its original limits.
   *
   * During the intersection computation we need to construct
   * a digital set in which ball and intersectWith set are merged.
   * This function guarantees that such set has the proper domain.
   * @param ds DigitalSet to be extended
   * @param r Radius of the digital ball
   * @return
   */
  static Domain extendDomain(const DigitalSet &ds, size_t r);

 public:
  DigitalBallIntersection(size_t r, const DigitalSet &intersectWith);

  template <class TPointSet>
  void operator()(TPointSet &intersectionSet, Point center) {
    setIntersection(intersectionSet, _ball, _ds, center);
  }

  const Domain &domain() { return _extDomain; }
  const DigitalSet &digitalBall() { return _ball; }

 private:
  size_t _r;
  DigitalSet _ball;
  const DigitalSet _ds;
  const Domain _extDomain;
};

}  // namespace GraphFlow::Utils::Digital::SetOperations

#include "set-operations.hpp"

#endif