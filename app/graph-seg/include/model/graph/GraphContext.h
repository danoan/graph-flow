#ifndef GRAPH_FLOW_APP_GRAPH_SEG_GRAPHCONTEXT_H
#define GRAPH_FLOW_APP_GRAPH_SEG_GRAPHCONTEXT_H

#include <graph-flow/core/neighborhood/RandomNeighborhood.h>
#include <graph-flow/utils/digital.h>

#include "model/GraphSegInput.h"
#include "utils/utils.h"
#include "utils/data-term.h"


namespace App::Graph{
struct Context{
  typedef DGtal::Z2i::DigitalSet DigitalSet;
  typedef DGtal::Z2i::Domain Domain;

  typedef GraphFlow::Core::Neighborhood::Random RandomNeighborhood;
  typedef std::pair<int,DigitalSet*> IdentifiedComponent;

  Context(const GraphSegInput& gfi, const DigitalSet& ds, const RandomNeighborhood& neighborhood);

  Context(const Context& context)=delete;
  Context(Context&& context)=delete;
  ~Context(){
    for(auto D:connectedComponents) delete D.second;
  }

  const DigitalSet& ds;
  std::vector<IdentifiedComponent> connectedComponents;
  const GraphSegInput& gfi;
  RandomNeighborhood neighborhood;

  DigitalSet background;
  cv::Vec3d avgB,avgF;
  double initialCVB, initialCVF;
};


}

#endif //GRAPH_FLOW_APP_GRAPH_SEG_GRAPHCONTEXT_H
