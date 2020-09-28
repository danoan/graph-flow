#include "graph-flow/utils/energy.h"
#include <DGtal/io/boards/Board2D.h>

namespace GraphFlow::Utils::Energy
{

double elastica(const DigitalSet& ds,double ballRadius,double h,double alpha,double beta){
  KSpace kspace;
  kspace.init(ds.domain().lowerBound(),ds.domain().upperBound(),true);



  std::vector<DIPaCUS::Misc::ConnectedComponent> vcc;
  DIPaCUS::Misc::getConnectedComponents(vcc,ds);

  double elasticaValue=0;
  for(auto PS:vcc){
    DGtal::SurfelAdjacency<2> sadj(true);
    std::vector< std::vector<DGtal::Z2i::SCell> > vscells;

    DigitalSet cDS(ds.domain());
    cDS.insert(PS.begin(),PS.end());

    DGtal::Surfaces<KSpace>::extractAll2DSCellContours(vscells,kspace,sadj,cDS);


    for(auto v:vscells){
      Curve curve;
      curve.initFromSCellsVector(v);
      elasticaValue+=elastica(curve.begin(),curve.end(),cDS,ballRadius,h,alpha,beta);
    }
  }

  return elasticaValue;
}

}