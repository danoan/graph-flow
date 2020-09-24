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
  avgB = Utils::DataTerm::avgColor(background,gfi.dataDistribution.gco.inputImage);
  initialCVB = Utils::DataTerm::chanvese_region_term(background,gfi.dataDistribution.gco.inputImage,avgB);

  avgF = Utils::DataTerm::avgColor(ds,gfi.dataDistribution.gco.inputImage);
  initialCVF = Utils::DataTerm::chanvese_region_term(ds,gfi.dataDistribution.gco.inputImage,avgF);

}
}