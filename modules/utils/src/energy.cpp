#include "graph-flow/utils/energy.h"
#include <DGtal/io/boards/Board2D.h>

namespace GraphFlow::Utils::Energy
{

double elastica(const DigitalSet& ds,double ballRadius,double h,double alpha,double beta){
  KSpace kspace;
  kspace.init(ds.domain().lowerBound(),ds.domain().upperBound(),true);

  DGtal::SurfelAdjacency<2> sadj(true);
  std::vector< std::vector<DGtal::Z2i::SCell> > vscells;
  DGtal::Surfaces<KSpace>::extractAll2DSCellContours(vscells,kspace,sadj,ds);

  double elasticaValue=0;
  for(auto v:vscells){
    Curve curve;
    curve.initFromSCellsVector(v);
    elasticaValue+=elastica(curve.begin(),curve.end(),ds,ballRadius,h,alpha,beta);
  }

  return elasticaValue;
}

}