#include "model/graph/GraphContext.h"

namespace App::Graph
{
Context::Context(const GraphSegInput& gfi, const DigitalSet& ds, const MorphologyNeighborhood& neighborhood)
:gfi(gfi),
neighborhood(neighborhood){
  std::vector<DIPaCUS::Misc::ConnectedComponent> vcc;
  DIPaCUS::Misc::getConnectedComponents(vcc,ds);

  const int nc =vcc.size();
  connectedComponents.resize(nc);

  for(int i=0;i<nc;++i){
    connectedComponents[i] = new DigitalSet(ds.domain());
    connectedComponents[i]->insert( vcc[i].begin(),vcc[i].end());
  }
}

}