#ifndef GRAPH_FLOW_APP_GRAPH_SEG_GRAPHCONTEXT_H
#define GRAPH_FLOW_APP_GRAPH_SEG_GRAPHCONTEXT_H

#include <graph-flow/core/neighborhood/MorphologyNeighborhood.h>
#include <graph-flow/utils/digital.h>

#include "model/GraphSegInput.h"
#include "utils.h"

namespace App::Graph{
struct Context{
  typedef DGtal::Z2i::DigitalSet DigitalSet;
  typedef DGtal::Z2i::Domain Domain;

  typedef GraphFlow::Core::Neighborhood::Morphology MorphologyNeighborhood;

  Context(const GraphSegInput& gfi, const DigitalSet& ds, const MorphologyNeighborhood& neighborhood);

  Context(const Context& context)=delete;
  Context(Context&& context)=delete;
  ~Context(){
    for(auto D:connectedComponents) delete D;
  }

  std::vector<DigitalSet*> connectedComponents;
  const GraphSegInput& gfi;
  MorphologyNeighborhood neighborhood;
};


}

#endif //GRAPH_FLOW_APP_GRAPH_SEG_GRAPHCONTEXT_H
