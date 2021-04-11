#include "graph-flow/core/neighborhood/RandomNeighborhood.h"

namespace GraphFlow::Core::Neighborhood {

void Random::randomOnContour(DigitalSet& dsOutput) const {
  using namespace DGtal::Z2i;

  std::vector<std::vector<Point>> vcontours;
  DGtal::SurfelAdjacency<2> sadj(true);

  KSpace kspace;
  kspace.init(dsOutput.domain().lowerBound(), dsOutput.domain().upperBound(),
              true);
  DGtal::Surfaces<KSpace>::extractAllPointContours4C(vcontours, kspace,
                                                     dsOutput, sadj);

  std::vector<Point>& vpoints = vcontours[0];
  int bSize = vpoints.size();

  DigitalSet ballDS = GraphFlow::Utils::Digital::Shapes::ball(1.0, 0, 0, 10);
  std::random_device rd;

  std::uniform_int_distribution opType(0, 1);
  std::uniform_int_distribution bPoint(0, bSize - 1);

  int nCenters = 1;
  for (int i = 0; i < nCenters; ++i) {
    int bPos = bPoint(rd);
    int op = opType(rd);

    Point translation = vpoints[bPos];

    if (op == 0) {
      for (Point p : ballDS) {
        Point curr = p + translation;
        if (dsOutput.domain().isInside(curr)) dsOutput.erase(curr);
      }
    } else {
      for (Point p : ballDS) {
        Point curr = p + translation;
        if (dsOutput.domain().isInside(curr)) dsOutput.insert(curr);
      }
    }
  }
}

void Random::evaluateCandidate(DigitalSet& dsOutput, const Blueprint& candidate,
                               const DigitalSet& dsInput) const {
  using namespace DGtal::Z2i;
  auto me = GraphFlow::Utils::Digital::Morphology::StructuringElement::CIRCLE;
  if (candidate.operationType == Blueprint::None) {
    dsOutput = dsInput;
  } else if (candidate.operationType == Blueprint::Dilation) {
    dilate(dsOutput, dsInput, GraphFlow::Utils::Digital::Morphology::StructuringElement(me, 1),
           1);
  } else if (candidate.operationType == Blueprint::Erosion) {
    erode(dsOutput, dsInput, GraphFlow::Utils::Digital::Morphology::StructuringElement(me, 1), 1);
  } else if (candidate.operationType == Blueprint::RandomOnContour) {
    dsOutput = dsInput;
    randomOnContour(dsOutput);
  }
}

}  // namespace GraphFlow::Core::Neighborhood
