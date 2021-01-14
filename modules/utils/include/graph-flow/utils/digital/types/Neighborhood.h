#ifndef GRAPHFLOW_UTILS_DIGITAL_NEIGHBORHOOD_H
#define GRAPHFLOW_UTILS_DIGITAL_NEIGHBORHOOD_H

#include <DGtal/helpers/StdDefs.h>

namespace GraphFlow::Utils::Digital::Neighborhood {
/**
 * \brief Predicate to identify 8-connected points in a digital set.
 * \author Daniel Martins Antunes
 * \version 0.1
 * \date 2018/08/27
 */
class EightNeighborhoodPredicate {
 public:
  typedef DGtal::Z2i::Domain Domain;
  typedef DGtal::Z2i::Point Point;
  typedef DGtal::Z2i::DigitalSet DigitalSet;

  /**
   * \brief Constructor.
   * @param digitalSet DGtal DigitalSet in which the predicate is evaluated.
   */
  explicit EightNeighborhoodPredicate(const DigitalSet &digitalSet);

  /**
   * \brief Test if point is 8-connected in digitalSet.
   * @param aPoint Point belonging to digital set.
   * @return True if aPoint is 8-connected.
   */
  bool operator()(const Point &aPoint) const;

  /**
   * \brief Test if point is 8-connected in digitalSet.
   * @param it ConstIterator from the digitalSet domain.
   * @return True if dereferenced iterator is 8-connected point in digitalSet.
   */
  bool operator()(const Domain::ConstIterator &it) const;

 private:
  const DigitalSet &myDigitalSet;
  Point filter[4] = {Point(0, 1), Point(1, 0), Point(-1, 0), Point(0, -1)};

  Point lowerBound, upperBound;
};

/**
 * \brief Predicate to identify 4-connected points in a digital set.
 * \author Daniel Martins Antunes
 * \version 0.1
 * \date 2018/08/27
 */
class FourNeighborhoodPredicate {
 public:
  typedef DGtal::Z2i::Domain Domain;
  typedef DGtal::Z2i::Point Point;
  typedef DGtal::Z2i::DigitalSet DigitalSet;

  /**
   * \brief Constructor.
   * @param digitalSet DGtal DigitalSet in which the predicate is evaluated.
   */
  explicit FourNeighborhoodPredicate(const DigitalSet &digitalSet);

  /**
   * \brief Test if point is 4-connected in digitalSet.
   * @param aPoint Point belonging to digital set.
   * @return True if aPoint is 4-connected.
   */
  bool operator()(const Point &aPoint) const;

  /**
   * \brief Test if point is 4-connected in digitalSet.
   * @param it ConstIterator from the digitalSet domain.
   * @return True if dereferenced iterator is 4-connected point in digitalSet.
   */
  bool operator()(const Domain::ConstIterator &it) const;

 private:
  const DigitalSet &myDigitalSet;
  Point filter[8] = {Point(0, 1), Point(1, 0),   Point(-1, 0), Point(0, -1),
                     Point(1, 1), Point(-1, -1), Point(1, -1), Point(-1, 1)};

  Point lowerBound, upperBound;
};
}  // namespace GraphFlow::Utils::Digital::Neighborhood
#endif