#include "graph-flow/core/neighborhood/RandomNeighborhood.h"

namespace GraphFlow::Core::Neighborhood{

void Random::randomOnContour(DigitalSet& dsOutput) const{
  using namespace DGtal::Z2i;

  std::vector<std::vector<Point>> vcontours;
  DGtal::SurfelAdjacency<2> sadj(true);

  KSpace kspace;
  kspace.init(dsOutput.domain().lowerBound(), dsOutput.domain().upperBound(), true);
  DGtal::Surfaces<KSpace>::extractAllPointContours4C(vcontours, kspace, dsOutput, sadj);

  std::vector<Point> &vpoints = vcontours[0];
  int bSize = vpoints.size();

  std::random_device rd;

  std::uniform_int_distribution ballSize(5, 10);
  std::uniform_int_distribution opType(0, 1);
  std::uniform_int_distribution bPoint(0, bSize - 1);

  DigitalSet ballDS = DIPaCUS::Shapes::ball(1.0, 0, 0, ballSize(rd));

  int nCenters = 1;
  for (int i = 0; i < nCenters; ++i) {
    int bPos = bPoint(rd);
    int op = opType(rd);

    Point translation = vpoints[bPos];

    if (op==0) {
      for (Point p:ballDS) {
        Point curr = p + translation;
        if (dsOutput.domain().isInside(curr)) dsOutput.erase(curr);
      }
    } else {
      for (Point p:ballDS) {
        Point curr = p + translation;
        if (dsOutput.domain().isInside(curr)) dsOutput.insert(curr);
      }
    }
  }
}

void Random::randomOnDomain(DigitalSet& dsOutput) const{
  using namespace DGtal::Z2i;

  DigitalSet ballDS = DIPaCUS::Shapes::ball(1.0, 0, 0, 5);
  std::random_device rd;

  Point lb = dsOutput.domain().lowerBound();
  Point ub = dsOutput.domain().upperBound();

  std::uniform_int_distribution opType(0, 1);
  std::uniform_int_distribution col(lb[0],ub[0]);
  std::uniform_int_distribution row(lb[1], ub[1]);

  int nCenters = 5;
  for (int i = 0; i < nCenters; ++i) {
    int c = col(rd);
    int r = row(rd);
    int op = opType(rd);

    Point translation{c,r};

    if (op==0) {
      for (Point p:ballDS) {
        Point curr = p + translation;
        if (dsOutput.domain().isInside(curr)) dsOutput.erase(curr);
      }
    } else {
      for (Point p:ballDS) {
        Point curr = p + translation;
        if (dsOutput.domain().isInside(curr)) dsOutput.insert(curr);
      }
    }
  }
}

void Random::evaluateCandidate(DigitalSet& dsOutput, const Blueprint& candidate, const DigitalSet& dsInput) const
{
  using namespace DGtal::Z2i;
  typedef DIPaCUS::Morphology::StructuringElement StructuringElement;

  if(candidate.operationType==Blueprint::None){
    dsOutput = dsInput;
  }else if(candidate.operationType==Blueprint::Dilation){
    dilate(dsOutput,dsInput,StructuringElement(me,candidate.morphologySize),1);
  }else if(candidate.operationType==Blueprint::Erosion){
    erode(dsOutput,dsInput,StructuringElement(me,candidate.morphologySize),1);
  }else if(candidate.operationType==Blueprint::RandomOnContour){
    dsOutput = dsInput;
    randomOnContour(dsOutput);
  }else if(candidate.operationType==Blueprint::RandomOnDomain){
    dsOutput = dsInput;
    randomOnDomain(dsOutput);
  }
}

}
