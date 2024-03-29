#ifndef GRAPH_FLOW_IMAGE_SEGMENTATION_CURVATURE_H
#define GRAPH_FLOW_IMAGE_SEGMENTATION_CURVATURE_H

#include <DGtal/helpers/StdDefs.h>
#include <graph-flow/core/EdgeWeight.h>
#include <graph-flow/utils/digital/set-operations.h>

namespace GraphFlow::ContourCorrection::Graph::Weight {
class Curvature : public GraphFlow::Core::EdgeWeight {
 public:
  typedef GraphFlow::Core::NormalizationGroup NormalizationGroup;
  typedef DGtal::Z2i::DigitalSet DigitalSet;
  typedef GraphFlow::Utils::Digital::SetOperations::DigitalBallIntersection
      DigitalBallIntersection;
  typedef EdgeWeight::Point Point;

  typedef std::map<Point, double> PointMap;

 private:
  double computeAreaDifference(const Point &p) {
    intersectionSet->clear();
    DBI->operator()(*intersectionSet, p);
    return pow(halfBallArea - (double)intersectionSet->size(), 2);
  }

 public:
  Curvature(double radius, double gridStep, const DigitalSet &ds,
            double curvatureWeight)
      : radius(radius), gridStep(gridStep), curvatureWeight(curvatureWeight) {
    DBI = new DigitalBallIntersection(radius, ds);
    intersectionSet = new DigitalSet(DBI->domain());
    halfBallArea = (double)DBI->digitalBall().size() / 2.0;
  }

  ~Curvature() {
    delete DBI;
    delete intersectionSet;
  }

  double operator()(const Point &p1, const Point &p2) {
    if (pm.find(p1) == pm.end())
      pm[p1] = computeAreaDifference(p1) * pow(gridStep, 2);

    if (pm.find(p2) == pm.end())
      pm[p2] = computeAreaDifference(p2) * pow(gridStep, 2);

    return (pm[p1] + pm[p2]) / 2.0;
  }

  double weight() const { return curvatureWeight; }
  NormalizationGroup normalizationGroup() const {
    return NormalizationGroup::GeometryRelated;
  }

 private:
  PointMap pm;
  double radius;
  double gridStep;
  double curvatureWeight;
  double halfBallArea;

  DigitalBallIntersection *DBI;
  DigitalSet *intersectionSet;
};
}  // namespace GraphFlow::ContourCorrection::Graph::Weight

#endif  // GRAPH_FLOW_IMAGE_SEGMENTATION_CURVATURE_H
