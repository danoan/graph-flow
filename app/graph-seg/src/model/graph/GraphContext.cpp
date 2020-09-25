#include "model/graph/GraphContext.h"

namespace App::Graph
{
Context::Context(const GraphSegInput& gfi, const DigitalSet& ds, const RandomNeighborhood& neighborhood)
:gfi(gfi),
neighborhood(neighborhood),
ds(ds),
background(ds.domain())
{
  std::vector<DIPaCUS::Misc::ConnectedComponent> vcc;
  DIPaCUS::Misc::getConnectedComponents(vcc,ds);

  connectedComponents.resize(vcc.size());
  int id=0;
  for(auto v:vcc){
    connectedComponents[id] = std::make_pair(id,new DigitalSet(ds.domain()));
    connectedComponents[id].second->insert(v.begin(),v.end());
    id++;
  }

  background.assignFromComplement(ds);
  avgB = Utils::DataTerm::avgColor(background,gfi.cvImg);
  initialCVB = Utils::DataTerm::chanvese_region_term(background,gfi.cvImg,avgB);

  avgF = Utils::DataTerm::avgColor(ds,gfi.cvImg);
  initialCVF = Utils::DataTerm::chanvese_region_term(ds,gfi.cvImg,avgF);

}
}